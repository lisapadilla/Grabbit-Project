/* $Id: README.txt,v 1.7.2.1 2009/08/21 03:16:31 hadsie Exp $ */

-- SUMMARY --

The dcl_importer lets users import contacts from various third party services
such as facebook, myspace, gmail, yahoo, friendfeed, twitter, and numerous
other services using an "importer engine". Currently the only support engine is the OpenInviter library.

NOTE: The only services are working are those that return a valid email address (facebook, for example, only returns the user id). Because of this, any of the social
networks are unlikely to be compatible.

-- REQUIREMENTS --

 * An importer engine. For now only OpenInviter is support.
     The OpenInviter package from http://openinviter.com/download.php.
     Use the "general" version, NOT the drupal specific version. It should be
     uncompressed within the openinviter_engine module directory:
       ex: sites/all/modules/dcl_importer/importers/openinviter_engine/OpenInviter

 * For the OpenInviter to function properly you will need to have PHP5 installed
   with DOMDocument support and either cURL or WGET.

-- INSTALLATION --

 * Install as usual, see http://drupal.org/node/70151 for further information.

 * Download and install the OpenInviter library as described in the REQUIREMENTS.
 
 * Run the script OpenInviter/postinstall.php to verify that everything is
   setup properly. This sets up the OpenInviter/config.php file. This will be at something
   like: http://<url>/sites/<site>/modules/dcl_importer/importers/openinviter_engine/Openinviter/postinstall.php

 * Remove the file postinstall.php
 
 * Setup permissions (admin/user/permissions)

 * Browse to the settings page (admin/settings/dcl_importer) and configure
   your preferences there.

-- IMPORTERS --

This module is designed to work with multiple importers. Each importer can be
configured with a weight and a list of "providers" it supports in the dcl_importer
admin settings page.

Currently the only supported importer is OpenInviter as listed above.

-- MODULE INTEGRATION --

The dcl_importer currently integrates with:
 * invite (http://drupal.org/project/invite)
 * friendlist (http://drupal.org/project/friendlist)
 * user_relationships (http://drupal.org/project/user_relationships)
   Both friendlist and user_relationships integration will only work properly if you have
   only one relation available to the user. If there's more than one then the importer
   doesn't know which relationship to act on.
 * services (http://drupal.org/project/services)

If you have the invite module and it's corresponding dcl connector installed then a new
menu tab on the invite page will be added called "Import Contacts".

The friendslist connector will add a "find friends" tab to the user profile page.

-- FOR DEVELOPERS --

-- Adding Importers: --
 See the openinviter_engine in the importers/ folder for an example.
 Each import engine needs to have the following
  * hook_import_engine_info() - Defines the engine details
  * <engine>_engine_form() - The import form for that module
  * <engine>_authenticate(&$errors, $provider, $username, $password)
  * <engine>_get_contacts($token)


-- Module Integration: --
  See the existing modules in the modules/ folder for example implementations.
  dcl_importer provides a hook described below:

hook_import_action($op, $a2, $a3)

Use this hook to alter dcl import functionality.

Parameters:
 $op The kind of action being performed. Possible values:
 
   * "contact_actions": This method is used to determine which users should be acted on by the connector. There are two types of users, those who are already in the system and those who aren't. If they are in the system, then the value in the $a2 parameter will contain a UID, otherwise it will contain an email address.

   In the example of the friendlist connector, I only want to act on users who are already
   in the system so I run a test in the import_action hook such as
   "if (!is_numeric($uid)) {"

   Whereas in the invite connector I'm looking for contacts who aren't in the system and
   run a test to validate the email address with:
   if (preg_match('/^[a-zA-Z0-9\._%\+\-]+@[a-zA-Z0-9\.\-]+\.[a-zA-Z]{2,4}$/', $email)) {

   The return value from this method should be the full list of users that match the criteria for that particular action. You may also want to use the 'key name' and 'key value' parameters which specify values to be passed with the form.

   The return value should be something like:
   return array(
     0 => array(
       'mail' => 'firstuser@example.com',
       'key name' => 'value1',
       'key value' => 'value',
     ),
     1 => array(
       'uid' => 5,
       'key name' => 'action2_key',
       'key value' => 'action2_value',
     ),
     ...
   );
   If the user is new, then 'mail' shoud be used. If they're already in the system then
   return the respective uid.
   
  * "submit": This method is called when the form submit is executed. This is where the actual action will happen. In the case of the invite connector we loop through all of the 'new_contacts' and run 'invite_send' on them. After the processing it allows a redirect value to be returned which should be the path to redirect to after submit. Only one of the enabled modules' redirect value can be used.

  $a2
   * For "contact_actions" this contains the imported contacts
   * For "submit" this represents the $form variable

  $a3
   * For "contact_actions" this field is not used
   * For "submit" this field contains the $form_state variable

-- CONTACT --

For bug reports, feature suggestions and latest developments visit the
project page: http://drupal.org/project/dcl_importer

Current maintainer:
 * Scott Hadfield (hadsie) <hadsie@gmail.com>

-- CREDITS --

Original D5 author:
 * Ma'moon Al-Akash (soosa)

Original D6 author:
 * Shankar Dhanasekaran (neokrish)
