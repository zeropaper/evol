<?php
// $Id:$
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html
  xmlns="http://www.w3.org/1999/xhtml"
  xml:lang="<?php print $language->language ?>"
  lang="<?php print $language->language ?>"
  dir="<?php print $language->dir ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>

<body class="<?php print $body_classes; ?>">
  <?php if ($admin) {print $admin;} ?>
  
  <div id="page">
    <div id="page-grid" class="<?php if ($nst_page_class) {print $nst_page_class;} ?> clear-block">
      <div id="page-inner" <?php if ($nst_page_class){ print 'class="grid-'. $nst_grid->get_columns() .'"'; } ?>>
        
        <?php if ($messages) { print $messages; } ?>
        
        <?php print $content; ?>
  
      </div>
    </div>
  </div>
  
  <div id="footer">
    <div id="footer-grid" class="<?php if ($nst_page_class) {print $nst_page_class;} ?> clear-block">
      <div id="footer-inner" <?php if ($nst_page_class){ print 'class="grid-'. $nst_grid->get_columns() .'"'; } ?>>
        
        <?php if ($footer): ?>
          <?php print $footer; ?>
        <?php endif; ?>
        
        <?php if ($feed_icons): ?>
          <?php print $feed_icons; ?>
        <?php endif; ?>
        
      </div>
    </div>
  </div>
  
  
  
  <?php
  // do NOT remove, do NOT place elsewhere, DO NOT EVEN THINK ABOUT IT!
  print $closure;
  ?>
</body>
</html>