<?php

// $Id: views_handler_filter_status.inc,v 1.1.2.4 2008/10/11 18:47:30 mercmobily Exp $

/**
 * @file
 * views_handler_filter_status for Views integration.
 */

/**
 * Field handler to filter according to the status.
 */
class views_handler_filter_status extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Status');

      $status_data = friendlist_api_status_data();
      foreach ($status_data as $key => $v) {
        $options[$key] = "$key -- ". t($v['description']);
      }

      $this->value_options = $options;
    }
  }
}

