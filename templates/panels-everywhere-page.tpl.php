<?php /* $Id: page.tpl.php,v 1.1 2009/12/29 06:07:29 merlinofchaos Exp $ */ ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html
  xmlns="http://www.w3.org/1999/xhtml"
  xml:lang="<?php print $language->language ?>"
  lang="<?php print $language->language ?>"
  dir="<?php print $language->dir ?>"
  <?php if($fb_enable) { print 'xmlns:fb="http://www.facebook.com/2008/fbml"'; } ?>>
<!-- Evol for panels everywhere -->
<head>
  <title><?php print $head_title; ?></title>
  
  <?php print $head; ?>
  
  <?php print $styles; ?>
  
  <?php print $designkit; ?>
  
  <?php print $scripts; ?>
  
</head>
<body class="<?php print $body_classes; ?>">
  <?php print $content; ?>
  <!-- /content -->
  <!-- closure -->
  <?php print $closure;?>
</body>
</html>
