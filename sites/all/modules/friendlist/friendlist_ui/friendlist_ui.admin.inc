<?php
// $Id: friendlist_ui.admin.inc,v 1.1.2.17 2008/10/11 18:47:29 mercmobily Exp $

/**
 * @file
 * friendlist_ui.admin module file.
 */

function friendlist_ui_relation_types_overview() {

  // Get the list of items.
  $return = friendlist_api_relation_types_load_all();

  foreach ($return as $rt) {
    $rt = $rt;
    // $form[$rt['rtid']]['#rt'] = $rt; // No idea what this is for.
    $form[$rt->rtid]['rtid'] = array('#value' => check_plain($rt->rtid));
    $form[$rt->rtid]['name'] = array('#value' => check_plain($rt->name));
    $form[$rt->rtid]['name_p'] = array('#value' => check_plain($rt->name_p));
    $form[$rt->rtid]['oneway'] = array('#value' => $rt->oneway ? t('One way') : t('Reciprocal'));
    $form[$rt->rtid]['active'] = array('#value' => $rt->active ? t('Yes') : t('No'));
    $form[$rt->rtid]['edit'] = array('#value' => l(t('edit'), 'admin/settings/friendlist_relation_types/edit/'. $rt->rtid));
  }
  return $form;

}


function theme_friendlist_ui_relation_types_overview($form) {
  $rows = array();
  foreach (element_children($form) as $key) {
    if (isset($form[$key]['name'])) {
      $rt = &$form[$key];

      $row = array();
      $row[] = drupal_render($rt['rtid']);
      $row[] = drupal_render($rt['name']);
      $row[] = drupal_render($rt['name_p']);
      $row[] = drupal_render($rt['oneway']);
      $row[] = drupal_render($rt['active']);
      $row[] = drupal_render($rt['edit']);
      $rows[] = array('data' => $row);
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('No relations available.'), 'colspan' => '5'));
  }

  $header = array(
              t('ID'),
              t('Name'),
              t('Name plur'),
              t('Type'),
              t('Active')
            );
  $header[] = array('data' => t('Operations'), 'colspan' => '2');
  return theme('table', $header, $rows, array('id' => 'taxonomy')) . drupal_render($form);
}




function friendlist_ui_form_relation_type(&$form_state, $edit = NULL) {

  // If $edit is not set, it's a new form. Set a state (used during submit to
  // know if it's a new record).
  if (!$edit) {
    $edit = new stdClass();
    $edit->name = '';
    $edit->name_p = '';
    $edit->oneway = 0;
    $edit->active = 1;
    $form_state['is_new'] = TRUE;
  }
  else {
    $form_state['rtid'] = $edit->rtid;
  }

  $form['name'] = array(
    '#title' => t('Relation name'),
    '#type' => 'textfield',
    '#size' => 35,
    '#default_value' => $edit->name,
    '#required' => TRUE,
  );
  $form['name_p'] = array(
    '#title' => t('Relation name - plural form'),
    '#type' => 'textfield',
    '#size' => 35,
    '#default_value' => $edit->name_p,
    '#required' => TRUE,
  );
  $form['oneway'] = array(
    '#title' => t('One way relation'),
    '#type' => 'checkbox',
    '#default_value' => $edit->oneway,
    '#required' => FALSE,
  );
  $form['active'] = array(
    '#title' => t('Active'),
    '#type' => 'checkbox',
    '#default_value' => $edit->active,
    '#required' => FALSE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function friendlist_ui_form_relation_type_submit($form, &$form_state) {

  $values = $form_state['values'];

  // It's a new relation type: save.
  if ($form_state['is_new']) {
    $r = friendlist_api_relation_type_add(
          $values['name'],
          $values['name_p'],
          $values['oneway'],
          $values['active']
        );
  drupal_set_message(t('Relation type created'));
  // It's an existing relation type: edit.
  }
  else {
    $r = friendlist_api_relation_type_edit(
          $form_state['rtid'],
          $values['name'],
          $values['name_p'],
          $values['oneway'],
          $values['active']
        );
  drupal_set_message(t('Relation type saved'));
  }
  $form_state['redirect'] = 'admin/settings/friendlist_relation_types';
}

function friendlist_ui_relation_edit($rtid) {

  $return = friendlist_api_relation_type_load($rtid);
  return drupal_get_form('friendlist_ui_form_relation_type', $return);
}

function friendlist_ui_form_relation_type_validate($form, &$form_state) {
}


#################################################################
#    CONFIGURATION FORMS
#################################################################

/**
 * Return the configuration form.
 *
 * @return
 *   The config form
 */
function friendlist_ui_admin_settings() {

  $status_messages = variable_get('friendlist_status_messages', NULL);

  // Create a fieldset with all of the messages.
  $form['friendlist_status_messages'] = array(
      '#type' => 'fieldset',
      '#title' => t('Status messages'),
      '#collapsible' => TRUE,
      //'#collapsed' => TRUE,
      '#tree' => TRUE,
    );

  $status_data = friendlist_api_status_data();

  // Scan the messages array. Create an associative array filled with
  // every possible key of the messages array.
  foreach (array_keys($status_data) as $s) {
    foreach (array_keys($status_data[$s]) as $d) {
      if (drupal_substr($d, 0, 3) == 'on_') {
        foreach (array_keys($status_data[$s][$d]) as $o) {
          $k = "${s}_${d}_${o}";
          $default[$k] = $status_data[$s][$d][$o];
          $status_key[$k] = "Description of operation $d, for '$o'";
          //drupal_set_message("TEST: ${s}_${d}_${o}");
        }
      }
      else {
        $k = "${s}_${d}";
        $default[$k] = $status_data[$s][$d];
        $status_key[$k] = "Description of status $s";
        $status_separator[$k] = TRUE;
        $status_separator_field[$k] = $s;
        //drupal_set_message("TEST: ${s}_${d}");
      }
    }
  }

  // For each possible key, give the user a chance to
  // edit it.
  foreach (array_keys($status_key) as $sk) {

    // Prettify the form slightly, adding a separator for each status.
    if ($status_separator[$sk]) {
      $form['friendlist_status_messages'][$sk .'_description'] = array(
        '#value' => t('<br/><hr /><br/><h1>Settings for status !status</h1>', array('!status' => $status_separator_field[$sk]))
      );
    }

    $form['friendlist_status_messages'][$sk] = array(
      '#type' => 'textfield',
      '#title' => $status_key[$sk],
      '#size' => 80,
      '#maxlength' => 80,
      '#required' => FALSE,
      '#description' => t('Currently: !default', array('!default' => $default[$sk])),
      '#default_value' => $status_messages[$sk]);
  }


  $form['friendlist_ui_before_rebuild_status_cache'] = array(
    '#value' => t('This button will rebuild the cache:') . ' ',
  );
  $form['friendlist_ui_rebuild_status_cache'] = array(
    '#type' => 'submit',
    '#value' => t('Rebuild status cache'),
  );
  $form['friendlist_ui_after_rebuild_status_cache'] = array(
    '#value' => '<br/>',
  );


  return system_settings_form($form);
}

/**
 * Implementation of hook_validate().
 *
 * This is for the admin settings, which are actually empty for now.
 */
function friendlist_ui_admin_settings_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Rebuild status cache')) {
    drupal_goto('admin/settings/friendlist_ui/rebuild');
  }
}

/**
 * Menu callback: confirm rebuilding of permissions.
 */
function friendlist_ui_rebuild_confirm() {
  return confirm_form(array(), t('Are you sure you want to rebuild the permissions on site content?'),
                  'admin/settings/friendlist_ui', t('This action rebuilds the status cache for the friendlist module. This may be a lengthy process. This action cannot be undone.'), t('Rebuild status cache'), t('Cancel'));
}

/**
 * Handler for wipe confirmation.
 */
function friendlist_ui_rebuild_confirm_submit($form, &$form_state) {

  set_time_limit(600);


  // Loop amongst all of the possible statuses available
  $r = db_query('SELECT * FROM {friendlist_relations}');

  while ($row = db_fetch_object($r)) {
    friendlist_api_relation_status_update_cache_both($row->requester_id, $row->requestee_id, $row->rtid);
  }

  $form_state['redirect'] = 'admin/settings/friendlist_ui';
  drupal_set_message(t("DONE!"));

  return;
}


