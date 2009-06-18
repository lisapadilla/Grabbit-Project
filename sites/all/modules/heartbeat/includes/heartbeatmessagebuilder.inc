<?php

/**
 * @file 
 * Strategy with access behaviour
 * 
 * @usage  
 * $context = new HeartbeatMessageBuilder(new PublicBehaviour());
 * $context->execute();
 * 
 * $context = new HeartbeatMessageBuilder(new PrivateBehaviour());
 * $context->execute();
 * 
 * $context = new HeartbeatMessageBuilder(new ConnectedBehaviour());
 * $context->execute();
 * 
 */
 
heartbeat_include('heartbeat');

/**
 * Abstract class heartbeataccess
 * This base class has final template methods which are
 * used by the derived concretes. The HeartbeatAccess is a 
 * state object that is given to the HeartbeatMessageBuilder to 
 * set the access to the current request.
 */
abstract class HeartbeatAccess {
  
  protected $_access = -1;
  
  public function fetchMessages() {
    $heartbeat = $this->prepareHeartbeatInfo();
    $heartbeat = $this->dressUpMessages($heartbeat);
    return $this->finishMessages($heartbeat);
  }
  
  protected function prepareHeartbeatInfo() {    
    global $user, $language;
    $full_timespan = variable_get('hb_activity_no_duplicate_seconds',172800) - 1;    
    $heartbeatInfo = new HeartbeatInfo();
    $heartbeatInfo->uid = $user->uid;
    $heartbeatInfo->access = $this->getAccess();
    $heartbeatInfo->user_relations = heartbeat_get_related_uids($heartbeatInfo->uid);
    // Populate the user object with a users relations
    $user->heartbeat_relations = $heartbeatInfo->user_relations;
    $heartbeatInfo->limit_sql = variable_get('heartbeat_block_items_max',250);
    $heartbeatInfo->language = $language->language;
    $heartbeatInfo->start_time = $_SERVER['REQUEST_TIME'] - (int)$full_timespan;
    $heartbeatInfo->time_span = date("G",$full_timespan) . ' hours';
    // Dirty sql parts 
    $heartbeatInfo->sql_start = "SELECT 
      hm.message AS 'message_orig', hm.message_concat AS 'message_concat_orig', 
      hm.concat_args, hm.karma_index, hm.module, hm.merge, hm.perms, 
      ua.*,  1 AS 'count' 
    FROM {hb_activity} ua 
    LEFT JOIN {heartbeat_messages} hm ON ua.message_id = hm.message_id 
    WHERE ua.language = '%s' ";
    $heartbeatInfo->sql_end = " AND timestamp > %d ORDER BY timestamp DESC";
    $heartbeat = Heartbeat::instantiate($this->getAccess());  
    $heartbeat->set_info($heartbeatInfo);
    return $heartbeat;
  }

  protected abstract function dressUpMessages(Heartbeat $heartbeat);

  protected function finishMessages(Heartbeat $heartbeat) {
    //do final things
    // Under certain conditions, the presence of a GROUP BY clause could
    // cause an ORDER BY clause to be ignored.
    //http://bugs.mysql.com/bug.php?id=32202 
    if(count($heartbeat->raw_messages) > 0) {      
      $duplicates = array();
      $duplicates += module_invoke_all('heartbeat_messages_alter', $heartbeat->raw_messages);
      $messages = $heartbeat->raw_messages;
      if(!empty($duplicates)) {
        $messages = array_diff_key ($messages ,$duplicates);
      }
      $heartbeat->raw_messages = $messages;
    }
    return $heartbeat;
  }
  
  final protected function getAccess() {
    return $this->_access;
  }
}

// Concrete strategy behaviour classes
// Altered into state objects within peer review 


/**
 * Class PublicHeartbeat
 * Concrete class to prepare messages for all  
 * users in the site of whom the heartbeat is 
 * set to public
 *
 */
class PublicHeartbeat extends HeartbeatAccess {
  
  protected $_access = HEARTBEAT_PUBLIC_TO_ALL;
  
  public function dressUpMessages(Heartbeat $heartbeat) {
    $heartbeatInfo = $heartbeat->get_info();
    $heartbeatInfo->uid = 0;
    $heartbeatInfo->limit_view = variable_get('heartbeat_block_public_items_max', 25);
    $heartbeatInfo->user_relations = $heartbeatInfo->uid;
    $heartbeat->set_info($heartbeatInfo);
    
    $sql = $heartbeatInfo->sql_start;
    // logic to fetch messages public to all
    $sql.= " AND ua.uid > %d  AND ua.access > 0 ";  
    $sql.= $heartbeatInfo->sql_end;
    $result = db_query_range($sql, $heartbeatInfo->language, $heartbeatInfo->uid, 
      $heartbeatInfo->start_time, 0,$heartbeatInfo->limit_sql);
    while($heartbeat_row = db_fetch_object($result) ) {
      $heartbeat->raw_messages[$heartbeat_row->uaid] = $heartbeat_row; 
    }
    return $heartbeat;
  }
}
 

/**
 * Class PrivateHeartbeat
 * Concrete class to prepare messages for the 
 * current user only
 *
 */
class PrivateHeartbeat extends HeartbeatAccess {
  
  protected $_access = HEARTBEAT_PRIVATE;
  
  public function dressUpMessages(Heartbeat $heartbeat) {
    $heartbeatInfo = $heartbeat->get_info();
    $heartbeatInfo->limit_view = variable_get('heartbeat_block_public_items_max', 25);    
    $heartbeat->set_info($heartbeatInfo);
    $sql.= " AND ((ua.uid = %d  AND ua.access = %d ) OR (ua.uid_target = %d AND ua.access > 0) )";    
    $sql.= $heartbeatInfo->sql_end;
    $result = db_query_range($sql, $heartbeatInfo->language, $heartbeatInfo->uid, $heartbeatInfo->access, 
    $heartbeatInfo->uid,  $heartbeatInfo->start_time, 0,$heartbeatInfo->limit_sql);
    while($heartbeat_row = db_fetch_object($result) ) {
      $heartbeat->raw_messages[$heartbeat_row->uaid] = $heartbeat_row; 
    }
    return $heartbeat;
  }
}


/**
 * Class ConnectedHeartbeat
 * Concrete class to prepare messages for the current user
 * and all of his/her relations.
 *
 */
class ConnectedHeartbeat extends HeartbeatAccess {
  
  protected $_access = HEARTBEAT_PUBLIC_TO_CONNECTED;
  
  public function dressUpMessages(Heartbeat $heartbeat) {
    $heartbeatInfo = $heartbeat->get_info();
    $heartbeatInfo->limit_view = variable_get('heartbeat_block_public_items_max', 25);	  
    $heartbeat->set_info($heartbeatInfo);
	  $sql = $heartbeatInfo->sql_start;
	  $sql.= " AND (
	   (ua.uid in( ". implode(',',$heartbeatInfo->user_relations) ." ) AND ua.access >= 0 )  
	   OR (ua.uid_target = %d AND ua.nid_target <> 0 )
	   )";
	  $sql.= $heartbeatInfo->sql_end;
	  $result = db_query_range($sql, $heartbeatInfo->language, $heartbeatInfo->uid,
	   $heartbeatInfo->start_time, 0,$heartbeatInfo->limit_sql);
	  while($heartbeat_row = db_fetch_object($result) ) {
	    $heartbeat->raw_messages[$heartbeat_row->uaid] = $heartbeat_row; 
	  }
    return $heartbeat;
  }
}
 
/**
 * Class HeartbeatMessageBuilder
 * Message builder that fetches and customizes a 
 * users activity on the site. 
 * The builder takes a heartbeataccess state object to 
 * handle the request to fetch the messages.
 *
 */
class HeartbeatMessageBuilder {
  
  private $_heartbeatState = null;
 
  public function __construct(HeartbeatAccess $heartbeatState) {
    $this->_heartbeatState = $heartbeatState;
  }
 
  public function execute() {
    $heartbeat = $this->_heartbeatState->fetchMessages();
    return $this->group($heartbeat);
  }
    
  /**
   * @see class HeartbeatParser
   */
  public function group(Heartbeat $heartbeat) {
	  $heartbeat->set_timespan_gap(variable_get('hb_activity_grouping_seconds',720));
	  $heartbeat->build_sets($heartbeat->raw_messages);
	  $heartbeat->merge_sets();
	  $messages = $heartbeat->get_messages();
	  //  $messages = $heartbeat->remove_broken_messages();
    return $messages;
  }
}