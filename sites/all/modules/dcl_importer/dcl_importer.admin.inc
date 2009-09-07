<?php
// $Id: dcl_importer.admin.inc,v 1.1.2.1 2009/08/21 03:16:31 hadsie Exp $
/**
 * @file
 * Contains the admin menu and settings functionality
 */

/**
 * The admin settings form
 */
function dcl_importer_admin() {
  dcl_importer_check_engines();
  
  $form = array();

  $advanced_dependencies = FALSE;
  if (module_exists('gridselect') && module_exists('ahah_helper')) {
    $advanced_dependencies = TRUE;
  }
  
  $form['dcl_importer_advanced_form'] = array(
    '#type' => 'checkbox',
    '#disabled' => !$advanced_dependencies,
    '#title' => t('Enable Advanced Import Form'),
    '#description' => t('In order to use the advanced form you will need to install both the gridselect and the ahah_helper modules'),
    '#default_value' => variable_get('dcl_importer_advanced_form', FALSE),
  );
  
  $form['dcl_importer_invite_select_all'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('dcl_importer_invite_select_all', TRUE),
    '#title' => t('Select all contacts by default when importing'),
  );
  
  $providers = dcl_importer_api_get_providers();
  $providers = _dcl_importer_clean_provider_list($providers);
  array_unshift($providers, 'Select');

  $current_providers = variable_get('dcl_importer_providers', array());
  
  $form['providers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Provider Priority'),
    '#description' => t('Define the top four providers here. They will be listed at the top of any select boxes for convenience. Or as the main tabs in the advanced form'),
  );
  $form['providers']['dcl_importer_provider1'] = array(
    '#type' => 'select',
    '#title' => t('Provider 1'),
    '#default_value' => $current_providers[0],
    '#options' => $providers,
  );
  $form['providers']['dcl_importer_provider2'] = array(
    '#type' => 'select',
    '#title' => t('Provider 2'),
    '#default_value' => $current_providers[1],
    '#options' => $providers,
  );
  $form['providers']['dcl_importer_provider3'] = array(
    '#type' => 'select',
    '#title' => t('Provider 3'),
    '#default_value' => $current_providers[2],
    '#options' => $providers,
  );
  $form['providers']['dcl_importer_provider4'] = array(
    '#type' => 'select',
    '#title' => t('Provider 4'),
    '#default_value' => $current_providers[3],
    '#options' => $providers,
  );

  $header = array(t('Title'), t('URL'));
  $rows = array();
  foreach (dcl_importer_api_engines() as $engine) {
    $rows[] = array(
      'data' => array(
        array('data' => $engine['name']),
        array('data' => l($engine['url'], $engine['url'])),
      ),
      'class' => 'draggable',
    );
  }
  $engines = theme('table', $header, $rows, array('id' => 'importer-engine-table'));

  $form['dcl_importer_engines'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available importer engines'),
  );
  
  $form['dcl_importer_engines']['dcl_importer_engines'] = array(
    '#value' => $engines,
  );

  $form['dcl_importer_engines']['weight']['#attributes']['class'] = 'importers-engine-weight';

  drupal_add_tabledrag('importer-engine-table', 'order', 'sibling', 'importers-engine-weight');
    
  $form['#submit'] = array('dcl_importer_admin_submit');
  return system_settings_form($form);
}

/**
 * Custom submit handler for the admin form that sets the providers array
 * used on the advanced form.
 */
function dcl_importer_admin_submit($form, &$form_values) {
  // Save the provider values to an array 
  $providers = array();
  foreach ($form_values['values'] as $key => $value) {
    if (preg_match('/dcl_importer_provider[0-9]+/', $key)) {
      $providers[] = $value;
      unset($form_values['values'][$key]);
    }
  }
  variable_set('dcl_importer_providers', $providers);
}

/**
 * Theme function for the admin settings plugin table.
 * Displays the plugin checkboxes as a table
 */
function theme_dcl_importer_admin_plugin_table(&$form) {
  $plugins = array();

  // Flatten forms array.
  foreach (element_children($form) as $plugin) {
    $plugins[] = drupal_render($form[$plugin]);
  }

  // Split checkboxes into rows with 3 columns.
  $total = count($plugins);
  $rows = array();
  for ($i = 0; $i < $total; $i++) {
    $row = array();
    $row[] = array('data' => $plugins[$i]);
    if (isset($plugins[++$i])) {
      $row[] = array('data' => $plugins[$i]);
    }
    if (isset($plugins[++$i])) {
      $row[] = array('data' => $plugins[$i]);
    }
    $rows[] = $row;
  }

  $output = theme('table', array(), $rows, array('width' => '100%'));

  return $output;
}
