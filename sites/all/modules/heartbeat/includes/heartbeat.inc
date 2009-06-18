<?php
// $Id: heartbeat.inc,v 1.1.2.9 2009/02/24 21:27:44 stalski Exp $

class HeartbeatInfo
{
  public $uid = 0;
  public $user_relations = array();
  public $limit_sql = 0;
  public $limit_view = 0;
  public $language = 'en';
  public $start_time = null;
  public $time_span = '';
  public $sql_start = '';
  public $sql_end = '';
  public $access = -1;
}

class Heartbeat
{
  private $_info = null;
  private $_candidates = array();
  private $_messages = array();
  private $_sets = array();
  private $_timespan_gap = 0;
  public $raw_messages = array();
  
  private function __construct() {
  }
  
  /**
   * Set the first time , start time of the gap
   */
  public function set_timespan_gap($gap) {
    $this->_timespan_gap = $gap;
  }
  
  /**
   * build sets of messages
   */
  public function build_sets($messages_raw) {
    $renewal_time = $_SERVER['REQUEST_TIME'] - $this->_timespan_gap;
	  $raw_messages = array();    
	  foreach($messages_raw as $key => $message) {	  
      // if the time with the gap exceeds the starttime 
      if($renewal_time >= $message->timestamp) {
        // reset the start time of the set
        $renewal_time = $message->timestamp - $this->_timespan_gap;
      }
      $this->_sets[$renewal_time][$key] = $message;      
	    // Rebuild the variables
	    $this->_sets[$renewal_time][$key]->variables = heartbeat_decode_message_variables($message->variables);
	    // rebuild concat arguments
	    $this->_sets[$renewal_time][$key]->concat_args = heartbeat_decode_message_variables($message->concat_args);	    
	  }
  }
  
  /**
   * Sets information on heartbeat messages in total
   */
  public function set_info(HeartbeatInfo $info) {
    $this->_info = $info;
  }
  
  public function get_info(){
    return $this->_info;
  }
  
  /**
   * Merges sets of messages to fully formatted messages
   * regenerated at runtime to group settings 
   */
  public function merge_sets() {     
	  $set_count = 0;
	  foreach($this->_sets as $message_set) {	    
	    $this->prepare_candidates($message_set, $set_count);	    
	    $set_count++;
	  }
    $this->remove_variables_duplicates();
    $this->rebuild_in_groups();    
    
	  return $count;
  }
  
  /**
   * Gets the messages as they exist for the time asked
   */
  public function get_messages($limit=0) {  
    if($limit > 0) {
      $this->_info->limit_view = $limit;
    }
	  return array_slice($this->_messages, 0, $this->_info->limit_view);
  }
    
  /**
   * Function to remove duplicate messages
   * meaning remove exactly the same already build messages,
   * incrementing the count of the messages
   * User-user relation always have duplicates that need to be removed.
   * This is handled here as well. Take care: the counter cannot increment!
   */
  private function remove_message_duplicates($message_set) {
    global $user;
	  // hash holding all unique values
	  // if this would be static ...you could do it for all timespan-sets
	  $holder = array();
	  $ow_relations = array();
    foreach($message_set as $key => $message) {
      if($message->concat_args['group_by'] == 'user-user' && $this->_info->access == HEARTBEAT_PUBLIC_TO_ALL) {
        if(!isset($ow_relations[$message->uid_target])) {
          $ow_relations[$message->uid_target] = array();
        }
        // Find bad duplicates in two way relations (5-2 and 2-5)
        if(!in_array($message->uid, $ow_relations[$message->uid_target])){
          $ow_relations[$message->uid][] = $message->uid_target;
        }
      }
    }
    
	  foreach($message_set as $key => $message) {
	    if($message->concat_args['group_by'] == 'user-user') {
	      // If i am not the actor, but one of my relations is
	      // and i am the target for the relation, then 
	      // it is a duplicate message    
	      if($this->_info->access == HEARTBEAT_PUBLIC_TO_CONNECTED && $message->uid_target == $user->uid 
	      && in_array($message->uid, $user->heartbeat_relations)) {
	        unset($message_set[$key]);
	      }
	      if($this->_info->access == HEARTBEAT_PUBLIC_TO_ALL) {
	        if(!in_array($message->uid, $ow_relations[$message->uid_target])) {
          unset($message_set[$key]);
	        }
	      }
	    }
      
      // if an exact identical message occurs contextual wise,
      // then skip it with an incrementation of the frequency 
      // of the message
	    if(in_array($message->message, $holder)) {
	      $message_set[array_search($message->message, $holder)]->count++;
	      // dsm($message_set[$key]);
	      unset($message_set[$key]);
	    } else {
	      $holder[$key] = $message->message;      
	    }
	  }
	  return $message_set;
  }

  /**
   * Prepare message candidates
   * This is an important method that handles several things
   * - Build an id for each time-gap limiting groupable messages
   * - Hold the candidates for each id (and count of messages)
   * - Logic to handle the group_by node or user setting
   */
  private function prepare_candidates($message_set, $set_count=0) {
    static $singles = 0;
    // Remove duplicate messages in the same set, 
    // incrementing the counter on the grouped message  
    $message_set = $this->remove_message_duplicates($message_set);
    foreach($message_set as $key => $message) {
      //$message->concat_args['group_by']
      //$message->concat_args['group_target']
      $type = $message->concat_args['type'];
      $message->target_count = 0;
      // Variable to hold the grouping gap id
      // Addons to the grouping gap id will result in summaries 
      // and groups of identical and related messages.
      $gap_id = 'BEAT_'.$set_count.'_'.$message->message_id;
      // Summaries have to be evaluated for merging
      if($type == 'summary' || $type == 'count' || $message->merge) {        
        if( $this->extend_gap_id($gap_id, $message, $type, $set_count)) {        
	        // Add a candidates if this one does not exist yet
	        if(!isset($this->_candidates[$gap_id])){
	          $this->_candidates[$gap_id] = array(
	            'count' => 0,
	            'group_target' => $message->concat_args['group_target'],
	            'variables' => array()
	          );
	          // Add the message
	          $this->_messages[$gap_id] = $message;      
	        }
	        $this->_messages[$gap_id]->target_count++; // first time is 1        
	        // pass variables, incrementing the count if needed    
	        $this->_candidates[$gap_id]['variables'][] = $message->variables;
	        $this->_candidates[$gap_id]['count']++;  // NOT the same as message->count (grouped by sql) 
        }       
      }
      else {
        // Autoincrement the singles to make the gap_id unique
        $gap_id .= '_single_'. $singles;
        $singles++;
        // Add the message
        $this->_messages[$gap_id] = $message;
      }
    }
  }
  
  /**
   * Remove broken messages
   * @Todo build this function 
   */
  public function remove_broken_messages($messages=array()) {
    if($messages == array()) {
      $messages = $this->_messages;
    }
    return $messages;
  }

	/**
	 * Function to remove duplicate messages valuating the
	 * variables and count properties 
	 */
	private function remove_variables_duplicates() { 
	  $uniques = array();
	  foreach($this->_candidates as $single_id => $info) { 
	    $uniques[$single_id] = array();
	    // Loop through variables to check if there are identical
	    foreach($info['variables'] as $rid => $value) {
	      if(!in_array($value, $uniques[$single_id])) {
	        $uniques[$single_id][] = $value;
	      }
	      else {
	        unset($this->_candidates[$single_id]['variables'][$rid]);
	      }
	    }
	  }
	  // Re-evaluate the counts
	  foreach($this->_candidates as $single_id => $info) { 
	    $this->_candidates[$single_id]['count'] = count($this->_candidates[$single_id]['variables']);
	  }
	  return $uniques;
	}
	
	/**
	 * Private helper function to build the gap_id
	 */
	private function extend_gap_id(&$gap_id, $message, $type, $set_count) {   
    // group by node will result in a summary of users 
    // performing the activity
    if($message->concat_args['group_by'] == 'node') {
      $gap_id .= '_'.$message->concat_args['group_target'].'_node_'.$message->nid_target;
    }
    // group by user will result in a summary of content
    // nodes which the user has done the activity on
    else if($message->concat_args['group_by'] == 'user') {          
      $gap_id .= '_'.$message->concat_args['group_target'].'_user_'.$message->uid;
    }
    // group by user-user will result in unique user-user 
    // messages, expressing a relation between the two users
    else if($message->concat_args['group_by'] == 'user-user') {
      $gap_id .= '_user_relation';
      $gap_id .= '_'. $message->uid;
    }
    else {
      // Handle the fall-backs as unique messages
      $gap_id .= '_'.$message->uid.'_'.$message->uid_target;
    }
    return TRUE;
	}
	
	/**
	 * Function to rebuild the messages in groups
	 * all sets are handled already
	 */
	private function rebuild_in_groups() {	    
        
    // Check the candidates and make the rebuild array
    foreach($this->_candidates as $single_id => $info) {   
      $message = $this->_messages[$single_id];      
      // if a candidate exists for this message and 
      // it has more than one count 
      // Take care!! not message->count because this could be set with the sql as well 
      // The purpose would be to fill %times%   
      if($this->_candidates[$single_id]['count'] > 1) {
        
        $message_template = $this->_messages[$single_id]->message_concat;
        $message_template = str_replace("%times%", $message->target_count, $message_template);
        // Prepare the merged factors from the stored messages
        $merged_string = '';
        
        $unique = $info['variables'];
        $count = $info['count'];//count($info['variables']);    
        if($count > variable_get('hb_activity_grouping_how_many', 6)) {
          $count = variable_get('hb_activity_grouping_how_many', 6);
          $unique = array_slice($unique, 0, $count);
        }
            
        // Replacement of placeholder with group targets
        // If there is a match for %variable%
        // Try to replace the variable with the group_target variables
        if(preg_match_all("|\%(.*)\%(.*)|U", $message_template, $matches)) {
          // This code in comment is/was a attempt to have more grouping words
          // The difficult and almost impossible part is the fact that you always
          // have to target something to group on (for the same node or same user)
          //foreach($matches[1] as $target) {       
            $placeholder = $matches[1][0];
            $target = $message->concat_args['group_target'];
            //dsm($target.$placeholder);
            $i = 1;          
            foreach($unique as $stored_variables) {
              // limit them to the value given by the group variable setting    
              if(isset($stored_variables["@".$target])) {
                if($i == 1) {
                  $merged_string .= ' '.$stored_variables["@".$target];
                }
                else if($i < $count && $count > 2) {
                  $merged_string .= ' '.$message->concat_args['merge_separator'];
                  $merged_string .= ' '.$stored_variables["@".$target];
                }
                else if($i == $count || $count == 2) {
                  $merged_string .= ' '.$message->concat_args['merge_end_separator'];
                  $merged_string .= ' '.$stored_variables["@".$target];
                }          
              }
              $i++;
            }
            $message_template = str_replace("%".$placeholder."%", $merged_string, $message_template);
          //}
        }
        $this->_messages[$single_id]->message = $message_template;
      }   
    }
	}
  
  /**
   * Creates an instance of heartbeat as singleton
   */
  static public function instantiate($type='cached') {    
    static $instances;    
    if(!$instances) {
      $instances = array();
    }
    if(!isset($instances[$type])) {
      $instances[$type] = new heartbeat();
    } 
    return $instances[$type];
  }
  
}

// eof