<?php /* $Id: page.tpl.php,v 1.1 2009/12/29 06:07:29 merlinofchaos Exp $ */ ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
  "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html
  xmlns="http://www.w3.org/1999/xhtml"
  xml:lang="<?php print $language->language ?>"
  lang="<?php print $language->language ?>"
  dir="<?php print $language->dir ?>"
  <?php if($fb_enable) { print 'xmlns:fb="http://www.facebook.com/2008/fbml"'; } ?>>
<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyled Content in IE */ ?> </script>
</head>
<body class="<?php print $body_classes; ?>">
  <?php print $content; ?>
  <?php print $closure;?>
</body>
</html>
