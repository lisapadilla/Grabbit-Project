<?php
// $Id: views-view-row-heartbeat.tpl.php,v 1.1.2.1 2009/01/22 21:39:26 stalski Exp $
/**
 * @file views-view-row-heartbeat.tpl.php
 * Default simple view template to display a single heartbeat.
 *
 * Rather than doing anything with this particular template, it is more
 * efficient to use a variant of the heartbeat.tpl.php based upon the view,
 * which will be named heartbeat-view-VIEWNAME.tpl.php. This isn't actually
 * a views template, which is why it's not used here, but is a template
 * 'suggestion' given to the heartbeat template, and is used exactly
 * the same as any other variant of the heartbeat template file, such as
 * heartbeat-heartbeat.tpl.php
 *
 * @ingroup views_templates
 */
?>
<?php print $row->message; ?>
  
<?php if ($info): ?>
  <?php print $info; ?>
<?php endif; ?>