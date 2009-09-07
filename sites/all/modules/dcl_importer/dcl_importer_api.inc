<?php
// $Id: dcl_importer_api.inc,v 1.2.4.1 2009/08/21 03:16:31 hadsie Exp $
/**
 *
 * @file
 * Contains the DCL Importer API calls
 *
 */

/**
 * Authenticates to the given provider.
 * @return - engine specific authentication values
 */
function dcl_importer_api_authenticate(&$errors, $provider, $username, $password) {
  // Find the appropriate engine
  $engine = dcl_importer_get_engine($provider);
  $token = call_user_func($engine['module'] . '_authenticate', $errors, $provider, $username, $password);
  return $token;
}

/**
 * Retrieves the contact list.
 * @param $token - The token return by the _authenticate function
 * @return - The contact array of the form
 *  Array (
 *    0 => Array (
 *      'mail' => 'first.email@address.com',
 *      'name' => 'First Email',
 *    ),
 *    1 => Array (
 *      'mail' => 'second.email@address.com',
 *      'name' => 'Second Email',
 *    ),
 *  )
 */
function dcl_importer_api_get_contacts($token) {
  $engine = dcl_importer_get_engine($provider);
  return call_user_func($engine['module'] . '_get_contacts', $token);
}

/**
 * Get a list of providers
 *
 * @param $all - If TRUE then returns all of the possible providers, if FALSE
 *   then returns only those providers that have been selected in the settings
 *   page.
 * @return
 *   an array containing available plugins in the form of
 *   Array (
 *    'openinviter_engine' => Array (
 *      'plugin' => 'gmail',
 *      'name' => 'GMail',
 *    )
 *    'openinviter_engine' => Array (
 *      'plugin' => 'msn',
 *      'name' => 'MSN',
 *    )
 *   )
 *
 */
function dcl_importer_api_get_providers($all = FALSE) {
  $plugin_arr = array();
  foreach (dcl_importer_api_engines() as $module => $engine) {
    $providers = call_user_func($module . '_get_providers');
    $provider_settings = variable_get($module . '_providers', NULL);
    foreach ($providers as $provider_key => $provider) {
      if ($all || $provider_settings == NULL || $provider_settings[$provider_key]) {
        $plugin_arr[$module][$provider_key] = $provider['name'];
      }
    }
  }
  return $plugin_arr;
}

/**
 * @return two lists:
 *  1. new contacts
 *  2. contacts that exist in the user table
 * 
 * The two arrays returned are of the same format as get_contacts;
 */
function dcl_importer_api_split_users($contacts) {
  if (empty($contacts)) {
    return $contacts;
  }

  $emails = array();
  foreach ($contacts as $contact) {
    $emails[] = $contact['mail'];
  }
  
  $query = db_query(
    'SELECT uid, name, mail FROM {users} WHERE mail in (' . implode(', ', array_fill(0, count($emails), "'%s'")) . ')',
    $emails);

  $exists = array();
  $emails = array();
  while ($user = db_fetch_object($query)) {
    $exists[$user->uid] = array(
      'mail' => $user->mail,
      'name' => $user->name,
    );
    $emails[] = $user->mail;
  }

  // Remove existing emails from the original $contacts array
  $new = array();
  foreach ($contacts as $contact) {
    if (!in_array($contact['mail'], $emails)) {
      $new[$contact['mail']] = $contact;
    }
  }
  
  return array($new, $exists);
}

/**
 * Returns a list of compatible retrieval engines.
 *
 * @return array of arrays
 *  Each secondary array represents a retrieval engine with keys for:
 *    name - Name of the provider's homepage.
 *    url - URL of provider.
 *    inc - The path to the service's main include file, without which the engine cannot function.
 */
function dcl_importer_api_engines() {
  static $engines = array();
  if (!count($engines)) {
    foreach (module_implements('import_engine_info') as $module) {
      $engines[$module] = module_invoke($module, 'import_engine_info');
      $engines[$module]['module'] = $module;
    }
  }
  return $engines;
}

// Return the designated engine for the given provider
function dcl_importer_api_get_engine($provider) {
  $engines = dcl_importer_api_engines();
  foreach (dcl_importer_api_get_providers() as $module => $plugins) {
    foreach ($plugins as $plugin => $name) {
      if ($plugin == $provider) {
        return $engines[$module];
      }
    }
  }
  return FALSE;
}

