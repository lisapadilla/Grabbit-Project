<?php
// $Id: friendlist_rules.rules.inc,v 1.1.2.12 2008/10/11 18:47:29 mercmobily Exp $

/**
 * @file
 * Rules data types, actions, conditions, events and tokens.
 */

#######################################################################
#                       DATA TYPES
#######################################################################

/**
 * Implementation of hook_rules_data_type_info().
 */
function friendlist_rules_rules_data_type_info() {
  return array(

    'relation_status' => array(
      'label' => t('Relation status'),
      'class' => 'rules_data_type_relation_status',
      'identifiable' => TRUE,
    ),

    'relation_type' => array(
      'label' => t('Relation type'),
      'class' => 'rules_data_type_relation_type',
      'identifiable' => TRUE,
    ),

    'relation_message' => array(
      'label' => t('Relation message'),
      'class' => 'rules_data_type_relation_message',
      'identifiable' => TRUE,
    ),

  );
}


/**
 * Rules relation_status data type.
 */
class rules_data_type_relation_status extends rules_data_type {

  function get_identifier() {
    $id = &$this->get();
    return $id;
  }

  function load($string) {
    return $string;
  }


}

/**
 * Rules relation_type data type.
 */
class rules_data_type_relation_type extends rules_data_type {

  function get_identifier() {
    $id = &$this->get();
    return $id;
  }

  function load($string) {
    return $string;
  }

}

/**
 * Rules relation_message data type.
 */
class rules_data_type_relation_message extends rules_data_type {

  function get_identifier() {
    $id = &$this->get();
    return $id;
  }

  function load($string) {
    return $string;
  }

}


#######################################################################
#                          ACTIONS
#######################################################################


/**
 * Implementation of hook_rules_action_info().
 *
 * @ingroup rules.
 */
function friendlist_rules_rules_action_info() {
  return array(

    'rules_action_friendlist_add' => array(
      'label' => t('Create a relationship between users'),
      'eval input' => array(
        'user1_param',
        'user2_param',
        'rtid_param',
        'message_param'
      ),

      'help' => 'Create a relationship between users',
      'module' => 'Friendlist Rules',
    ),

    'rules_action_friendlist_delete' => array(
      'label' => t('Delete a relationship between users'),
      'eval input' => array(
        'user1_param',
        'user2_param',
        'rtid_param',
      ),

      'help' => 'Delete a relationship between users',
      'module' => 'Friendlist Rules',
    ),

  );
}

/**
 * Form to add a relation in FriendList.
 *
 * Action drupal message configuration form.
 */
function rules_action_friendlist_add_form($settings, &$form) {
  $settings += array('user1_param' => '', 'user2_param' => '', 'rtid_param' => '', 'message_param' => '');


  $form['settings']['user1_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '15',
    '#title' => t('User 1'),
    '#default_value' => $settings['user1_param'],
    '#description' => t('The user from which the relation will start'),
  );

  $form['settings']['user2_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '15',
    '#title' => t('User 2'),
    '#default_value' => $settings['user2_param'],
    '#description' => t('The user to which the relation will get'),
  );


  $form['settings']['rtid_param'] = array(
    '#type' => 'textfield',
    '#size' => '25',
    '#maxsize' => '25',
    '#title' => t('Relation type ID'),
    '#default_value' => $settings['rtid_param'],
    '#description' => t('The relation ID'),
  );

  $form['settings']['message_param'] = array(
    '#type' => 'textfield',
    '#size' => '50',
    '#maxsize' => '50',
    '#title' => t('The message'),
    '#default_value' => $settings['message_param'],
    '#description' => t('The message'),
  );

}


/**
 * Action Implementation: Add a friend
 */
function rules_action_friendlist_add($settings) {
  $user1 = $settings['user1_param'];
  $user2 = $settings['user2_param'];
  $rtid = $settings['rtid_param'];
  $message = $settings['message_param'];
  #drupal_set_message("In the Action implementation (add): $user1, $user2, $rtid, $message");
  friendlist_api_relation_add($user1, $user2, $rtid, $message, 0);
}

/**
 * Form to delete a relation in FriendList.
 */
function rules_action_friendlist_delete_form($settings, &$form) {
  $settings += array('user1_param' => '', 'user2_param' => '', 'rtid_param' => '', 'message_param' => '');


  $form['settings']['user1_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '15',
    '#title' => t('User 1'),
    '#default_value' => $settings['user1_param'],
    '#description' => t('The user from which the relation will start'),
  );

  $form['settings']['user2_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '15',
    '#title' => t('User 2'),
    '#default_value' => $settings['user2_param'],
    '#description' => t('The user to which the relation will get'),
  );


  $form['settings']['rtid_param'] = array(
    '#type' => 'textfield',
    '#size' => '25',
    '#maxsize' => '25',
    '#title' => t('Relation type ID'),
    '#default_value' => $settings['rtid_param'],
    '#description' => t('The relation ID'),
  );

}

/**
 * Action Implementation: Delete a friend.
 */
function rules_action_friendlist_delete($settings) {
  $user1 = $settings['user1_param'];
  $user2 = $settings['user2_param'];
  $rtid = $settings['rtid_param'];
  #drupal_set_message("In the Action implementation (delete): $user1, $user2, $rtid, $message");
  friendlist_api_relation_delete($user1, $user2, $rtid, 0);
}



#######################################################################
#                          CONDITIONS
#######################################################################

/**
 * Implementation of hook_rules_condition_info().
 *
 * @ingroup rules
 */
function friendlist_rules_rules_condition_info() {
  return array(

    'rules_condition_relation_status_compare' => array(
      'label' => t('Compare with a status.'),
      'arguments' => array(

        'relation_status' => array(
          'label' => t('Relation status'),
          'type' => 'relation_status',
          'description' => 'The relation to compare'
        ),

      ),
      'help' => 'TRUE is returned if the relation status equals the string in the input box',
      'module' => 'Friendlist Rules',
    ),


    'rules_condition_relation_type_compare' => array(
      'label' => t('Compare with a relation type'),
      'arguments' => array(

        'relation_type' => array(
          'label' => t('Relation type'),
          'type' => 'relation_type',
          'description' => 'The relation type'
        ),

      ),

      'help' => 'TRUE is returned if the relation type matches',
      'module' => 'Friendlist Rules',
    ),

  );
}

/**
 * Action drupal message configuration form.
 */
function rules_condition_relation_status_compare_form($settings, &$form) {
  $settings += array('status_param' => '', );

  $options = array();
    $status_data = friendlist_api_status_data();
    foreach ($status_data as $key => $v) {
      $options[$key] = "$key -- ". t($v['description']);
    }


  $form['settings']['status_param'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t('Status'),
    '#default_value' => $settings['status_param'],
    '#description' => t('The status to compare it with'),
  );
}



/**
 * Condition Implementation: Relation Status comparison.
 */
function rules_condition_relation_status_compare($status, $settings) {
  $status_to_compare = $settings['status_param'];

  #drupal_set_message("Comparing: $status == $status_to_compare");
  return $status == $status_to_compare;
}

/**
 * Action drupal message configuration form.
 */
function rules_condition_relation_type_compare_form($settings, &$form) {
  $settings += array('relation_type_param' => '', );

  $options = array();
    $relation_types = friendlist_api_relation_types_load_all();
    $options = array();
    foreach ($relation_types as $relation_type) {
      $options[ $relation_type->rtid ] = $relation_type->rtid .' -- '. $relation_type->name;
    }

  $form['settings']['relation_type_param'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#title' => t('Relation type'),
    '#default_value' => $settings['relation_type_param'],
    '#description' => t('The relation_type to compare it with'),
  );
}


/**
 * Condition Implementation: Relation Type comparison.
 */
function rules_condition_relation_type_compare($rt, $settings) {
  $rt_to_compare = $settings['relation_type_param'];
  #drupal_set_message("Comparing $rt_to_compare == $rt ");
  return $rt_to_compare == $rt;
}

##################################################################
#                       EVENTS
##################################################################

/**
 * Implementation of hook_rules_event_info().
 *
 * @ingroup rules
 */
function friendlist_rules_rules_event_info() {
  return array(

    'friendlist_add' => array(
      'label' => t('User1 adds a relation to User2'),
      'module' => 'FriendList',
      'arguments' => array(
        'user1' => array('type' => 'user', 'label' => t('User1, which adds User2.')),
        'user2' => array('type' => 'user', 'label' => t('User2, which is added to User1\'s list.')),
        'rtid' => array('type' => 'relation_type', 'label' => t('The relation type id')),
        'message' => array('type' => 'relation_message', 'label' => t('The message sent to the user')),
        'status_pre' => array('type' => 'relation_status', 'label' => t('The status before the user gets added')),
        'status_post' => array('type' => 'relation_status', 'label' => t('The status once the user has been added')),
        'user_generated' => array('type' => 'boolean', 'label' => t('The action was generated by a live user')),
      ),
      'redirect' => TRUE,
    ),


    'friendlist_delete' => array(
      'label' => t('User1 deletes a relation to user2'),
      'module' => 'FriendList',
      'arguments' => array(
        'user1' => array('type' => 'user', 'label' => t('User1, which deletes User2.')),
        'user2' => array('type' => 'user', 'label' => t('User2, which is deleted to User1\'s list.')),
        'rtid' => array('type' => 'relation_type', 'label' => t('The relation type id')),
        'message' => array('type' => 'relation_message', 'label' => t('The message sent to the user')),
        'status_pre' => array('type' => 'relation_status', 'label' => t('The status before the user was deleted')),
        'status_post' => array('type' => 'relation_status', 'label' => t('The status once the user has been deleted')),
        'user_generated' => array('type' => 'boolean', 'label' => t('True if the action was generated by a live user')),
      ),
      'redirect' => TRUE,
    ),

  );
}

##################################################################
#                       TOKENS
##################################################################


/**
 * Implementation of hook_token_list().
 */
function friendlist_rules_token_list($type = 'all') {

  if ($type == 'relation_status') {
    $tokens['relation_status']['raw'] = t("The status in string form");
  }

  if ($type == 'relation_type') {
    $tokens['relation_type']['raw'] = t("The relation type in numeric form");
    $tokens['relation_type']['name'] = t("The relation type in string");
    $tokens['relation_type']['name_p'] = t("The relation type in string, plural");
  }

  if ($type == 'relation_message') {
    $tokens['relation_message']['string-raw'] = t("The raw string");
  }

  if ($type == 'boolean') {
    $tokens['boolean']['1-or-0'] = t("1 for true, 0 for FALSE");
  }

  return $tokens;
}



/**
 * Implementation of hook_token_values().
 */
function friendlist_rules_token_values($type, $object = NULL, $options = array()) {
  $values = array();
  switch ($type) {

    case 'relation_status':
      $values['raw'] = $object;
    break;

    case 'relation_type':
      $rt = friendlist_api_relation_type_load($object);
      $values['id'] = $rt->rtid;
      $values['name'] = $rt->name;
      $values['name_p'] = $rt->name_p;
    break;

    case 'boolean':
      $values['1-or-0'] = $object ?  '1' : '0' ;
      break;

  }
  return $values;
}

