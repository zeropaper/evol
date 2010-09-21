<?php
// $Id: evol-admin.tpl.php,v 1.1 2010/01/11 06:37:09 merlinofchaos Exp $
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * additional areas for the header and the footer.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['header']: Content in the header row.
 *   - $content['left']: Content in the left column.
 *   - $content['content']: Main content area.
 *   - $content['right']: Content in the right column.
 *   - $content['footer']: Content in the footer row.
 */
?>
<div class="evol-panels-admin">
  <div class="evol-sticky-root evol-layout-wrapper">
    <div id="header-wrapper">
      <?php print $content['header']; ?>
    </div>
    <div id="content-wrapper" class="<?php print $evol_classes; ?>">
      <?php if ($content['left']): ?>
        <div id="sidebar-left">
          <div class="inside"><?php print $content['left']; ?></div>
        </div>
      <?php endif; ?>
      
      <div id="content">
        <div class="inside"><?php print $content['content']; ?></div>
      </div>
  
      <?php if ($content['right']): ?>
        <div id="sidebar-right">
          <div class="inside"><?php print $content['right']; ?></div>
        </div>
      <?php endif; ?>
    </div>
    <div class="evol-sticky-root-footer"><!--  --></div>
  </div>
  
  <div id="footer-wrapper" class="evol-sticky-footer clear-block">
    <div class="inside"><?php print $content['footer']; ?><!--  --></div>
  </div>
</div>