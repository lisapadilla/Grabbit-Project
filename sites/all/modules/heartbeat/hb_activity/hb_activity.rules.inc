<?php 
// $Id: hb_activity.rules.inc,v 1.1.2.2 2008/12/28 22:52:49 stalski Exp $ 
// by Jochen Stals - ONE-agency - www.one-agency.be


# DATA TYPES


/**
* Rules heartbeat activity message data type
*/
class rules_data_type_heartbeat_message extends rules_data_type {
  /**
   * Gets the input form for the data
   * Implement it, if your data is not identifiable.
   */
  function get_default_input_form($info, $value) {
    $info += array('long' => FALSE, 'required' => TRUE, 'description' => '');
    return array(
      '#type' => $info['long'] ? 'textarea' : 'textfield',
      '#title' => $info['label'],
      '#description' => $info['description'],
      '#required' => $info['required'],
      '#default_value' => $value,
    );
  }
}

/**
* Rules heartbeat activity message data type
*/
class rules_data_type_heartbeat_message_id extends rules_data_type_heartbeat_message {
  function check_value($info, $value) {
    return (float)$value;
  }
}

/**
* Rules heartbeat activity message data type
*/
class rules_data_type_heartbeat_access extends rules_data_type_heartbeat_message {
  function check_value($info, $value) {
    return (float)$value;
  }
}

/**
* Implementation of hook_rules_data_type_info()
*/
function hb_activity_rules_data_type_info() {
  return array(
    'heartbeat_message' => array(
      'label' => t('logged heartbeat message in the most basic form'),
      'class' => 'rules_data_type_heartbeat_message',
      'identifiable' => FALSE,
      'eval input' => TRUE,
    ),
    'heartbeat_message_id' => array(
      'label' => t('heartbeat message id'),
      'class' => 'rules_data_type_heartbeat_message_id',
      'identifiable' => FALSE,
      'eval input' => TRUE,
    ),
    'heartbeat_access' => array(
      'label' => t('heartbeat message access'),
      'class' => 'rules_data_type_heartbeat_access',
      'identifiable' => FALSE,
      'eval input' => TRUE,
    ),
  );
}



# EVENTS

/**
* Implementation of hook_rules_event_info().
* @ingroup rules
*/
function heartbeat_rules_event_info() {
  return array(
    'heartbeat_flag_post' => array(
      'label' => t('User posts a new flag message'),
      'module' => 'heartbeat',
      'arguments' => array(
        'user' => array(
          'type' => 'user', 
          'label' => t('User who posts a new shout.')
        ),
        'flagged_user' => array(
          'type' => 'user', 
          'label' => t('Flag user.')
        ),
        'message_id' => array(
          'type' => 'rules_data_type_heartbeat_message_id', 
          'label' => t('Message id.'),
		      /*'arguments' => array(
		        'accounnee' => array('type' => 'user', 'label' => t('logged in user')),
		      ),*/
        ),
        'access' => array(
          'type' => 'rules_data_type_heartbeat_access', 
          'label' => t('Message access.')
        ),
      ),
      'redirect' => TRUE,
    ),
  );
}



# ACTIONS


/**
 * Implementation of hook_rules_action_info().
 * @ingroup rules
 */
function hb_activity_rules_action_info() {  
  $info = array(
  
    // Base action to execute as default user activity logs
    'hb_activity_rules_default_action' => array(
      'label' => t('Logs user activity for single users'),
      'eval input' => array(
        'uid_param',
        'uid_target_param',
        'nid_target_param',
        'message_id_param',
        'variables_param'
      ),
      'help' => 'Create a relation between a user and others when handling content(node or comment).',
      'module' => 'heartbeat',
    ),
    
    // Simplified action to execute user-to-user activity logs
    'hb_activity_rules_users_action' => array(
      'label' => t('Logs default user activity between users'),
      'eval input' => array(
        'uid_param',
        'uid_target_param',
        'message_id_param',
        'variables_param'
      ),
      'help' => 'Create a relation between a user and another user.',
      'module' => 'heartbeat',
    ),
  
    // Action to execute for user activity with flagged messages
    'heartbeat_flag_rules_action' => array(
      'label' => t('Logs relational user activity when flagging a user'),
      'eval input' => array(
        'uid_param',
        'uid_target_param',
        'message_id_param',
        'access_param',
        'variables_param'
      ),
      'help' => 'Logs relational user activity when flagging a user',
      'module' => 'heartbeat',
    ),
  );
  return $info;
}

/**
 * Action drupal message configuration form.
 */
function hb_activity_rules_default_action_form($settings, &$form, $form_state) {
  // Ahah is in the form, so cache it
  $form['#cache'] = TRUE;
  
  // Add the default empty values to the settings hash
  $settings += array(
    'uid_param' => '', 
    'uid_target_param' => '', 
    'nid_target_param' => '', 
    'message_id_param' => '', 
    'variables_param' => ''
  );
  $form['settings']['uid_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '25',
    '#title' => t('User'),
    '#default_value' => $settings['uid_param'],
    '#description' => t('The user doing the activity. Think well about who is the acting user for content related events. Is it the currently logged-in user or the author of the content.'),
    '#weight' => -5,
  );
  $form['settings']['uid_target_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '25',
    '#title' => t('User target'),
    '#default_value' => $settings['uid_target_param'],
    '#description' => t('The user target of the activity'),
    '#weight' => -4,
  );
  $form['settings']['nid_target_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '25',
    '#title' => t('Node target'),
    '#default_value' => $settings['nid_target_param'],
    '#description' => t('The node target of the activity'),
    '#weight' => -3,
  );
  $messages = heartbeat_messages('all',false,false);
  $options = array(0 => t('No message selected'));
  foreach($messages as $message) {  
    $options[$message['message_id']] = $message['description'];
  }    
  // Choose a message and addin ahah behavior to show variables
  $form['settings']['message_id_param'] = array(
    '#type' => 'select',
    '#title' => t('Choose a message'),
    '#default_value' => empty($settings['message_id_param']) ? 0 : $settings['message_id_param'],
    '#options' => $options,
    '#weight' => -2,
    '#description' => t('The message'),
    '#submit' => array('hb_activity_rules_action_message_id_submit'), // If no javascript action.
    '#ahah' => array(
      'path' => 'heartbeat/hb_activity_rules_default/js',
      'wrapper' => 'message-variables',
      'event' => 'change',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  ); 
  // Add a wrapper for the variables section.
  $form['settings']['message_id_wrapper'] = array(
    '#type' => 'markup',
    '#weight' => -1,
    '#prefix' => '<div class="clear-block" id="heartbeat-wrapper"><div id="message-variables">',
    '#suffix' => '</div></div>',
    '#value' => '',
  );
  // Show variables if message_id_param is set
  //dsm($form_state);
  if(!empty($form_state['values']['settings']['message_id_param']) ) {
    // With the message id, we fetch the whole message
    $heartbeat_message_id = $form_state['values']['settings']['message_id_param'];
    $message = heartbeat_load_message($heartbeat_message_id);
    $defined_variables = heartbeat_match_variables($message->message, $message->message_concat);
    // If words are found as match to a heartbeat message variable,
    // variables are needed in the message
    if(count($defined_variables['words']) > 0) {
      
      // Add the textarea where all the magic variables go into
	    $description = t('Variables are supported to build heartbeat messages at all time from a log.<br />
	    The syntax you must use for this is simple. You give your variable you want to use, 
	    prefixed by @ or #. (# is for variables that need to be pretranslated)
	    <br />Assign your variable to a token available from the token replacement list, 
	    and assign it with the "=".<br /><strong>Note! One variable assignment per line and no colons as assignment because colons are in the tokens as well.</strong>');
	    
      $default_values = heartbeat_variables_compare($settings, $form_state['values']['variables_param'], $defined_variables['words']);
      
		  // Container for just the message variables
		  $form['settings']['variables_param'] = array(
		    '#type' => 'textarea',
		    '#title' => t('Assign a token to each of these variables used in the selected message'),
		    '#suffix' => '<small>'.$description.'</small>',
		    '#default_value' => $default_values,
        '#cols' => 60,
        '#rows' => 5,
		    '#prefix' => t('<strong>Message</strong>: <em>@message</em>', array('@message'=>$message->message)),
		    '#required' => TRUE
		  );      
    }
  } 
  // Show default information on how variables will appear
  else {
    $form['settings']['message_id_wrapper']['variables_info'] = array(
      '#type' => 'markup',
      '#value' => t('Variables in the chosen message will appear here. Assign them to a token, available for this type of event.'),
    );    
  }
}

/**
 * Action drupal message configuration form. 
 * 
 * @desc Update heartbeat_messages to synchronize,
 * and avoid separate versions of messages and message_concats
 */
function hb_activity_rules_default_action_submit(&$settings, $form, $form_state) {  
  //  dsm(func_get_args());
  $params = $form_state['values']['settings'];    
  $vars = $params['variables_param'];
  $vars = eregi_replace("\r\n", "-|-",$vars);
  $vars = eregi_replace("=", "=|=",$vars);
  $settings['variables_param'] = $vars;
  db_query("UPDATE {heartbeat_messages} SET variables = '%s' WHERE message_id = '%s'", $vars, $params['message_id_param']);    
}

/**
 * Action Implementation: Log an activity
 *   Default action for most common heartbeat message activities
 *
 * @param array $settings
 * @param array form
 * @param array with two arrays (set_info and variables)
 * @ToDo  figure out what params mean / can do
 */
function hb_activity_rules_default_action($settings, $form=array(), $event_info=array()){  
  //dsm($message);
	$data = array();
  if(is_array($settings)) {
    // Normal form values
	  $data['uid'] = $settings['uid_param'];
	  $data['uid_target'] = $settings['uid_target_param'];
	  $data['nid_target'] = $settings['nid_target_param'];
    $data['message_id'] = $settings['message_id_param'];
    // Relational message of heartbeat messages
	  $message = heartbeat_load_message($data['message_id']);	  
    $data['message'] = $message->message;
    $data['message_concat'] = $message->message_concat;
	  $data['variables'] = $settings['variables_param'];
  }
  hb_activity_log($data); 
}

/**
 * User action drupal message configuration form.
 */
function hb_activity_rules_users_action_form($settings, &$form, $form_state) {
  // Ahah is in the form, so cache it
  $form['#cache'] = TRUE;
  
  // Add the default empty values to the settings hash
  $settings += array(
    'uid_param' => '', 
    'uid_target_param' => '', 
    'message_id_param' => '', 
    'variables_param' => ''
  );
  $form['settings']['uid_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '25',
    '#title' => t('User'),
    '#default_value' => $settings['uid_param'],
    '#description' => t('The user doing the activity. Think well about who is the acting user for content related events. Is it the currently logged-in user or the author of the content.'),
    '#weight' => -5,
  );
  $form['settings']['uid_target_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '25',
    '#title' => t('User target'),
    '#default_value' => $settings['uid_target_param'],
    '#description' => t('The user target of the activity'),
    '#weight' => -4,
  );
  $messages = heartbeat_messages('all',false,false);
  $options = array(0 => t('No message selected'));
  foreach($messages as $message) {  
    $options[$message['message_id']] = $message['description'];
  }
  // Choose a message and addin ahah behavior to show variables
  $form['settings']['message_id_param'] = array(
    '#type' => 'select',
    '#title' => t('Choose a message'),
    '#default_value' => empty($settings['message_id_param']) ? 0 : $settings['message_id_param'],
    '#options' => $options,
    '#weight' => -2,
    '#description' => t('The message'),
    '#submit' => array('hb_activity_rules_action_message_id_submit'), // If no javascript action.
    '#ahah' => array(
      'path' => 'heartbeat/hb_activity_rules_default/js',
      'wrapper' => 'message-variables',
      'event' => 'change',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  ); 
  // Add a wrapper for the variables section.
  $form['settings']['message_id_wrapper'] = array(
    '#type' => 'markup',
    '#weight' => -1,
    '#prefix' => '<div class="clear-block" id="heartbeat-wrapper"><div id="message-variables">',
    '#suffix' => '</div></div>',
    '#value' => '',
  );
  // Show variables if message_id_param is set
  //dsm($form_state);
  if(!empty($form_state['values']['settings']['message_id_param']) ) {
    // With the message id, we fetch the whole message
    $heartbeat_message_id = $form_state['values']['settings']['message_id_param'];
    $message = heartbeat_load_message($heartbeat_message_id);
    $defined_variables = heartbeat_match_variables($message->message, $message->message_concat);
    // If words are found as match to a heartbeat message variable,
    // variables are needed in the message
    if(count($defined_variables['words']) > 0) {
      
      // Add the textarea where all the magic variables go into
      $description = t('Variables are supported to build heartbeat messages at all time from a log.<br />
      The syntax you must use for this is simple. You give your variable you want to use, 
      prefixed by @ or #. (# is for variables that need to be pretranslated)
      <br />Assign your variable to a token available from the token replacement list, 
      and assign it with the "=".<br /><strong>Note! One variable assignment per line and no colons as assignment because colons are in the tokens as well.</strong>');
      
      $default_values = heartbeat_variables_compare($settings, $form_state['values']['variables_param'], $defined_variables['words']);
      
      // Container for just the message variables
      $form['settings']['variables_param'] = array(
        '#type' => 'textarea',
        '#title' => t('Assign a token to each of these variables used in the selected message'),
        '#suffix' => '<small>'.$description.'</small>',
        '#default_value' => $default_values,
        '#cols' => 60,
        '#rows' => 5,
        '#prefix' => t('<strong>Message</strong>: <em>@message</em>', array('@message'=>$message->message)),
        '#required' => TRUE
      );      
    }
  } 
  // Show default information on how variables will appear
  else {
    $form['settings']['message_id_wrapper']['variables_info'] = array(
      '#type' => 'markup',
      '#value' => t('Variables in the chosen message will appear here. Assign them to a token, available for this type of event.'),
    );    
  }
}

/**
 * Action drupal message configuration form. 
 * 
 * @desc Update heartbeat_messages to synchronize,
 * and avoid separate versions of messages and message_concats
 */
function hb_activity_rules_users_action_submit(&$settings, $form, $form_state) {  
  hb_activity_rules_default_action_submit($settings, $form, $form_state);
}

/**
 * Action Implementation: Log an activity
 *   between two users
 *
 * @param array $settings
 * @param array form
 * @param array with two arrays (set_info and variables)
 * @ToDo  figure out what params mean / can do
 */
function hb_activity_rules_users_action($settings, $form=array(), $event_info=array()){  
  //dsm($message);
  $data = array();
  if(is_array($settings)) {
    // Normal form values
    $data['uid'] = $settings['uid_param'];
    $data['uid_target'] = $settings['uid_target_param'];
    $data['nid_target'] = 0;
    $data['message_id'] = $settings['message_id_param'];
    // Relational message of heartbeat messages
    $message = heartbeat_load_message($data['message_id']);   
    $data['message'] = $message->message;
    $data['message_concat'] = $message->message_concat;
    $data['variables'] = $settings['variables_param'];
  }
  hb_activity_log($data); 
}


/**
 * Flag action form.
 */
function heartbeat_flag_rules_action_form($settings, &$form, $form_state) {
  // Ahah is in the form, so cache it
  
  // Add the default empty values to the settings hash
  $settings += array(
    'uid_param' => '', 
    'uid_target_param' => '', 
    'message_id_param' => 0, 
    'access_param' => 0, 
    'variables_param' => ''
  );
  $form['settings']['uid_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '25',
    '#title' => t('User'),
    '#default_value' => $settings['uid_param'],
    '#description' => t('The user doing the activity. Think well about who is the acting user for content related events. Is it the currently logged-in user or the author of the content.'),
    '#weight' => -5,
  );
  $form['settings']['uid_target_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '25',
    '#title' => t('User target'),
    '#default_value' => $settings['uid_target_param'],
    '#description' => t('The user target of the activity'),
    '#weight' => -4,
  ); 
  // Choose a message and addin ahah behavior to show variables
  $form['settings']['message_id_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '60',
    '#title' => t('Message chosen by user (token)'),
    '#default_value' => empty($settings['message_id_param']) ? '' : $settings['message_id_param'],
    '#description' => t('The flagged message choosen by the user'),
    '#weight' => -4,
  ); 
  $form['settings']['access_param'] = array(
    '#type' => 'textfield',
    '#size' => '15',
    '#maxsize' => '60',
    '#title' => t('Access chosen by user (token)'),
    '#default_value' => empty($settings['access_param']) ? '' : $settings['access_param'],
    '#description' => t('The flagged message access choosen by the user'),
    '#weight' => 2,
  ); 
  // load 
  $defined_variables = array(
    '@username' => '',
    '@username_target'=> ''
  );
  //dsm($settings);
  $default_values = heartbeat_variables_compare($settings, null, $defined_variables, false);
  // Container for just the message variables
  $form['settings']['variables_param'] = array(
    '#type' => 'textarea',
    '#title' => t('Assign a token to each of these variables used in the selected message'),
    '#description' => t('fill in the token for each of the variables used in flag messages'),
    '#default_value' => $default_values,
    '#cols' => 60,
    '#rows' => 5,
    '#required' => TRUE
  );  
}

/**
 *  Flag action submission. 
 * 
 * @desc Update heartbeat_messages to synchronize,
 * and avoid separate versions of messages and message_concats
 */
function heartbeat_flag_rules_action_submit(&$settings, $form, $form_state) {  
  //  dsm(func_get_args());
  $params = $form_state['values']['settings'];    
  $vars = $params['variables_param'];
  $vars = eregi_replace("\r\n", "-|-",$vars);
  $vars = eregi_replace("=", "=|=",$vars);
  $settings['variables_param'] = $vars;
  db_query("UPDATE {heartbeat_messages} SET variables = '%s' WHERE message_type = 'flag'", $vars);    
}

/**
 *  Flag action.
 *
 * @param array $settings
 * @param array form
 * @param array with two arrays (set_info and variables)
 * @ToDo  figure out what params mean / can do
 */
function heartbeat_flag_rules_action($settings, $form=array(), $event_info=array()){  
  //dsm($event_info['variables']['access']);
  $data = array();
  if(is_array($settings)) {
    // Normal form values
    $data['uid'] = $settings['uid_param'];
    $data['uid_target'] = $settings['uid_target_param'];
    $data['access'] = $settings['access_param'];
    $data['message_id'] = $settings['message_id_param'];
    // Relational message of heartbeat messages
    $message = heartbeat_load_message($data['message_id']);    
    $data['message'] = $message->message;
    $data['message_concat'] = $message->message_concat;
    $data['variables'] = $settings['variables_param'];
  }
  hb_activity_log($data); 
}


# CONDITIONS

/**
 * Implentation of hook_rules_conditions_info().
 */
function hb_activity_rules_condition_info() {
  // example code here
}

