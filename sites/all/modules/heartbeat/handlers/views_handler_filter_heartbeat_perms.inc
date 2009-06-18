<?php
class views_handler_filter_heartbeat_perms extends views_handler_filter_in_operator {

  function construct() {
    parent::construct();
    $this->definition['numeric'] = TRUE;
  }

  /**
   * Child classes should override this function to set the 'value options'.
   * This can use a guard to be used to reduce database hits as much as
   * possible.
   */
  function get_value_options() {
    $this->value_options = variable_get('heartbeat_perms', array('Private', 'Friends', 'Full Site', 'All'));
  }
  
}
?>