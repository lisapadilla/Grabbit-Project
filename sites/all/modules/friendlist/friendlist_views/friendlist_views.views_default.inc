<?php
// $Id: friendlist_views.views_default.inc,v 1.1.2.17 2009/02/08 08:29:32 inadarei Exp $

/**
 * @file
 * Friendlist's preconfigured views
 */

/**
 * Implementation of hook_default_view_views().
 */
function friendlist_views_views_default_views() {
  // Load all views from the "views_defs" subdirectory
  foreach (glob(dirname(__FILE__) . "/views_defs/*.inc") as $filename) {
      include_once($filename);
      $views[$view->name] = $view;
  }
  return $views;
}


