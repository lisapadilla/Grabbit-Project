<?php
// $Id: heartbeat.admin.inc,v 1.1.2.15.2.18 2009/02/22 20:59:53 stalski Exp $ 
// by Jochen Stals - ONE-agency - www.one-agency.be

/**
 * Function to maintain and administer heartbeat settings
 *
 * @return settingsform
 */
function heartbeat_admin_settings() {
  $form['heartbeat_enabled'] = array(
    '#title' => t('Do you want to enable the heatbeat logging'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('heartbeat_enabled',1)
  );
  $form['heartbeat_show_message_times'] = array(
    '#title' => t('Show the time of action in message displays'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('heartbeat_show_message_times',1)
  );
  $form['heartbeat_show_time_grouped_items'] = array(
    '#title' => t('Show the time of action with messages are grouped together'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('heartbeat_show_time_grouped_items',1)
  );
  return system_settings_form($form);
}

/**
 * Overview list of  heartbeat messages
 * This page must be viewed to make the messages 
 * appear in the database after a module is installed
 * as well as make them translatable 
 */
function heartbeat_messages_overview() {
  global $base_url;
  
  // Clear the rules cache to avoid problems
  //rules_clear_cache(); // not needed anymore i guess
  
  $intro = '';
  
  $intro.= t('Go to !link to add your conditional actions to one of the existing events.',
    array('!link' => l('rules administration','admin/rules/trigger'))
  );
  
  // Invoke a hook function of contributed modules 
  // so that their messages are known in the database  
  $info = heartbeat_gather_messages();
  
  // Fetch the heartbeat_message objects
  $messages = heartbeat_messages('all',true,true);
 
  if(!empty($info)) {
    drupal_set_message(t('New messages were added to heartbeat.'));
  }
  if(count($messages) <= 0) {
    return t('Sorry, no heartbeat messages yet');
  }
  $languages = module_exists('locale') ? locale_language_list() : array();
  foreach ($messages as $message) {     
    // Additional things to do if messages need to be translatable
    if($languages != array()) {
      // Pretend we are showing the strings to translate  
      // Mis-usage of the t-function, but how could i fix this?
      $fake_message = t($message->message);
      $fake_message_concat = t($message->message_concat);
      $message->description .= '</div>';
      // Show the admin user that there are things that need translation
      $report = array();
      foreach($languages as $lang => $human_language) {
	      if($lang != 'en') { 
	        // Look into the messages
	        if( locale($message->message, $lang) == locale($message->message,  'en')) { 
	          $label = t('@human_language translation',array('@human_language' => strip_tags($human_language)));         
		        $options = array('query' => 'op=Search&string='.str_replace(" ","+",$message->message));
		        $report[] = l($label, 'admin/build/translate/search', $options);
	        }
          // Look into the message_concat groupings
	        /*if(t($message->message_concat, array(), $lang) == t($message->message_concat, array(), 'en')) {       
            $label = t('@human_language translation',array('@human_language' => strip_tags($human_language)));         
            $options = array('query' => 'op=Search&string='.str_replace(" ","+",$message->message_concat));
            $report[] =  l($label, 'admin/build/translate/search', $options);
          }*/          
	      }
      } 
      // Add a report of todo translations to the list
      if($report != array()) {
        $message->description .= '<div><small>'.implode(', ', $report).'</small></div>';
      }
    } 
    $rows[] = array(
      $message->description,
      $message->module,
      $message->message_type,
      $message->karma_index,
      l( t('edit'), $base_url."/admin/build/heartbeat/edit/". $message->hid, array('query'=> 'destination=admin/build/heartbeat/list')) . ' - '.
      l( t('delete'),$base_url."/admin/build/heartbeat/delete/". $message->hid, array('query'=> 'destination=admin/build/heartbeat/list'))
     );
  }
  $headers = array(
    t('Description'),
    t('Module'), 
    t('Message type'), 
    t('Karma index'), 
    t('Operations')
  );
  
  if(module_exists('locale')) {
    $intro.= t('<blockquote>The messages are passed to the t-function when parsed to view.</blockquote>
    <p>This means that once they are viewed, they are available for you to translate.
    Altering these messages will clear the rules cache and the altered message 
    will need translation if you are dealing with a multilingual site. 
    The links show only the untranslated messages.</p>');
  }  
  return $intro. theme('table', $headers, $rows);  
}

/**
 * Function to delete a heartbeat message
 */
function heartbeat_messages_delete($hid) {
  global $base_url;
  $result = db_query("DELETE FROM {heartbeat_messages} WHERE hid = %d LIMIT 1", $hid);
  if (isset($_REQUEST['destination'])) {
    drupal_set_message(t('Message deleted'));
    drupal_goto($base_url.'/'.urlencode($_REQUEST['destination']));
  }
}


/**
 * Function to maintain and administer heartbeat messages
 *
 * @return settingsform
 */
function heartbeat_messages_add(&$form_state, $edit = array()) {
  return heartbeat_messages_edit($form_state, 0,$edit);
}

/**
 * Function to maintain and administer heartbeat messages
 *
 * @return settingsform
 */
function heartbeat_messages_edit(&$form_state, $hid=0,$edit = array()) {
  $form = array();
  if($hid) {
	  // Get messages
	  $result = db_query("SELECT * FROM {heartbeat_messages} WHERE hid = %d LIMIT 1", $hid);
	  $message = db_fetch_object($result);
	  // concat args , if merging is set  
	  $concat_args = heartbeat_decode_message_variables($message->concat_args);
	  if(!empty($concat_args)) {
	    $message->concat_args = array();
	    foreach($concat_args as $arg => $value) {
	      $message->concat_args[$arg] = $value;
	    }
	  }
  }
  else {
    $message = new StdClass();
  }
  $form['intro'] = array(
    '#type' => 'fieldset',
    '#title' => t('Information'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,  
    '#prefix' => '<p><strong>You can choose and use your own variables in your messages.</strong></p>', 
  );  
  
  $form['intro']['message_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Unique but descriptive message id'),
    '#description' => t('Example "heartbeat_add_content" in the format heartbeat_do_something.'),
    '#default_value' => empty($edit['message_id']) ? $message->message_id : $edit['message_id'],
    '#disabled' => $hid ? TRUE : FALSE,
  );
  $form['intro']['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description of the message'),
    '#description' => t('(most of the time you already have an event in mind)'),
    '#cols' => 60,
    '#rows' => 2,
    '#default_value' => empty($edit['description']) ? $message->description : $edit['description'],
  );
  $module_list = module_list();
  asort($module_list);
  $form['intro']['module'] = array(
    '#type' => 'select',
    '#title' => t('Module to filter in views'),
    '#options' => $module_list,
    '#default_value' => empty($edit['module']) ? $message->module : $edit['module'],
  );  
  $form['intro']['message_type'] = array(
    '#type' => 'select',
    '#title' => t('Type of the message and can be used as a filter in views'),
    '#options' => heartbeat_get_message_types(),
    '#default_value' => empty($edit['message_type']) ? $message->message_type : $edit['message_type'], 
    '#ahah' => array(
      'path' => 'heartbeat/message_types/js',
      'wrapper' => 'heartbeat-type-messages',
      'event' => 'change',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );  
  
  // Examples with variables
  $form['examples'] = array(
    '#type' => 'fieldset',
    '#title' => t('Variable information'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,  
  );  
  // variables
  $form['examples']['tokens']['#type'] = 'markup';
  $form['examples']['tokens']['#value'] = '<p>'.t('Here are a few examples of usage of variables in heartbeat messages:').'</p><blockquote>';
  $form['examples']['tokens']['#value'] .= '<small>'.t('!username has updated !node_title').'</small><br />';
  $form['examples']['tokens']['#value'] .= '<small>'.t('!username has added %node_titles%').'</small><br />';

  // Extended example, specific to a good module: friendlist
  if(module_exists('friendlist_api')) {
    $form['examples']['tokens']['#value'] .= '<small>'.t('!username1 is now !relation_type with !username2').'</small><br />';
  }
  $form['examples']['tokens']['#value'] .= '</blockquote><p>'.t('Always append your variables with ! or embed the word in %\'s to group several instances of one part of a message.').'</p>';
  
  // TEST
  //$tokens = token_get_values('global'); 
  //dsm($tokens);  
  
  $form['messages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Messages'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,  
    '#prefix' => '<div id="heartbeat-type-messages">',
    '#suffix' => '</div>',
  );
  
  if(isset($form_state['values']['message_type']) && in_array($form_state['values']['message_type'], array('flag') )) {
    $form['messages']['message'] = array(
      '#type' => 'textarea',
      '#title' => t('Single message'),
      '#cols' => 60,
      '#rows' => 2,
      '#default_value' => empty($edit['message']) ? $message->message : $edit['message'],
      '#description' => t('"!" is available to interpret a words as variables. For flag messages you must use !username and !username_target for the'),
    ); 
  }
  else {
    // the replacement of @ from # is only needed to view them like that. 
    // The actual implementation needs the # for partial message translations
    $form['messages']['message'] = array(
      '#type' => 'textarea',
      '#title' => t('Single message'),
      '#cols' => 60,
      '#rows' => 2,
      '#default_value' => empty($edit['message']) ? $message->message : $edit['message'],
      '#description' => t('"!" is available to interpret a words as variables.'),
    ); 
    $form['messages']['message_concat'] = array(
      '#type' => 'textarea',
      '#title' => t('Message when it is grouped or merged with other messages'),
      '#description' => t('You can use "%" to indicate that a variable word needs to be replaced with multiple instances of another variable (target variable). This is used when messages are merged together.<br />! is still available'),
      '#cols' => 60,
      '#rows' => 2,
      '#default_value' => empty($edit['message_concat']) ? $message->message_concat : $edit['message_concat'],
    );     
  }
  $form['features'] = array(
    '#type' => 'fieldset',
    '#title' => t('Extra features'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,  
  );
  $form['features']['karma_index'] = array(
    '#type' => 'select',
    '#title' => t('karma value for the event resulting to this message'),
    '#options' => drupal_map_assoc(variable_get('karma_indexes', array('1','5','10'))),
    '#required' => TRUE,
    '#default_value' => empty($edit['karma_index']) ? $message->karma_index : $edit['karma_index'],
  );
  $desc = t('Type of message when it comes to grouping and merging messages. <br />
  <strong>Single</strong> is when you want to repeat messages without merging them together.
  <strong>Count</strong> means you want to group the messages together so you know the number of times.
  A <strong>summary</strong> is when you want to list target variables with a separator and knowing 
  the number of times. ');
  $form['features']['type'] = array(
    '#type' => 'select',
    '#title' => t('Type of message (merging, grouping, standalone)'),
    '#suffix' => '<small>'.$desc.'</small>',
    '#options' => drupal_map_assoc(variable_get('heartbeat_types', array('single','summary','count'))),
    '#required' => TRUE,
    '#default_value' => empty($edit['type']) ? $message->concat_args['type'] : $edit['type'],
  );  
  $form['features']['merge'] = array(
    '#type' => 'checkbox',
    '#title' => t('Merge this message'),
    '#suffix' => '<small>'.t('If the same event happened more than once in the heartbeat views timespan, messages can be merged together if this option is set.').'</small>',
    '#required' => TRUE,
    '#default_value' => empty($edit['merge']) ? $message->merge : $edit['merge'],
  );  
  
  // These are fields that end up as concatenation arguments (concat_args)
  $form['features']['group_by'] = array(
    '#type' => 'select',
    '#options' => array('none'=>'','user'=>'user','node'=>'node','user-user'=>'user-user'),
    '#title' => t('Group by (only required for types summary and count)'),
    '#suffix' => '<small>'.t('Messages with parts that merge together are grouped by user or node. 
    E.g. Group by node if you want to summarize users and vice versa.<br />In some cases where the activity uses a relation 
    between two users, then set the group by to "user-user". A good example is a friend-relation.').'</small>',
    '#required' => FALSE,
    '#default_value' => empty($edit['group_by']) ? $message->concat_args['group_by'] : $edit['group_by'],
  );  
  $desc = t('<blockquote>
  Grouped message: !username added %images%.
  Single message: !username added an !image and a nice one.
  Then you will group by user and build a summary of images. The grouping variable here is "image". 
  </blockquote>');
  $form['features']['group_target'] = array(
    '#type' => 'textfield',
    '#title' => t('Group or merge variable'),
    '#suffix' => '<small>'.t('If you used a word between %-signs, you have to fill in the message variable you used that needs to be replaced with a summary.'). '<br /> e.g.:'.$desc.'</small>',
    '#required' => FALSE,
    '#default_value' => empty($edit['group_target']) ? $message->concat_args['group_target'] : $edit['group_target'],
  );
  
  $form['features']['merge_separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Fill in the target separator'),
    '#description' => t('Separators between the targets, like a colon. E.g. "title1<strong>,</strong> title2 and title3"'),
    '#required' => FALSE,
    '#default_value' => empty($edit['merge_separator']) ? $message->concat_args['merge_separator'] : $edit['merge_separator'],
  ); 
  $form['features']['merge_end_separator'] = array(
    '#type' => 'textfield',
    '#title' => t('Fill in the target end separator.'),
    '#description' => t('Separators finishing listed targets. E.g. "title1, title2 <strong>and</strong> title3"'),
    '#required' => FALSE,
    '#default_value' => empty($edit['merge_end_separator']) ? $message->concat_args['merge_end_separator'] : $edit['merge_end_separator'],
  ); 
  
  // Hidden elements
  $form['hid'] = array(
    '#type' => 'hidden',
    '#default_value' => empty($edit['hid']) ? $message->hid : $edit['hid'],
  ); 
  // Buttons
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
  if (isset($edit['hid'])) {
    $form['delete'] = array('#type' => 'submit', '#value' => t('Delete'));
  }
	  
  return $form;
}

/**
 * Accept the form submission to add messages.
 */
function heartbeat_messages_add_submit($form, &$form_state) {
  
  if($form_state['clicked_button']['#value'] != t('Save')) 
    return;
  if(!empty($form_state['values']['message']) && !empty($form_state['values']['description'])) {
	  $variables = array(
	    'type' => $form_state['values']['type'],
	    'group_by' => $form_state['values']['group_by'],
      'group_target' => $form_state['values']['group_target'],
	    'merge_separator' => $form_state['values']['merge_separator'],
	    'merge_end_separator' => $form_state['values']['merge_end_separator'],
	  );
    $concat_args = heartbeat_encode_message_variables($variables);
    $result = db_query("INSERT INTO {heartbeat_messages} SET message_id ='%s',message ='%s', message_concat ='%s', 
    karma_index = %d, message_type = '%s', merge = %d, description = '%s', module = '%s', concat_args = '%s', perms = '%s'  ",
    $form_state['values']['message_id'], $form_state['values']['message'], $form_state['values']['message_concat'], 
    $form_state['values']['karma_index'], $form_state['values']['message_type'], 
    $form_state['values']['merge'],$form_state['values']['description'], 
    $form_state['values']['module'], $concat_args, 1 );
    drupal_set_message(t('New message was added and can be used in actions of a rule'));  
    //dsm($result);
  }
  //$form_state['redirect'] = 'admin/settings/heartbeat/messages';
  return;
}


/**
 * Accept the form submission heartbeat messages to edit.
 */
function heartbeat_messages_edit_submit($form, &$form_state) {
  
  // Message_id's cannot be changed
  if($form_state['clicked_button']['#value'] == t('Save')) {      
    // Prepare message concatenation variables
    $variables = array(
      'type' => $form_state['values']['type'],
      'group_by' => $form_state['values']['group_by'],
      'group_target' => $form_state['values']['group_target'],
      'merge_separator' => $form_state['values']['merge_separator'],
      'merge_end_separator' => $form_state['values']['merge_end_separator'],
    );  
    $concat_args = heartbeat_encode_message_variables($variables);
    $result = db_query("UPDATE {heartbeat_messages} SET message ='%s', message_concat ='%s', 
    karma_index = %d, merge = %d, description = '%s', module = '%s' , concat_args = '%s' 
    WHERE hid = %d",
    $form_state['values']['message'], $form_state['values']['message_concat'], 
    $form_state['values']['karma_index'],  $form_state['values']['merge'],
    $form_state['values']['description'], $form_state['values']['module'],
    $concat_args,$form_state['values']['hid']);
    drupal_set_message(t('Settings saved'));  
  }
  //$form_state['redirect'] = 'admin/settings/heartbeat/messages';
  return;
}


/**
 * Callback function to add variables to the 
 *  user activity actions forms
 */
function hb_activity_rules_action_message_id_js() {
  // The form is generated in an include file which we need to include manually.
  include_once drupal_get_path('module', 'rules').'/rules.input_evaluators.inc';
  include_once drupal_get_path('module', 'rules').'/rules.admin.inc';  
  // We're starting in step #3, preparing for #4.
  $form_state = array('submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  // Step #4.
  $form = form_get_cache($form_build_id, $form_state);
  // Preparing for #5.
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;
  // Step #5.
  drupal_process_form($form_id, $form, $form_state);
  // Step #6 and #7 and #8.
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);  
  // Step #9.
  $hm_form = $form['settings']['variables_param'];
  unset($hm_form['#prefix'], $hm_form['#suffix']);
  $output = /*theme('status_messages') . */drupal_render($hm_form);
  // Updating the drupal settings to be able to do one ahah request after another
  $javascript = drupal_add_js(NULL, NULL, 'header');
  // Final rendering callback.
  drupal_json(array(
    'status' => TRUE, 
    'data' => $output,
    'settings' => call_user_func_array('array_merge_recursive', $javascript['setting'])
 ));  
}

/**
 * Function to export messages to use as default
 */
function heartbeat_messages_export($form_state=array()) {  
  $form = array();
  $messages = heartbeat_messages('all',true,true);
  if(count($messages) == 0) {
    return t('There are not heartbeat messages to export.');
  }
  if(!isset($form_state['export'])) { 
    $form['messages'] = array('#tree' => TRUE);
    foreach ($messages as $message) { 
      $form['messages']['m_'.$message->hid] = array(
        '#type' => 'checkbox',
        '#title' => $message->description,
        '#default_value' => 1,
        '#description' => $message->message,
      );
    }
    $form['button'] = array('#type' => 'submit', '#weight' => 10, '#value' => t('Export'));
  }
  else {
    //show a textarea containg the exported configs
    $form['result'] = array(
      '#type' => 'textarea',
      '#title' => 'Exported heartbeat messages',
      '#description' => 'Copy this data and paste them in <strong>hook_heartbeat_message_info</strong>.',
      '#rows' => 15,
      '#attributes' => array('readonly' => 'readonly'),
      '#default_value' => var_export(heartbeat_messages_export_messages($form_state['export']), 1),
    );
  }
  return $form;  
}

/**
 * Submit handler to stay on the same form and show a textbox
 *
 * @param array $form
 * @param array $form_state
 */
function heartbeat_messages_export_submit($form, &$form_state) {
  $count = 0;
  foreach($form_state['values']['messages'] as $key => $value) {
    $count += $value;
  }
  if($count) {
    $form_state['export'] = $form_state['values']['messages'];
    $form_state['rebuild'] = TRUE;
  }
}

/**
 * Function to export messages to use as default
 */
function heartbeat_messages_export_messages($selected_messages) {
  $messages = heartbeat_messages('all',true,false);
  if(count($messages) == 0) {
    return t('There are not heartbeat messages to export.');
  }
  $info = array();
  foreach ($messages as $message) {    
    $message = (object) $message;
    if(!$selected_messages['m_'.$message->hid]) {
      continue; // Leave if not selected
    } 
    $concat_args = heartbeat_decode_message_variables($message->concat_args); 
    $variables = heartbeat_decode_message_variables($message->variables);
    $info[$message->hid] = array(
      'message' => $message->message,
      'message_concat' => $message->message_concat,
      'message_id' => $message->message_id,
      'message_type' => $message->message_type,
      'concat_args' => $concat_args,
      'module' => $message->module,
      'karma_index' =>  $message->karma_index,
      'description' =>  $message->description,
      'variables' => $variables
    );
  }
  return $info;  
}

/**
 * Callback function to change the form of message
 */
function heartbeat_message_type_js() {
   // The form is generated in an include file which we need to include manually.
  //include_once drupal_get_path('module', 'rules').'/rules.input_evaluators.inc';
  //include_once drupal_get_path('module', 'rules').'/rules.admin.inc';  
  // We're starting in step #3, preparing for #4.
  $form_state = array('submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  // Step #4.
  $form = form_get_cache($form_build_id, $form_state);
  // Preparing for #5.
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;
  // Step #5.
  drupal_process_form($form_id, $form, $form_state);
  // Step #6 and #7 and #8.
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);  
  // Step #9.
  $hm_form = $form['messages'];
  unset($hm_form['#prefix'], $hm_form['#suffix']);
  $output = drupal_render($hm_form);
  // Updating the drupal settings to be able to do one ahah request after another
  $javascript = drupal_add_js(NULL, NULL, 'header');
  // Final rendering callback.
  drupal_json(array(
    'status' => TRUE, 
    'data' => $output,
    'settings' => call_user_func_array('array_merge_recursive', $javascript['setting'])
 ));  
}

/**
 * Menu callback: confirm deleting of logs.
 */
function heartbeat_delete_logs_confirm() {
  return confirm_form(
    array(), 
    t('Are you sure you want to delete all activity logs?'),
    'admin/settings/heartbeat/delete/confirm', 
    t('This action can not be undone.'), 
    t('Delete'), 
    t('Cancel')
  );
}

/**
 * Handler for wipe confirmation
 */
function heartbeat_delete_logs_confirm_submit($form, &$form_state) {
  db_query("DELETE FROM {hb_activity}");
  $form_state['redirect'] = 'admin/settings/heartbeat/settings';
  drupal_set_message('All messages have been deleted');
}
