<?php
// $Id$

/**
 * @file
 *   Filter to allow only statuses posted on one's own profile.
 */

/**
 * Allows only statuses posted on one's own profile.
 */
class facebook_status_views_handler_filter_not_own extends views_handler_filter_boolean_operator {
  function construct() {
    $this->definition['type'] = 'yes-no';
    $this->definition['label'] = t("Show only others' statuses");
    $this->value_value = $this->definition['label'];
    parent::construct();
  }

  function query() {
    if ($this->value) {
      $this->ensure_my_table();
      $this->query->add_where(0, db_prefix_tables("$this->table_alias.uid <> $this->table_alias.pid"));
    }
  }
}