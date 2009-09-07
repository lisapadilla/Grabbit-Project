<?php if (!$advanced): ?>
  <?php print drupal_render($form); ?>
<?php else: ?>
  <?php $form['dcl_importer']['#access'] = FALSE; ?>
  <?php //print drupal_render($form['import_form']); ?>
  <?php print drupal_render($form); ?>
<?php endif; ?>
