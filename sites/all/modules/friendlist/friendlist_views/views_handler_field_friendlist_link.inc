<?php
// $Id: views_handler_field_friendlist_link.inc,v 1.1.2.4 2008/10/02 08:27:42 mercmobily Exp $

/**
 * @file
 * views_handler_field_friendlist_link for Views integration
 *
 */

/**
 * Field handler to present a link to the user.
 */
class views_handler_field_friendlist_link extends views_handler_field {

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function construct() {
    parent::construct();
    $this->additional_fields['requestee_id'] = 'requestee_id';
    $this->additional_fields['requester_id'] = 'requester_id';
    $this->additional_fields['rtid'] = 'rtid';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  // An example of field level access control.
  function access() {
    return user_access('access user profiles');
  }

}

