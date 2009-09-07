<?php
// $Id: gridselect-cell.tpl.php,v 1.2 2009/09/01 03:52:59 hadsie Exp $

/**
 * @file gridselect-cell.tpl.php
 * Theme implementation to present each grid cell.
 *
 * Available variables:
 * - $key: The key used to identify this cells data.
 * - $key_id: The "processed" version of the key to use as in html.
 * - $cell: The complete cell data array.
 * - $disabled: TRUE if this cell should be disabled.
 * - $selected: TRUE if this cell should be selected.
 * - $attributes: Any html attributes to be added to the list item.
 * - $data: The cell data as processed by gridselect_cell_data.tpl.php
 *
 * @see template_preprocess_gridselect_cell
 */
?>
<li id="key-<?php print $key_id; ?>"<?php print $attributes; ?>>
  <a href="#"<?php if ($selected) print 'class="selected"'; ?> title="<?php print $title; ?>"><?php print $data; ?></a>
</li>
