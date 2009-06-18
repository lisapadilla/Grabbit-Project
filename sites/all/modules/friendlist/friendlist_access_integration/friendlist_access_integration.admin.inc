<?php
// $Id: friendlist_access_integration.admin.inc,v 1.1.2.7 2008/10/11 18:47:28 mercmobily Exp $

/**
 * @file
 * Friendlist's Views integration configuration forms.
 */

#################################################################
#    CONFIGURATION FORMS
#################################################################

/**
 * Return the configuration form.
 *
 * @return
 *   The config form.
 */
function friendlist_access_integration_admin_settings() {


  $form['friendlist_access_integration']['cck_field_privacy'] = array(
      '#type' => 'fieldset',
      '#title' => t('CCK Field privacy integration'),
      '#collapsible' => TRUE,
      #'#collapsed' => TRUE,
      #'#tree' => TRUE,
    );

  // Make up the options for the statuses.
  $options_status = array();
  $status_data = friendlist_api_status_data();
  foreach ($status_data as $key => $v) {
    $options_status[$key] = "$key -- ". t($v['description']);
  }

  // Make up the options for the relation types.
  $relation_types = friendlist_api_relation_types_load_all();
  $options_rt = array();
  foreach ($relation_types as $relation_type) {
    $options_rt[$relation_type->rtid] = $relation_type->rtid .' -- '. $relation_type->name;
    }

  $form['friendlist_access_integration']['cck_field_privacy']['friendlist_access_integration_cck_field_privacy_statuses'] = array(
    '#type' => 'select',
    '#options' => $options_status,
    '#multiple' => TRUE,
    '#title' => 'Statuses which will grant field access for locked fields',
    '#required' => FALSE,
    '#default_value' => variable_get('friendlist_access_integration_cck_field_privacy_statuses', array()),
  );


  $form['friendlist_access_integration']['cck_field_privacy']['friendlist_access_integration_cck_field_privacy_rtid'] = array(
    '#type' => 'select',
    '#options' => $options_rt,
    '#title' => 'Relation type that will be checked against while granting field access for locked fields',
    '#required' => FALSE,
    '#default_value' => variable_get('friendlist_access_integration_cck_field_privacy_rtid', 0),
  );

  return system_settings_form($form);
}


