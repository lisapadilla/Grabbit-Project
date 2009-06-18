<?php
// $Id: views_handler_filter_heartbeat_access.inc,v 1.1.2.3 2009/02/24 21:27:43 stalski Exp $ 

/**
 * Filter by language
 */
class views_handler_filter_heartbeat_access extends views_handler_filter_numeric {
  
  public $heartbeat_access = -1;
  public $heartbeat_relations = array();
  
  function construct() {
    parent::construct();
    $this->value_value = t('Are restricted to access type');
  }
  
  /**
   * Implementation override option_definition
   * Information about options for all kinds of purposes will be held here. 
   *
   * @return array options definition
   */
  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }
    
  /**
   * Set default values for the heartbeat access filter.
   */ 
  function options(&$options) {
    parent::options($options);
    $options['value']['access'] = array();
  }

  /**
   * Definition of available operators
   * Override the parent method
   *
   * @return array of operators
   */
  function operators() {
    $operators = array(
      '=' => array(
        'title' => t('Is equal to'),
        'method' => 'op_simple',
        'short' => t('='),
        'values' => 1,
      ),
      '!=' => array(
        'title' => t('Is not equal to'),
        'method' => 'op_simple',
        'short' => t('!='),
        'values' => 1,
      )
    );
    // if the definition allows for the empty operator, add it.
    if (!empty($this->definition['allow empty'])) {
      $operators += array(
        'empty' => array(
          'title' => t('Is empty (NULL)'),
          'method' => 'op_empty',
          'short' => t('empty'),
          'values' => 0,
        ),
        'not empty' => array(
          'title' => t('Is not empty (NULL)'),
          'method' => 'op_empty',
          'short' => t('not empty'),
          'values' => 0,
        ),
      );
    }
    return $operators;
  }
  
  /**
   * Display the filter on the administrative summary. 
   * After selecting, let the builder of the view
   * know what he selected
   *
   * @return human title for the access type
   */
  function admin_summary() {
    $options = _heartbeat_access_type_options();
    $key = (int) (isset($this->value['access']) ? $this->value['access'] : HEARTBEAT_PRIVATE);
    return $options[$key]; 
  }  
  
  /**
   * Adding things to query object
   *
   */
  function query() {
    global $user;
    $uid = $user->uid;
    $this->ensure_my_table();
    $info = $this->operators();
    //dsm($this->query);
    $access = $this->value['access'];    
    // Make the sql limited to the access
    $field = "$this->table_alias.$this->real_field";
    $this->heartbeat_access = $access;
    switch($access) {
      case HEARTBEAT_PUBLIC_TO_CONNECTED:
        $uids = heartbeat_get_related_uids($uid);
        $this->heartbeat_relations = $uids;
        $this->query->set_where_group('OR','orgroup'); 
        $sql = "$field in( ".implode(',',$uids)." ) AND $this->table_alias.access >= 0 ";
        $this->query->add_where('orgroup', $sql);        
        $sql = "$this->table_alias.uid_target = %d AND $this->table_alias.nid_target <> 0";
        $this->query->add_where('orgroup', $sql,$uid);         
        break;
      case HEARTBEAT_PRIVATE:
        $this->query->set_where_group('OR','orgroup');
        $uids = heartbeat_get_related_uids($uid); 
        $this->heartbeat_relations = $uids;
        $sql = "$field = %d  AND $this->table_alias.access = %d ";
        $this->query->add_where('orgroup', $sql, $uid, $access);        
        $sql = "($this->table_alias.uid_target = %d AND $this->table_alias.access > 0)";
        $this->query->add_where('orgroup', $sql, $uid);  
        break;
      case HEARTBEAT_PUBLIC_TO_ALL:
        $sql = "$field > %d  AND $this->table_alias.access > 0";
        $this->query->add_where('andgroup', $sql, $uid);
        break;
      default:
        $sql = "$field = %d";
        $this->query->add_where('andgroup', $sql, $uid); 
    }    
  }

  /**
   * Add a type selector to the value form
   */
  function value_form(&$form, &$form_state) {   
    if (empty($form_state['exposed'])) {
      $form['value']['access'] = array(
        '#type' => 'radios',
        '#title' => t('Access type'),
        '#options' => _heartbeat_access_type_options(),
        '#default_value' => !empty($this->value['access']) ? $this->value['access'] : HEARTBEAT_PRIVATE,
      );
    }
    parent::value_form($form, $form_state);
  }
  
}