<?php // $Id: block.tpl.php,v 1.1 2009/06/06 18:19:44 giorgio79 Exp $
/**
 * @file
 *  block.tpl.php
 *
 * Theme implementation to display a block.
 *
 * @see template_preprocess()
 * @see template_preprocess_block()
 */
?>
<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block <?php print $block_classes; ?>">
  <div class="block-inner-0"><div class="block-inner-1">
    <div class="block-inner-2"><div class="block-inner-3">
  <div class="block-inner">

    <?php if ($block->subject): ?>
      <h2 class="block-title"><?php print $block->subject; ?></h2>
    <?php endif; ?>

    <div class="block-content">
      <div class="block-content-inner">
        <?php print $block->content; ?>
      </div>
    </div>


  </div>

    </div></div>
  </div></div>

</div> <!-- /block -->