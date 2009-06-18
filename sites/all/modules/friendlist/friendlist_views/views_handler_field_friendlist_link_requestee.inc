<?php

// $Id: views_handler_field_friendlist_link_requestee.inc,v 1.1.2.6 2008/10/11 18:47:30 mercmobily Exp $

/**
 * @file
 * views_handler_field_friendlist_link_requestee for Views integration.
 */

/**
 * Field handler to present a link to the user - requestee.
 */
class views_handler_field_friendlist_link_requestee extends views_handler_field_friendlist_link {

  function render($values) {

    global $user;

    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
    $requestee_id = $values->{$this->aliases['requestee_id']};
    $requester_id = $values->{$this->aliases['requester_id']};
    $rtid = $values->{$this->aliases['rtid']};

    $add = friendlist_ui_get_link('add', $requestee_id, $rtid);
    $del = friendlist_ui_get_link('delete', $requestee_id , $rtid);

    if ($add) {
      $result = t('<div class="friendlist-user-links">!add_link</div>', array('!add_link' => $add) );
    }
    if ($del) {
      $result .= t('<div class="friendlist-user-links">!delete_link</div>', array('!delete_link' => $del) );
    }
    return $result;
  }
}
