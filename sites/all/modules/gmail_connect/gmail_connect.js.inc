<?php
// $Id: gmail_connect.js.inc,v 1.1 2009/05/04 22:18:06 elliottf Exp $

/**********************************************************/
/* gmail_connect.js.inc - this include file handles the   */
/*  JavaScript callbacks for the gmail_connect module.    */
/*                                                        */
/* This program is free software: you can redistribute it */
/*  and/or modify it under the terms of the GNU General   */
/*  Public License as published by the Free Software      */
/*  Foundation, either version 3 of the License, or (at   */
/*  your option) any later version.                       */
/*                                                        */
/* This program is distributed in the hope that it will   */
/*  be useful, but WITHOUT ANY WARRANTY; without even the */
/*  implied warranty of MERCHANTABILITY or FITNESS FOR A  */
/*  PARTICULAR PURPOSE.  See the GNU General Public       */
/*  License for more details.                             */
/*                                                        */
/* You should have received a copy of the GNU General     */
/*  Public License along with this program.  If not, see  */
/*  <http://www.gnu.org/licenses/>.                       */
/*                                                        */
/* @author: Elliott Foster                                */
/* @copyright: Elliott Foster 2009                        */
/**********************************************************/

/**
 * gmail_connect_js - handle the AHAH login callback.
 */
function gmail_connect_js() {
  global $user;
  $out = '';

  $sess = gmail_connect_get_session($user->uid, array('gmail_name' => $_POST['name'], 'gmail_pass' => $_POST['pass']));

  $messages = gmail_connect_get_count($sess);
  if (!is_array($messages) && stripos($messages, 'fail') !== FALSE) {
    $form_build_id = $_POST['form_build_id'];
    if (!$form = form_get_cache($form_build_id, $form_state)) {
      exit();
    }

    // Rebuild the form.
    $form = form_builder('mashcast_ad_node_form', $form, $form_state);
    $out = $messages . "\n" . drupal_render($form);
  } else {
    $out = theme('gmail_connect_counts', $messages);
  }
  drupal_json(array('status' => TRUE, 'data' => $out));
}

/**
 * gmail_connect_js_delete - delete a message 
 *  via AJAX.
 */
function gmail_connect_js_delete($mid = -1) {
  global $user;

  if ($mid == -1) {
    return FALSE;
  }

  $sess = gmail_connect_get_session($user->uid);
  $mbox = @imap_open(
    "{imap.googlemail.com:993/imap/ssl}INBOX",
    $sess['gmail_name'],
    $sess['gmail_pass']
  );

  if ($mbox === FALSE) {
    return FALSE;
  }

  imap_delete($mbox, $mid, FT_UID);
  imap_close($mbox, CL_EXPUNGE);

  // remove the message from the message cache since we
  // just deleted it
  $messages = gmail_connect_get_messages($user->uid);
  if (array_key_exists($mid, $messages)) {
    unset($messages[$mid]);
    cache_set('gmail_connect_messages:'.$user->uid, $messages, 'cache', (time() + variable_get('gmail_connect_cache_timeout', 60)));
  }
}

