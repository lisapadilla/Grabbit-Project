<?php
// $Id$

/**
 * @file
 * Outputs contents of nodes
 *
 * @see template_preprocess_node(), preprocess/preprocess-node.inc
 * http://api.drupal.org/api/function/template_preprocess_node/6
 */
?>
<div<?php print $attributes; ?>>
    <div class="meta">
      <?php if ($submitted): ?>
      <?php print $picture; ?>
      <?php endif; ?>
      <?php if (!$page && $title): ?>
      <div class="content-floated-left">
	    <h2><a href="<?php print $node_url; ?>" title="<?php print $title; ?>"><?php print $title; ?></a></h2>
	  </div>
      <div class="content-floated-right">
      <?php print $content; ?>
      <?php endif; ?>
      <?php if ($submitted): ?>
        <p><?php print $submitted; ?></p>
      <?php endif; ?>
      <?php if ($links): ?>
	    <div class="links">
	      <?php print $links; ?>
	    </div>
	  <?php endif; ?>
      </div>
    </div>

</div>