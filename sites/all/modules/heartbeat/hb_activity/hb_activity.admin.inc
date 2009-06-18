<?php
// $Id: hb_activity.admin.inc,v 1.1.2.3 2008/12/28 22:52:49 stalski Exp $ 
// by Jochen Stals - ONE-agency - www.one-agency.be


/**
 * Function to maintain and administer specific settings
 *
 * @return settingsform
 */
function hb_activity_admin_settings() {
  $form['hb_fields'] = array(
    '#type' => 'fieldset',  
    '#weight' => -5,   
    '#title' => t('Heartbeat log settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE, 
  );
  $form['hb_fields']['hb_activity_no_duplicate_seconds'] = array(
    '#title' => t('Total timespan to show in heartbeat views'),
    '#type' => 'textfield',
    '#size' => 40,
    '#default_value' => variable_get('hb_activity_no_duplicate_seconds',172800),
    '#description' => t('You can set this to your needs. For example 36000 is 10h, 172800 is 24h'), 
    '#prefix' => '<div id="heartbeat-tabs">',
    '#suffix' => '</div>',
    '#ahah' => array(
      'path' => 'heartbeat/ahah/hb_activity_no_duplicate_seconds',
      'wrapper' => 'heartbeat-tabs',
      'event' => 'change',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['hb_fields']['hb_activity_grouping_seconds'] = array(
    '#title' => t('Maximum gap (in seconds)'),
    '#type' => 'textfield',
    '#size' => 40,
    '#default_value' => variable_get('hb_activity_grouping_seconds',7200),
    '#description' => t('Maximum gap for the same activity to be grouped together and before an identical activity can be logged again'),
    '#prefix' => '<div id="heartbeat-tabs-2">',
    '#suffix' => '</div>',
    '#ahah' => array(
      'path' => 'heartbeat/ahah/hb_activity_grouping_seconds',
      'wrapper' => 'heartbeat-tabs-2',
      'event' => 'change',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['hb_fields']['hb_activity_grouping_how_many'] = array(
    '#title' => 'Maximum number of items that can be grouped',
    '#type' => 'textfield',
    '#size' => 20,
    '#default_value' => variable_get('hb_activity_grouping_how_many',5)
  );
  
  $form['hb_fields']['heartbeat_block_items_max'] = array(
    '#title' => 'Maximum rows that are fetched from database',
    '#type' => 'textfield',
    '#size' => 20,
    '#default_value' => variable_get('heartbeat_block_items_max',100),
    '#description' => 'This is for performance reasons. Limiting the messages is calculated after grouping', 
  ); 
  $form['hb_fields']['heartbeat_block_public_items_max'] = array(
    '#title' => 'Maximum items in the public heartbeat',
    '#type' => 'textfield',
    '#size' => 20,
    '#default_value' => variable_get('heartbeat_block_public_items_max',25)
  ); 
  $form['hb_fields']['heartbeat_block_private_items_max'] = array(
    '#title' => 'Maximum items in the private heartbeat',
    '#type' => 'textfield',
    '#size' => 20,
    '#default_value' => variable_get('heartbeat_block_private_items_max',25)
  );   
  $form = system_settings_form($form);
  $form['#submit'][] = 'hb_activity_admin_settings_submit';
  return $form;
}

/**
 * submit callback for settings form
 *
 */
function hb_activity_admin_settings_submit($form, &$form_state) { 
  //$_SESSION['messages'] = array();
}

/**
* ahah callback
*/
function hb_activity_ahah($element) {
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);
  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form['#post'] = $_POST;
  $form['#redirect'] = FALSE;
  $form['#programmed'] = FALSE;
  $form_state['post'] = $_POST;
  drupal_process_form($form_id, $form, $form_state);
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);
  $javascript = drupal_add_js(NULL, NULL, 'header');
  $_SESSION['messages'] = array();
  if(isset($form['hb_fields'][$element])) {
	  $ahah_form = $form['hb_fields'][$element];
	  $date = _hb_activity_get_time($form_state['values'][$element]);
	  drupal_set_message(t('<strong>@days days @hours hours @minutes minutes @seconds seconds</strong>', $date));
    unset($ahah_form['#prefix'], $ahah_form['#suffix']); // Prevent duplicate wrappers.
	  drupal_json(array(
	    'status'   => TRUE,
	    'data'     => theme('status_messages') . drupal_render($ahah_form),
	    'settings' => call_user_func_array('array_merge_recursive', $javascript['setting']),
	  ));
  } 
	else {	  
    drupal_json(array(
      'status'   => FALSE,
      'data'     => t('Element not found: @element', array('@element' => $element)),
      'settings' => call_user_func_array('array_merge_recursive', $javascript['setting']),
    ));
	}
}

/**
 * Helper function to get a readable time
 */
function _hb_activity_get_time($time) {
  if(is_numeric($time)){
    $value = array(
      "@years" => 0, "@days" => 0, "@hours" => 0,
      "@minutes" => 0, "@seconds" => 0,
    );
    if($time >= 31556926){
      $value["@years"] = floor($time/31556926);
      $time = ($time%31556926);
    }
    if($time >= 86400){
      $value["@days"] = floor($time/86400);
      $time = ($time%86400);
    }
    if($time >= 3600){
      $value["@hours"] = floor($time/3600);
      $time = ($time%3600);
    }
    if($time >= 60){
      $value["@minutes"] = floor($time/60);
      $time = ($time%60);
    }
    $value["@seconds"] = floor($time);
    return (array) $value;
  }else{
    return (bool) FALSE;
  }
}