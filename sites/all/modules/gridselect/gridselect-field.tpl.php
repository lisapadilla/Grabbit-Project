<?php
// $Id: gridselect-field.tpl.php,v 1.2 2009/09/01 03:52:59 hadsie Exp $

/**
 * @file gridselect-field.tpl.php
 * Theme implementation to present the overall grid selection widget
 *
 * Available variables:
 * - $field: The gridselect form field
 * - $items: An array of all of the cells in the grid
 * - $inline_style: Inline style necessary to set the width and height for the grid
 * - $sidebar: TRUE if the sidebar should be displayed
 * - $sidebar_style: Inline style necessary to set the height of the sidebar
 * - $disabled: An array containing all of the disabled items
 * - $selected: An array containing all of the selected items
 *
 * @see template_preprocess_gridselect_field
 */
?>
<div id="multi-grid-selector">
  <ul id="items" <?php print $inline_style; ?>>
    <?php foreach ($items as $key => $cell): ?>
      <?php print theme('gridselect_cell', $key, $cell, $disabled, in_array($key, $selected)); ?>
    <?php endforeach; ?>
  </ul>
  
  <?php if ($sidebar): ?>
    <ul id="selected-items" <?php print $sidebar_style; ?>>
   </ul>
  <?php endif; ?>
  <br class="end-selector" />
</div>
