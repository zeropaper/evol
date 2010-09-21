<?php
// $Id:$
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html
  xmlns="http://www.w3.org/1999/xhtml"
  xml:lang="<?php print $language->language ?>"
  lang="<?php print $language->language ?>"
  dir="<?php print $language->dir ?>"
  <?php if(module_exists('fb')) { print 'xmlns:fb="http://www.facebook.com/2008/fbml"'; } ?>>

<head>
  <title><?php print $head_title; ?></title>
  
  <?php print $head; ?>
  
  <?php print $styles; ?>
  
  <?php print $designkit; ?>
  
  <?php print $scripts; ?>
  
</head>

<body class="<?php print $body_classes; ?>">
  <?php if ($admin) {print $admin;} ?>
  
  
  
  
  <div id="page">
    <div id="page-grid" class="<?php if (isset($nst_grid_name)) { print $nst_grid_name; } ?> clear-block">
      <div id="page-inner" <?php if (isset($nst_grid_columns)){ print 'class="grid-'. $nst_grid_columns .'"'; } ?>>
        
        <?php if ($title) { ?><h1 id="page-title"><?php print $title; ?></h1><?php } ?>
        
        <?php print $tabs; ?>
          
        <?php print $breadcrumb; ?>
        
        <?php if ($messages) { print $messages; } ?>
        
        <div id="page-content">
          <?php print $content; ?>
        </div>
        <div id="page-footer">
        </div>
      </div>
    </div>
  </div>
  
  <div id="footer">
    <div id="footer-grid" class="<?php if ($nst_grid_name) {print $nst_grid_name;} ?> clear-block">
      <div id="footer-inner" <?php if ($nst_grid_columns){ print 'class="grid-'. $nst_grid_columns .'"'; } ?>>
        
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
  if (module_exists('fb')) { ?>
  <!-- http://wiki.developers.facebook.com/index.php/JavaScript_Client_Library -->  
  <div id="FB_HiddenIFrameContainer" style="display:none; position:absolute; left:-100px; top:-100px; width:0px; height: 0px;"></div>
  <?php }
  ?>
</body>
</html>