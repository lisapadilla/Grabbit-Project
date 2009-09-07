<?php
// $Id: gridselect-cell-data.tpl.php,v 1.1 2009/08/28 23:41:16 hadsie Exp $

/**
 * @file gridselect-cell-data.tpl.php
 * Theme implementation to present the data in each grid cell.
 *
 * Available variables:
 * - $key: The key used to identify this cells data.
 * - $cell: The complete cell data array.
 * - $primary_rendered: The "trimmed" version of the username (to prevent
 *    wrapping format errors).
 * - $secondary_rendered: Same as above except for the secondary text.
 * - $picture: A picture to use with this cell.
 *
 * @see template_preprocess_gridselect_cell_data
 */
?>
<?php if (isset($picture)): ?>
  <span class="avatar" style="background-image: url(<?php print $picture; ?>);"></span>
<?php endif; ?>
<?php if (isset($primary_rendered)): ?>
 <span class="primary"><?php print $primary_rendered; ?></span>
<?php endif; ?>
<?php if (isset($secondary_rendered)): ?>
  <span class="secondary"><?php print $secondary_rendered; ?></span>
<?php endif; ?>
