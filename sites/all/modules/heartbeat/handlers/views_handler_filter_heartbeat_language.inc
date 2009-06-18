<?php
// $Id: views_handler_filter_heartbeat_language.inc,v 1.1.2.1 2009/01/17 20:41:45 stalski Exp $ 

/**
 * Filter by language
 */
class views_handler_filter_heartbeat_language extends views_handler_filter_boolean_operator {
  
  function construct() {
    parent::construct();
    $this->value_value = t('Is the current language');
  }

  function query() {
    $this->ensure_my_table();   
    //watchdog('useractivity',"$this->table_alias.$this->real_field " . (empty($this->value) ? '!=' : '=') . " ***CURRENT_LANGUAGE***");
    
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field " . (empty($this->value) ? '!=' : '=') . " '***CURRENT_LANGUAGE***'");
  }
  
}