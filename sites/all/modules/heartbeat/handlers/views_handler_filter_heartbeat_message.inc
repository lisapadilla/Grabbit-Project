<?php
// $Id: views_handler_filter_heartbeat_message.inc,v 1.1.2.1 2009/01/17 20:41:45 stalski Exp $ 

/**
 * Filter by language
 */
class views_handler_filter_heartbeat_message extends views_handler_filter_boolean_operator {
  
  function construct() {
    parent::construct();
    $this->value_value = t('message ... not implemented yet');
  }

  function query() {
    $this->ensure_my_table(); 
  }
  
}