/* $Id */

-- SUMMARY --

The gridselect module adds a new form type that displays content in a similar way
to facebook friend pages (specifically the pages you see when inviting friends to
events). It's fairly simple with no configuration necessary.

This module requires javascript on the client side to work correctly. With no javascript
it will fallback to a multi-select field.

-- HOWTO USE THE MODULE --

This module is currently in use in the dcl_importer module. You can look there for a
usage example.

<?php
  $form['gridselect_eample'] = array(
    '#type' => 'gridselect',
    '#title' => t('Contacts'),
    '#description' => t("Select the contacts you know"),
    '#sidebar' => FALSE,
    '#disabled_items' => array(),
    '#options' => $options,
    '#cols' => 5,
    '#rows' => 4,
  );
?>

#sidebar: This is a sidebar used to display the currently selected cells
#disabled_items: Any disabled_items will be greyed out and not selectable
#options: An array of grid cells. Every cells is an associative array with the following keys:
  * "data": an array of cells - This field can contain the following keys:
    * class: Any classes to add to the cell
    * title: The value that will be used in the multiselect field if JS is disabled
    * avatar: a picture to sit in the cell
    * primary: The primary text to display in the cell
    * secondary: The secondary text to display in the cell
  * Any HTML attributes, such as "class", to apply to the table row.

#cols: the number of columns to display in the grid (default 4)
#rows: the number of rows to display in the grid (default 5)

-- TODO --
 * Support for CCK
 * Filter by selected / unselected users
 * Filter textbox to filter the contents based on arbitrary text input
 * Get the sidebar working

 -- CONTACT --

For bug reports, feature suggestions and latest developments visit the
project page: http://drupal.org/project/dcl_importer

Current maintainer:
 * Scott Hadfield (hadsie) <hadsie@gmail.com>

