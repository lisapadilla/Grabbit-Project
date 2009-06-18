<?php
//$Id: hb_activity.inc,v 1.1.2.3 2008/12/28 22:52:49 stalski Exp $


/**
 * Class to handle user activity data
 *
 */
class hb_activity {
  
  // Private members are prefixed with m_
  private $m_uid = 0;
  private $m_uid_target = 0;
  private $m_nid_target = 0;
  private $m_hid = 0;
  private $m_karma_index = 0;
  private $m_access = HEARTBEAT_PUBLIC_TO_ALL;
  private $m_description = '';
  private $m_message_id = '';
  private $m_message = '';
  private $m_message_concat = '';
  private $m_variables_array = array();
  private $m_variables_string = '';
  
  public $message_type = '';
  public $module = '';
  public $perms = 0;
  
  /**
   * constructor
   */
  function __construct($data=null) {
    if(isset($data)) {
      $this->set_data($data);
    }
  }
  
  /**
   * Set data into members
   */
  public function set_data($data) {
    foreach($data as $key => $value) {
      if(isset( $this->{$key})) {
        $this->{$key} = $value;
      }
      if(isset( $this->{'m_'.$key})) {
        $this->{'m_'.$key} = $value;
      }
    }
    // Data variables are more complicated
    if(isset($data['variables'])) 
      $this->m_variables_string = $data['variables'];
    // if the data variables have not been included 
    // as normal members, do so now to be available when asked for 
    // @see __get
    if($this->m_variables_array == array() && $this->m_variables_string != '') {
      $this->variables2array();
    }
  }  
  
  /**
   * Method gets a hb_activity variable
   * 
   * @desc The magic getter method fetches a variable
   *       in members. If not found there, it will always 
   *       check the variables as well
   */
  public function __get($variable) {    
    // a private member is asked
    $var = null;
    if( isset( $this->{'m_'.$variable} ) ) {
      $var = $this->{'m_'.$variable};
    }
    else if(array_key_exists($variable, $this->m_variables_array)) {
      $var = $this->m_variables_array[$variable];
    }
    return $var;
  }
  
  /**
   * public function to set variables into readable array
   */
  public function variables2array() {    
    $this->m_variables_array = heartbeat_decode_message_variables($this->m_variables_string);
    return $this->m_variables_array;
  }
  
  /**
   * Public function to save activity to database
   * @param array raw argument to enforce as is (pre-renderd)
   */
  public function save($raw_args=array()) {         
    if(module_exists('locale')) { 
      $this->save_locale($raw_args);
    }
    else {
      $this->_save($raw_args);
    }
  }
  
  /**
   * Save activity log with multilingual content
   * and multilingual parts to pre-translate
   *
   * @param array $raw_args
   */
  private function save_locale($raw_args=array()) {    
    $args = $this->rebuild_arguments($raw_args, true);
    $locale = $args['locale'];
    unset($args['locale']);
    // Save activity by logging a row for each active language  
    // Translations only when locale exists
    $languages = locale_language_list();
    foreach($languages as $language => $human_language) {      
      // preprocess multilingual message "parts"
      // for all flagged token replacements     
      foreach($this->m_variables_array as $key => $value) {
        if(isset($locale[$key])) {
          $amp_token = str_replace("#","!",$key);
          $args[$amp_token] = locale($locale[$key], $language);
        }
      }
      $this->log_message($args,$language);      
    }
  }
  
  /**
   * Save activity log
   *
   * @param array $raw_args
   */
  private function _save($raw_args=array()) {
    // Rebuild arguments with tokens
    $args = $this->rebuild_arguments($raw_args);    
    $this->log_message($args);
  }
  
  /**
   * Logs a heartbeat message 
   * @param string language optional 
   *
   */
  private function log_message($args, $lang='') {      
    if($lang == '') {  
      global $language; 
      $lang = $language->language;
    }  
    // Mis-usage of the t-function, but how could i fix this?
    $message = t($this->m_message, $args, $lang);
    $message_concat = t($this->m_message_concat, $args, $lang);
    // Checks if there should be logging what so ever
    if(empty($message)){
      watchdog('heartbeat', 'Error in logging user activity: it is not possible to log empty message', array(), WATCHDOG_ERROR);
      return false;
    }
    if(!is_numeric($this->m_uid) || $this->m_uid <= 0){
      watchdog('heartbeat', 'Error in logging user activity: no information on the user invoking heartbeat activity', array(), WATCHDOG_ERROR);
      return false;
    }
    //dsm($message);
    // Log relational message to user activity
    db_query("INSERT INTO {hb_activity} SET uid=%d, uid_target=%d, nid_target=%d, message_id='%s', language='%s', 
    access = %d, message ='%s',message_concat ='%s', timestamp=%d, variables='%s'", 
    $this->m_uid,  $this->m_uid_target, $this->m_nid_target, $this->m_message_id, $lang,
    $this->m_access, $message, $message_concat, $_SERVER['REQUEST_TIME'], $this->m_variables_string );
    
  }
  
  /**
   * Rebuild the arguments for variables
   * to share within this object
   *
   * @param array $raw_input of arguments
   */
  private function rebuild_arguments($raw_input, $locale=false) {  
    $args = array();    
    if($locale) {      
      // Variables that need to be pre-translated go here
      $args['locale'] = array();
    }
    // Rebuild arguments with language tokens
    foreach($this->m_variables_array as $key => $value) {
      // Leave $key[0] == "!"  asis
      if($key[0] != "@" && $key[0] != "#" ) {
        continue; // bad argument
      }
      $oldkey = $key;            
      // Reset the key of the arguments to ! to parse the next 
      // tokenization asis.
      if($key[0] == "@") $key[0] = "!";        
      // # and @ token replacement prefixes are kept,
      // but set a flag for it in the raw_arguments
      if($key[0] == "#") {
        //dsm($key.' '.$value);   
        // if it has to be translated ...
        if($locale) $args['locale'][$key] = $value;
        // Now reset the key
        $key[0] = "!";        
      }    
      // if argument is prefilled, override
      if(isset($raw_args[$oldkey])) {
        $args[$key] = $raw_args[$oldkey];
        continue;
      }      
      // Argument gets the value as in variables
      $args[$key] = $value;
    }
    return $args;
  }

} // eof class hb_activity
