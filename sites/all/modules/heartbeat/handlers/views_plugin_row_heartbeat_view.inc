<?php
// $Id: views_plugin_row_heartbeat_view.inc,v 1.1.2.2 2009/02/25 00:19:44 stalski Exp $
/**
 * @file
 * Contains the heartbeat row style plugin.
 */

/**
 * Plugin which performs a heartbeat_view on the resulting object.
 *
 * Most of the code on this object is in the theme function.
 */
class views_plugin_row_heartbeat_view extends views_plugin_row {
  
  function init(&$view, &$display, $options=NULL) {
    
    // call init of base class
    parent::init($view, $display, $options);
    if($view->query === null) {
      //drupal_set_message('Something went wrong while fetching heartbeat messages.', 'error');
      return;
    }
    $table1 = 'hb_activity'; 
    $table2 = 'heartbeat_messages';
    $join_by = 'message_id';    
    
    // Clear the fields first
    //$view->query->clear_fields();
    // Build the fields for hb_activity
    $fields = _heartbeat_get_fields($table1);   
    foreach($fields as $field => $alias) {
      $view->query->add_field($table1, $field, $alias);
    }
    
    // Build the fields for heartbeat_messages    
    $join = new views_join;
    $join->construct($table2, $table1, $join_by, $join_by);
    $view->query->add_relationship($table2, $join, $table1);    
    
    //$view->query->add_table($table2);
    $fields = _heartbeat_get_fields($table2);    
    foreach($fields as $field => $alias) {
      $view->query->add_field($table2, $field, $alias);
    }
  }
  
  function uses_fields() {
    $has_fields = !empty($this->definition['uses fields']);    
    return $has_fields;
  }  
  
  function option_definition() {   
    $options = parent::option_definition();
    $options['messages'] = array('default' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['messages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display messages'),
      '#default_value' => $this->options['messages'],
    );
  }

  /**
   * Override the behavior of the render() function.
   */
  function render($row) {
    return theme($this->theme_functions(), $this->view, $this->options, $row);
  }
}
