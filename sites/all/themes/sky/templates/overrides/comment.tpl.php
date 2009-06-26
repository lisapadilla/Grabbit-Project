<?php
// $Id$

/**
 * @file
 * Output of comment content.
 *
 * @see template_preprocess_comment(), preprocess/preprocess-block.inc
 * http://api.drupal.org/api/function/template_preprocess_comment/6
 */
?>
<div<?php print $attributes; ?>>
<!-- start comment.tpl.php -->
<?php if ($title): ?>
  <div class="inner">
    <span class="title"> <?php print $title; ?>
    <?php if ($comment->new): ?>
      <span class="new"><?php print $new; ?></span>
    <?php endif; // end "new" check ?>
    </span>
  <?php endif; // end "title" check ?>
  <div class="content"><?php print $content; ?></div>
  <?php if ($submitted): ?>
    <div class="info"><?php print $picture ?> <?php print 'Posted by '.  $author; ?> on <?php print $date; ?> </div>
  <?php endif; ?>
  </div>
<?php print $links; ?>
</div>
<!-- end comment.tpl.php -->