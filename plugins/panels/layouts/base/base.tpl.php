<?php
/**
 * @file
 * Template for 3 column panel layout.
 *
 * This template provides a three column 50%-25%-25% panel display layout.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the left column.
 *   - $content['middle']: Content in the middle column.
 *   - $content['bottom']: Content in the right column.
 */
?>
<div class="evol-base" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="evol-base-top" <?php if (!empty($css_id)) { print "id=\"$css_id-top\""; } ?>>
    <div class="inside"><?php print $content['top']; ?></div>
    <div class="shadow"><!-- shadow --></div>
  </div>

  <div class="evol-base-middle" <?php if (!empty($css_id)) { print "id=\"$css_id-middle\""; } ?>>
    <div class="hat"><!-- hat --></div>
    <div class="inside"><?php print $content['middle']; ?></div>
  </div>
  
  <div class="evol-base-pusher"><!--  --></div>
</div>
  
<div class="evol-base-bottom" <?php if (!empty($css_id)) { print "id=\"$css_id-bottom\""; } ?>>
  <div class="inside"><?php print $content['bottom']; ?></div>
</div>