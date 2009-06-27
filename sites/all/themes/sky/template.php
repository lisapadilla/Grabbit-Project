<?php
// $Id$

/**
 * @file
 * The guts of the theme :)
 */

/*
 * Initialize theme settings
 */
if (is_null(theme_get_setting('sky_layout'))) {
  global $theme_key;

  // Save default theme settings
  $defaults = array(
    'sky_background' => NULL,
    'sky_background_header' => NULL,
    'sky_breadcrumbs' => 0,
    'sky_breadcrumbs_sep' => '&raquo;',
    'sky_links' => NULL,
    'sky_links_active' => NULL,
    'sky_links_hover' => NULL,
    'sky_links_visited' => NULL,
    'sky_font' => 'lucida',
    'sky_font_headings' => 'lucida',
    'sky_font_size' => '12px',
    'sky_header_height' => 'auto',
    'sky_layout' => 'fixed_960',
    'sky_custom_layout' => NULL,
    'sky_nav_alignment' => 'center',
    'sky_sub_navigation_size' => '15em',
  );

  // Get default theme settings.
  $settings = theme_get_settings($theme_key);
  // Don't save the toggle_node_info_ variables.
  if (module_exists('node')) {
    foreach (node_get_types() as $type => $name) {
      unset($settings['toggle_node_info_'. $type]);
    }
  }
  // Save default theme settings.
  variable_set(
    str_replace('/', '_', 'theme_'. $theme_key .'_settings'),
    array_merge($defaults, $settings)
  );

  // Force refresh of Drupal internals
  theme_get_setting('', TRUE);
}

/**
 * Add Custom Generated CSS File
 * This file is generated each time the theme settings page is loaded.
 * @todo Test subthemes.
 */
$custom_css = file_directory_path() .'/sky/custom.css';
if (file_exists($custom_css)) {
  drupal_add_css($custom_css, 'theme', 'all', TRUE);
}

/**
 * Implementation of hook_theme().
 * This function provides a one-stop reference for all
 */
function sky_theme() {
  return array(
    'breadcrumb' => array(
      'arguments' => array('breadcrumb' => array()),
      'file' => 'functions/theme-overrides.inc',
    ),
    'conditional_stylesheets' => array(
      'file' => 'functions/theme-custom.inc',
    ),
    'feed_icon' => array(
      'arguments' => array('url' => NULL, 'title' => NULL),
      'file' => 'functions/theme-overrides.inc',
    ),
    'form_element' => array(
      'arguments' => array('element' => NULL, 'value' => NULL),
      'file' => 'functions/theme-overrides.inc',
    ),
    'fieldset' => array(
      'arguments' => array('element' => NULL),
      'file' => 'functions/theme-overrides.inc',
    ),
    'menu_local_tasks' => array(
      'arguments' => NULL,
      'file' => 'functions/theme-overrides.inc',
    ),
    'more_link' => array(
      'arguments' => array('url' => array(), 'title' => NULL),
      'file' => 'functions/theme-overrides.inc',
    ),
    'pager' => array(
      'arguments' => array('tags' => array(), 'limit' => NULL, 'element' => NULL, 'parameters' => array(), 'quantity' => NULL),
      'file' => 'functions/theme-overrides.inc',
    ),
   'status_messages' => array(
      'arguments' => array('display' => NULL),
      'file' => 'functions/theme-overrides.inc',
    ),
    'status_report' => array(
      'arguments' => array('requirements' => NULL),
      'file' => 'functions/theme-overrides.inc',
    ),
    'table' => array(
      'arguments' => array('header' => NULL, 'rows' => NULL, 'attributes' => array(), 'caption' => NULL),
      'file' => 'functions/theme-overrides.inc',
    ),
    'render_attributes' => array(
      'arguments' => array('attributes'),
      'file' => 'functions/theme-custom.inc',
    ),
  );
}

/**
 * Implementation of hook_preprocess().
 *
 * @param $vars
 * @param $hook
 * @return Array
 */
function sky_preprocess(&$vars, $hook) {

  // Only add the admin.css file to administrative pages
  if (arg(0) == 'admin') {
    drupal_add_css(path_to_theme() .'/css/admin.css', 'theme', 'all', TRUE);
  }

 /**
  * This function checks to see if a hook has a preprocess file associated with
  * it, and if so, loads it.
  */
  if (is_file(drupal_get_path('theme', 'sky') .'/preprocess/preprocess-'. str_replace('_', '-', $hook) .'.inc')) {
    include('preprocess/preprocess-'. str_replace('_', '-', $hook) .'.inc');
  }
}

drupal_rebuild_theme_registry();