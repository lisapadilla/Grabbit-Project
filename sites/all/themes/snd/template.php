<?php
// $Id: template.php,v 1.1 2009/06/06 18:19:44 giorgio79 Exp $

/**
 * @file
 *
 * OVERRIDING THEME FUNCTIONS
 *
 * The Drupal theme system uses special theme functions to generate HTML output
 * automatically. Often we wish to customize this HTML output. To do this, we
 * have to override the theme function. You have to first find the theme
 * function that generates the output, and then "catch" it and modify it here.
 * The easiest way to do it is to copy the original function in its entirety and
 * paste it here, changing the prefix from theme_ to STARTERKIT_. For example:
 *
 *   original: theme_breadcrumb()
 *   theme override: STARTERKIT_breadcrumb()
 *
 * where STARTERKIT is the name of your sub-theme. For example, the zen_classic
 * theme would define a zen_classic_breadcrumb() function.
 *
 * If you would like to override any of the theme functions used in Zen core,
 * you should first look at how Zen core implements those functions:
 *   theme_breadcrumbs()      in zen/template.php
 *   theme_menu_item_link()   in zen/template-menus.php
 *   theme_menu_local_tasks() in zen/template-menus.php
 */

function snd_breadcrumb($breadcrumb) {
  $show_breadcrumb = theme_get_setting('zen_breadcrumb');
  $show_breadcrumb_home = theme_get_setting('zen_breadcrumb_home');
  $breadcrumb_separator = theme_get_setting('zen_breadcrumb_separator');
  $trailing_separator = (theme_get_setting('zen_breadcrumb_trailing') || theme_get_setting('zen_breadcrumb_title')) ? $breadcrumb_separator : '';
  $leading_separator = theme_get_setting('zen_breadcrumb_leading') ? $breadcrumb_separator : '';

  // Determine if we are to display the breadcrumb
  if ($show_breadcrumb == 'yes' || $show_breadcrumb == 'admin' && arg(0) == 'admin') {
    if (!$show_breadcrumb_home) {
      // Optionally get rid of the homepage link
      array_shift($breadcrumb);
    }
    if (!empty($breadcrumb)) {
      // Return the breadcrumb with separators
      return '<div class="breadcrumb">' . $leading_separator . implode($breadcrumb_separator, $breadcrumb) . "$trailing_separator</div>";
    }
  }
  // Otherwise, return an empty string
  return '';
}


/*
 * Add any conditional stylesheets you will need for this sub-theme.
 *
 * To add stylesheets that ALWAYS need to be included, you should add them to
 * your .info file instead. Only use this section if you are including
 * stylesheets based on certain conditions.
 */

/* -- Delete this line if you want to use and modify this code
// Example: optionally add a fixed width CSS file.
if (theme_get_setting('STARTERKIT_fixed')) {
  drupal_add_css(path_to_theme() . '/layout-fixed.css', 'theme', 'all');
}
// */


/**
 * Implementation of HOOK_theme().
 */
function snd_theme(&$existing, $type, $theme, $path) {
  return zen_theme($existing, $type, $theme, $path);
}

/**
 * Override or insert PHPTemplate variables into all templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called (name of the .tpl.php file.)
 */
/* -- Delete this line if you want to use this function
function snd_preprocess(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert PHPTemplate variables into the page templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called ("page" in this case.)
 */
/* -- Delete this line if you want to use this function
function snd_preprocess_page(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert PHPTemplate variables into the node templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called ("node" in this case.)
 */
/* -- Delete this line if you want to use this function
function snd_preprocess_node(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert PHPTemplate variables into the comment templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called ("comment" in this case.)
 */
/* -- Delete this line if you want to use this function
function snd_preprocess_comment(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert PHPTemplate variables into the block templates.
 *
 * @param $vars
 *   A sequential array of variables to pass to the theme template.
 * @param $hook
 *   The name of the theme function being called ("block" in this case.)
 */
/* -- Delete this line if you want to use this function
function snd_preprocess_block(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */


/**
 * The rel="nofollow" attribute is missing from anonymous users' URL in Drupal 6.0-6.2.
 */
/* -- Delete this line if you want to use this function
function snd_username($object) {

  if ($object->uid && $object->name) {
    // Shorten the name when it is too long or it will break many tables.
    if (drupal_strlen($object->name) > 20) {
      $name = drupal_substr($object->name, 0, 15) . '...';
    }
    else {
      $name = $object->name;
    }

    if (user_access('access user profiles')) {
      $output = l($name, 'user/' . $object->uid, array('attributes' => array('title' => t('View user profile.'))));
    }
    else {
      $output = check_plain($name);
    }
  }
  else if ($object->name) {
    // Sometimes modules display content composed by people who are
    // not registered members of the site (e.g. mailing list or news
    // aggregator modules). This clause enables modules to display
    // the true author of the content.
    if (!empty($object->homepage)) {
      $output = l($object->name, $object->homepage, array('attributes' => array('rel' => 'nofollow')));
    }
    else {
      $output = check_plain($object->name);
    }

    $output .= ' (' . t('not verified') . ')';
  }
  else {
    $output = variable_get('anonymous', t('Anonymous'));
  }

  return $output;
}
// */
/**
 *	Implements hook_color()
 *  Color replacement method(s): 'shift' (using base)
 */
function snd_color() {
	/**
	 *  $color = array() (Required)
	 *  For essential scheme information.
	 *
	 */
	$color = array(
	  /**
	   *  'replacement methods'
	   *  Declare replacement replacement methods in the 'replacement methods' array, 
	   *  in the order you want them to work.
	   *    They are comprised different algorithms to change your colors.
	   *  replacement methods like 'shift' can accept different options and behave differently.
	   *  To change the order of the replacement methods color replacement, put them in order.
	   */
	  'replacement methods' => array(
	    /**
	     *  'shift' method
	     *  Requires 'base-only', or 'base', and/or'link' and/or 'text'
	     */
	    'shift' => array('base'),
	  ),

	  /**
	   *  'fields' (Required)
	   *  The machine-readable names of color fields. The name will help you
	   *  and your theme users identify colors.
	   */
	  'fields' => array('base'),

	  /**
	   *  'premade schemes' (Required)
	   *  A list of pre-made schemes that will be available for install by default.
	   *  The scheme name, human-readable, is followed by hex values separated by
	   *  commas (no spaces). The colors are to be ordered respectable to 'fields'.
	   *
	   *  This scheme uses a special shift feature called 'base-only'. 
	   *  So we only mention a single color, and the rest of the work
	   *  is done for us.
	   */
	  'premade schemes' => array(
	    'Blue' => array('base' => '#006287'),
	    'Gold' => array('base' => '#6E720D'),
	    'Green' => array('base' => '#11551c'),
	    'Orange' => array('base' => '#72380D'),
	    'Purple' => array('base' => '#24156A'),
	    'Red' => array('base' => '#a00025'),
	    'Rose' => array('base' => '#72170D'),
	    'Aqua' => array('base' => '#0075a0'),
	  ),

	  /**
	   *  'default scheme' (Required)
	   *  A scheme name from one in your 'premade schemes' list.
	   */
	  'default scheme' => 'Blue',

	  /**
	   *  'reference scheme' (Required)
	   *  A scheme name from one in your 'premade schemes' list.
	   *  On schemes which use the 'base', 'link' or 'text' flag, always mention this.
	   *  Other schemes will be shifted against the fields of the reference one.
	   */
	  'reference scheme' => 'Blue',

	  /**
	   *  'stylesheets' (Required)
	   *  Path to your CSS file relevant to the root of your theme directory.
	   *  Can mention an array of stylesheets.
	   */
	  'stylesheets' => array('snd.css'),

	  /**
	   *  'blend target' (Required)
	   *  Used as a target color for image and shifting colors to and fro.
	   *  Usually #ffffff, #000000, or #666666 can do.
	   */
	  'blend target' => '#ffffff'
	);
	
	return $color;
}