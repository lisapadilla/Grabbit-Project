<?php
// $Id: dcl_importer.form.inc,v 1.1.2.2 2009/08/28 23:42:25 hadsie Exp $

/**
 * The main importer (simple) form.
 */
function dcl_importer_simple_form($form_state) {
  // Which "step" are we on?
  $button = $form_state['clicked_button']['#dcl_button'];

  // Build the provider selection form.
  $form['info'] = array(
    '#value' => '<strong>' . t('Import contacts from your existing social networking accounts and email address books.') . '</strong>',
  );

  $form['import_form'] = array(
    '#tree' => FALSE,
    '#prefix' => '<div id="dcl-importer-import-form">',
    '#suffix' => '</div>',
  );

  _dcl_importer_form_provider($form, $form_state);

  if ($button == 'provider') {// || $form_state['storage']['provider']) {
    // The provider has been selected, so render the input form.
    $module = $form_state['storage']['engine']['module'];
    _dcl_importer_load_engine_form($form, $form_state, $module);
    $form['import_form']['submit']['#dcl_button'] = 'import_contacts';
  }

  $imported_emails = $form_state['storage']['imported_emails'];
  if ($button == 'import_contacts' && $imported_emails) {
    // The "Get Contacts" button was pressed, so let's render the contacts
    list($new, $existing) = dcl_importer_api_split_users($imported_emails);
    list($new, $existing) = _dcl_importer_session_contacts($new, $existing);
    _dcl_importer_form_contacts($form, $form_state, $new, $existing);
  }

  return $form;
}

/**
 * The main importer (advanced) form.
 */
function dcl_importer_advanced_form($form_state) {
  $form = array();
  ahah_helper_register($form, $form_state);

  $button = $form_state['clicked_button']['#dcl_button'];

  _dcl_importer_form_tabs($form, $form_state);
  
  $selected_provider = $form_state['clicked_button']['#provider'];
  if ($selected_provider == 'other' && $button != 'imported_contacts') {
    _dcl_importer_form_provider($form, $form_state);
    $selected_provider = NULL;
  }
  else {
    $form['import_form']['provider'] = array(
      '#type' => 'value',
      '#value' => $selected_provider,
    );
  }
  
  if ($selected_provider && $button != 'imported_contacts') {
    $engine = dcl_importer_api_get_engine($selected_provider);
    _dcl_importer_load_engine_form($form, $form_state, $engine['module']);

    $form['import_form']['submit']['#ahah'] = array(
      'path' => ahah_helper_path(array('contacts')),
      'wrapper' => 'dcl-importer-import-form',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type' => 'none'),
    );
    $form['import_form']['submit']['#dcl_button'] = 'import_contacts';
    $form['import_form']['submit']['#submit'][] = 'ahah_helper_generic_submit';
  }

  $form['contact_list_wrapper'] = array(
    '#value' => '<div id="dcl-importer-import-form"><div id="dcl-importer-provider-import-form"></div></div>',
  );

  $imported_emails = $form_state['storage']['imported_emails'];
  if ($button == 'import_contacts' && $imported_emails) {
    list($new, $existing) = dcl_importer_api_split_users($imported_emails);
    list($new, $existing) = _dcl_importer_session_contacts($new, $existing);
  }
  else {
    $new = unserialize($_SESSION['dcl_contacts_new']);
    $existing = unserialize($_SESSION['dcl_contacts_existing']);
  }

  if ($new || $existing) {
    $form['contacts_raw'] = array(
      '#type' => 'value',
      '#value' => array(
        'new' => $new,
        'existing' => $existing,
      ),
    );
    
    _dcl_importer_form_contacts($form, $form_state, $new, $existing);
  }

  return $form;
}

/**
 * The dcl importer form submit callback.
 * The submit function here performs different actions depending on the step.
 *   1. Load the appropriate engine (based on the specified provider)
 *   2. Load all of the contacts and run the submit callback on them.
 */
function dcl_importer_form_submit($form, &$form_state) {
	
  $button = $form_state['clicked_button']['#dcl_button'];
  if ($button == 'provider') {
    $engine = dcl_importer_api_get_engine($form_state['values']['provider']);
    $form_state['storage']['provider'] = $form_state['values']['provider'];
    $form_state['storage']['engine'] = $engine;
  }
  elseif ($button == 'invite_contacts') {
    $redir = _dcl_importer_invoke_import_action('submit', $form, $form_state);
    if (!empty($redir)) {
      unset($form_state['storage']);
      $form_state['redirect'] = $redir[0];
    }
  }
  elseif ($button == 'cancel') {
    unset($_SESSION['dcl_contacts_new']);
    unset($_SESSION['dcl_contacts_existing']);
    unset($form_state['storage']);
  }
}

/**
 * Build the tabs form component
 */
function _dcl_importer_form_tabs(&$form, &$form_state) {
  $providers = dcl_importer_api_get_providers();
  $providers = _dcl_importer_clean_provider_list($providers);

  $form['tabs'] = array();
  $tab_definition = array(
    '#type' => 'button',
    '#button_type' => 'button',
    '#value' => 'Import from !provider',
    '#attributes' => array('class' => 'provider-button'),
    '#dcl_button' => 'provider',
    '#ahah' => array(
      'path' => ahah_helper_path(array('import_form')),
      'wrapper' => 'dcl-importer-provider-import-form',
      'method' => 'replace',
      'effect' => 'fade',
      'progress' => array('type' => 'none'),
    ),
    '#submit' => array('ahah_helper_generic_submit'),
  );

  foreach (variable_get('dcl_importer_providers', NULL) as $provider) {
    if (!$provider) {
      continue;
    }
    $form['tabs'][$provider] = $tab_definition;
    $form['tabs'][$provider]['#value'] =
      t($tab_definition['#value'], array('!provider' => $providers[$provider]));
    $form['tabs'][$provider]['#provider'] = $provider;
  }
  
  $form['tabs']['other'] = $tab_definition;
  $form['tabs']['other']['#value'] = t('Other Providers');
  $form['tabs']['other']['#provider'] = 'other';
  
  $form['tabs_border'] = array(
    '#value' => '<div class="provider-buttons-border"></div>',
  );
}

/**
 * Build the provider selection form component
 */
function _dcl_importer_form_provider(&$form, &$form_state) {
  $provider_priority = variable_get('dcl_importer_providers', array());
  $default_provider = NULL;
  if (!empty($provider_priority)) {
    $default_provider = $provider_priority[0];
  }
  
  $providers = dcl_importer_api_get_providers();
  $form['import_form']['provider'] = array(
    '#type' => 'select',
    '#title' => t('Service Provider'),
    '#default_value' => $default_provider,
    '#options' => _dcl_importer_clean_provider_list($providers),
    '#required' => TRUE,
    '#description' =>  t('The service provider that is hosting your contacts'),
    '#dcl_button' => 'provider',
  );

  // If there's exactly one engine available then we can
  // include the engine form in the first step. We don't need to worry about
  // different import forms.
  $engines = dcl_importer_api_engines();
  if (count($engines) == 1) {
    $engines = array_keys($engines);
    $module = $engines[0];
  }
  else {
    // Add ahah functionality since we'll need to switch between forms
    $form['import_form']['provider']['#ahah'] = array(
      'path' => 'dcl_importer/js',
      'wrapper' => 'dcl-importer-import-form',
      'method' => 'prepend',
      'effect' => 'fade',
    );

    $engine = dcl_importer_api_get_engine($default_provider);
    $module = $engine['module'];
    
    $form['import_form']['provider-submit'] = array(
      '#type' => 'submit',
      '#value' => t('Go'),
      '#dcl_button' => 'provider',
      '#attributes' => array('class' => 'no-js no-js-provider-button'),
    );
  }

  _dcl_importer_load_engine_form($form, $form_state, $module);
  $form['import_form']['submit']['#dcl_button'] = 'import_contacts';
}

/**
 * Build the contact selection form component
 */
function _dcl_importer_form_contacts(&$form, &$form_state, $new, $existing) {

  $form['contacts']['existing'] = _dcl_importer_existing_contacts_form($existing);
  $form['contacts']['new'] = _dcl_importer_new_contacts_form($new);

  $form['contacts']['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Add a Personal Message'),
  );

  $form['contacts']['buttons']['invite_contacts'] = array(
    '#type' => 'submit',
    '#value' => t('Send Invite Request'),
    '#dcl_button' => 'invite_contacts',
  );
  $form['contacts']['buttons']['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#dcl_button' => 'cancel',
  );
}

/**
 * Build the data for the "new" contacts listing.
 * This just creates a list of checkboxes which is processed in the theme
 * function afterwards.
 */
function _dcl_importer_new_contacts_form($contacts) {
	
  $contact_actions = _dcl_importer_invoke_import_action('contact_actions', array_keys($contacts));
//  if (empty($contact_actions)) {
//    return array();
//  }

  $form['#theme'] = 'dcl_importer_new_contacts';
  
  $options = array();

  foreach ($contact_actions as $action) {
    $contact = $contacts[$action['mail']];
    $id = $contact['mail'];
   // $options[$id] = '';
   // $form['mail'][$id] = array('#value' => $contact['mail']);
   // $form['name'][$id] = array('#value' => $contact['name']);
  }

  foreach($contacts as $contact){
	if(!is_numeric($contact["mail"])){
		$options[$contact['mail']]="";
		$id = $contact['mail'];	
		$form['mail'][$id] = array('#value' => $contact['mail']);
	    $form['name'][$id] = array('#value' => $contact['name']);
	}
  }

  $form['new_contacts'] = array(
    '#type' => 'checkboxes',
    '#default_value' => variable_get('dcl_importer_invite_select_all', TRUE) ? array_keys($options) : array(),
    '#options' => $options,
  );

  return $form;
}

/**
 * Build the data for the existing contacts listing.
 * This uses the gridselect module to display the listing in a facebook
 * like grid.
 */
function _dcl_importer_existing_contacts_form($contacts) {
  // Retrieve and clean up the actions
  $contact_actions = _dcl_importer_invoke_import_action('contact_actions', array_keys($contacts));
  if (empty($contact_actions)) {
    return array();
  }

  $actions = array();
  $keys = array();
  foreach ($contact_actions as $action) {
    if (!empty($action)) {
      $actions[$action['uid']][] = $action;
      // Only add one button per action title
      $keys[$action['key name']] = $action['key value'];
    }
  }
  
  $options = array();
  foreach (array_keys($actions) as $uid) {
    $user = $contacts[$uid];
    $options[$uid] = theme('dcl_importer_gridselect_cell', $user,$uid);
  }

  $form['existing_contacts'] = array(
    '#type' => 'gridselect',
    '#title' => t('Existing Contacts'),
    '#description' => t("Select the contacts you know"),
    '#sidebar' => FALSE,
    '#disabled_items' => array(),
    '#options' => $options,
    '#cols' => 5,
    '#rows' => 4,
  );

  foreach ($keys as $name => $value) {
    $form['existing_contacts'][$name] = array(
      '#type' => 'value',
      '#value' => $value,
    );
  }

  $form['instructions'] = array(
    '#type' => 'item',
    '#title'=>'This contacts don\'t have a Grabbit accout, you can invite them to join by checking the box'
  );
  
  return $form;
}

/**
 * Callback for AHAH functionality
 */
function dcl_importer_js() {
  $form_state = array('storage' => NULL, 'submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);

  $args = $form['#parameters'];
  $form_id = array_shift($args);
  $form_state['post'] = $form['#post'] = $_POST;
  $form['#programmed'] = $form['#redirect'] = FALSE;

  drupal_process_form($form_id, $form, $form_state);
  $form = drupal_rebuild_form($form_id, $form_state, $args, $form_build_id);

  $output = drupal_render($form['import_form']);
  drupal_json(array('status' => TRUE, 'data' => $output));
}

/**** Theme and preprocessor functions ****/

/**
 * Implementation of hook_preprocess_dcl_importer_form().
 * Adds the current selected provider to dcl_importer_form.tpl.php
 */
function dcl_importer_preprocess_dcl_importer_form(&$variables) {
  $variables['provider'] = arg(2);
}

/**
 * Theme function for each cell in the existing contacts field.
 */
function theme_dcl_importer_gridselect_cell($user,$uid) {
	$profile = content_profile_load('profile', $uid);
	
	$pic = theme('imagecache', 'friend_thumbnail', $profile->field_profile_picture[0]['filepath'], 'My Image');
	
  $data = array();
  $data['primary'] = $user['name']."<br><strong>".$user['mail']."</strong>";
  if ($user['name'] != $user['mail']) {
    $data['secondary'] = $user['mail'];
  }
$data['secondary'] = $pic;
  return array('data' => $data, 'title' => $user['mail']);
}

/**
 * Theme the "new" contacts (i.e. not yet members of the site) into a
 * "select-all" table. This uses the tableselect.js file and some custom
 * js in dcl_importer.js.
 */
function theme_dcl_importer_new_contacts($form) {
  $select_header = array('class' => 'select-all');
  $header = array($select_header, t('Email'), t('Name'));
  $rows = array();
  foreach (element_children($form['mail']) as $id) {
    $row = array();
    $row[] = drupal_render($form['new_contacts'][$id]);
    $row[] = drupal_render($form['mail'][$id]);
    $row[] = drupal_render($form['name'][$id]);
    $rows[] = array('data' => $row);
  }
  $output .= theme('table', $header, $rows, array('class' => 'new_dcl_contacts'));
  $output .= drupal_render($form);
  unset($_SESSION['dcl_contacts_new']);
  return $output;
}
