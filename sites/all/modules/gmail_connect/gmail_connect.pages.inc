<?php
// $Id: gmail_connect.pages.inc,v 1.1 2009/05/04 22:18:06 elliottf Exp $

/**********************************************************/
/* gmail_connect.pages.inc - the callbacks for the pages  */
/*  created by the gmail_connect module.                  */
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
 * gmail_connect_logout - log the user out of the current
 *  GMail Connect session.
 */
function gmail_connect_logout() {
  global $user;

  cache_clear_all('gmail_connect:'.$user->uid, 'cache');
  cache_clear_all('gmail_connect_messages:'.$user->uid, 'cache');

  if (isset($_GET['destination'])) {
    drupal_goto($_GET['destination']);
  }
}

/**
 * gmail_connect_page - list a few messages...
 */
function gmail_connect_page($account) {
  $css = drupal_get_path('module', 'gmail_connect') . '/theme/gmail_connect.css';
  if (file_exists(path_to_theme() . '/gmail_connect.css')) {
    $css = path_to_theme() . '/gmail_connect.css';
  }
  drupal_add_css($css);
  drupal_add_js(drupal_get_path('module', 'gmail_connect') . '/js/gmail_connect.js');

  $out = '';
  $sess = gmail_connect_get_session($account->uid);

  // we're allready connected, let's get some emails!
  if (sizeof($sess) > 0) {
    $messages = gmail_connect_get_messages($account->uid);

    $total_count = sizeof($messages);

    if (is_array($messages)) {
      // set the pager globals...
      global $pager_page_array, $pager_total, $pager_total_items;
      $pager_page_array[0] = (isset($_GET['page']) ? $_GET['page'] : 0);
      $pager_total[0] = ceil($total_count / 20);
      $pager_total_items[0] = $total_count;

      $messages = array_slice($messages, (20 * $pager_page_array[0]), 20, TRUE);
      foreach ($messages as $k => $v) {
        $data = array(
          'date_recieved' => ($v->udate >= (time() - 86400) ? date('H:i', $v->udate + $account->timezone) : date('M d, Y', $v->udate + $account->timezone)),
	  'from' => $v->fromaddress,
          'subject' => l(
	    (strlen($v->subject) > 0 ? $v->subject : '<none>'),
	    'user/'.$account->uid.'/gmail_connect/view/'.$k
	  ),
          'options' => l(
              t('Delete'), 
              'user/'.$account->uid.'/gmail_connect/delete/' . $k,
              array('attributes' => array('class' => 'gmail_connect_delete', 'id' => 'gmail_connect_delete-'.$k))
            ) . ' | ' . 
            l(
              t('Auto-Reply'),
              'user/'.$account->uid.'/gmail_connect/auto_reply/'.$k,
              array('attributes' => array('class' => 'gmail_connect_auto_reply', 'id' => 'gmail_connect_auto_reply-'.$k))
            ),
        );
        $messages[$k] = array(
          'data' => $data,
	  'id' => 'message-'.$k,
	  'class' => 'message' . ($v->Unseen == 'U' ? ' new' : '')
        );
      }
      $out = theme(
        'gmail_connect_page',
        theme('table', array('date_recieved' => t('Date Recieved'), 'from' => t('From'), 'subject' => t('Subject'), 'options' => t('Options')), $messages),
        theme('pager', 20)
      );
    }

  } else { // show the login form...
    drupal_set_message(t('You must log into your GMail account here before you can see your messages'));
    $sess['gmail_name'] = $account->gmail_name;
    $out = drupal_get_form('gmail_connect_get_login', $sess, FALSE);
  }
  return $out;
}

/**
 * gmail_connect_view_message - view a message by
 *  message ID
 *
 * @param: $accouunt - the mailbox owner
 * @param: $mid - the message ID
 */
function gmail_connect_view_message($account, $mid = -1) {
  $sess = gmail_connect_get_session($account->uid);
  $mbox = @imap_open(
    "{imap.googlemail.com:993/imap/ssl}INBOX",
    $sess['gmail_name'],
    $sess['gmail_pass']
  );

  $msgno = imap_msgno($mbox, $mid); // the non-unique message ID
  $header = imap_headerinfo($mbox, $msgno);
  $body = imap_fetchbody($mbox, $msgno, '1');
  imap_setflag_full($mbox, $msgno, "\\Seen");
  imap_close($mbox);
////// GRABBIT
  // update the cached message to set it as read
  $messages = gmail_connect_get_messages($account->uid);
  if ($messages[$mid]->Unseen == 'U') {
    $messages[$mid]->Unseen = '';
    cache_set('gmail_connect_messages:'.$account->uid, $messages, 'cache', (time() + variable_get('gmail_connect_cache_timeout', 60)));
  }
  return theme('gmail_connect_message', $header, $body);
}


/**
 * gmail_connect_delete_message - delete a message from
 *  the user's inbox.
 */
function gmail_connect_delete_message($form_state, $account, $mid = -1) {
  $form = array();

  $messages = gmail_connect_get_messages($account->uid);
  if (array_key_exists($mid, $messages)) {
    $form['confirm'] = array(
      '#type' => 'markup',
      '#value' => '<p>' . t('Are you sure you want to delete this message?  This action cannot be undone.') . '</p>',
    );
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Delete')
    );

    $form_state['storage']['account'] = $account;
    $form_state['storage']['sess'] = gmail_connect_get_session($account->uid);
    $form_state['storage']['mid'] = $mid;
  }

  if (sizeof($form) == 0) {
    drupal_set_message(t('Message not found!  Either the message does not exist or there was an error connecting to GMail.'), 'error');
    drupal_goto('user/'.$account->uid.'/gmail_connect');
  }
  return $form;
}

/**
 * gmail_connect_delete_message_submit - delete a message from
 *  the user's inbox.
 */
function gmail_connect_delete_message_submit($form, &$form_state) {
  $mbox = @imap_open(
    "{imap.googlemail.com:993/imap/ssl}INBOX",
    $form_state['storage']['sess']['gmail_name'],
    $form_state['storage']['sess']['gmail_pass']
  );

  if ($mbox === FALSE) {
    drupal_set_message(t('Message not found!  Either the message does not exist or there was an error connecting to GMail.'), 'error');
    drupal_goto('user/'.$form_state['storage']['account']->uid.'/gmail_connect');
  }

  imap_delete($mbox, $form_state['storage']['mid'], FT_UID);
  imap_close($mbox, CL_EXPUNGE);

  // remove the message from the message cache since we
  // just deleted it
  $messages = gmail_connect_get_messages($form_state['storage']['account']->uid);
  if (array_key_exists($form_state['storage']['mid'], $messages)) {
    unset($messages[$form_state['storage']['mid']]);
    cache_set('gmail_connect_messages:'.$form_state['storage']['account']->uid, $messages, 'cache', (time() + variable_get('gmail_connect_cache_timeout', 60)));
  }

  drupal_set_message(t('Message deleted'));
  drupal_goto('user/'.$form_state['storage']['account']->uid.'/gmail_connect');
}

/**
 * gmail_connect_auto_reply - send an auto-reply
 *  message to the passed in message.
 *
 * @param: $account - the sender
 * @param: $mid - the message ID
 */
function gmail_connect_auto_reply($account, $mid = -1) {
  $messages = gmail_connect_get_messages($account->uid);

  $sess = gmail_connect_get_session($account->uid);
  $mbox = @imap_open(
    "{imap.googlemail.com:993/imap/ssl}INBOX",
    $sess['gmail_name'],
    $sess['gmail_pass']
  );

  $success = imap_mail(
    $messages[$mid]->fromaddress,
    'RE: ' . $messages[$mid]->subject,
    (isset($account->gmail_auto_reply) ? $account->gmail_auto_reply : variable_get('gmail_connect_auto_reply', GMAIL_CONNECT_AUTO_REPLY)),
    'From: '. $sess['gmail_name'] 
  );

  imap_close($mbox);
  if ($success) {
    drupal_set_message(t('Auto-reply message sent to @rec', array('@rec' => $messages[$mid]->fromaddress)));
  } else {
    drupal_set_message(t('There was a problem sending auto-reply message to @rec', array('@rec' => $messages[$mid]->fromaddress)));
  }
  drupal_goto('user/'.$account->uid.'/gmail_connect');
}

