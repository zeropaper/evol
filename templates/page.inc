<?php

/**
 * Preprocessor for page.tpl.php template file.
 */
function evol_preprocess_page(&$vars, $hook) {
  // uncomment if you do understand what will happen
  // or set the ztools_use_reset_css variable to TRUE if zTools is installed
  #drupal_set_html_head('<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . drupal_get_path('theme', 'evol') .'/styles/reset.css" />');
  #$vars['head']                 = drupal_get_html_head();
  
  evol_body_classes($vars['body_classes'], $vars);
//  $vars['content'] = '<pre style="font-size:x-small">'. htmlentities(var_export(array_keys($vars), TRUE)) .'</pre>'. $vars['content'];
  
  // http://wiki.developers.facebook.com/index.php/JavaScript_Client_Library
  if ($vars['fb_enable']) {
    $vars['closure'] .= '<div id="FB_HiddenIFrameContainer" style="display:none; position:absolute; left:-100px; top:-100px; width:0px; height: 0px;"><!-- --></div>';
  }
  
}

function evol_body_classes(&$body_classes, $vars) {
  $classes = explode(' ', $body_classes);
  $vars['fb_enable'] = module_exists('fb');
//  $vars['fb_active'] = (theme_get_setting('fb_active') && $vars['fb_enable']);
  
  if (theme_get_setting('show_grid_helper')) {
    $classes[] = 'show-grid-helper';
  }
  
  // helps avoiding IE fixes with an other stylesheet and such
  if (function_exists('browscap_get_browser')) {
    $browser = browscap_get_browser();
    $classes[] = 'browser-'. strtolower(check_plain($browser['browser']));
  }
  
  $body_classes = implode(' ', array_unique($classes));
  
}


function evol_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    foreach ($breadcrumb as $l => $link) {
      $first_last  = '';
      if ($l == 0) {
        $first_last .= ' first';
      }
      if ($l == count($breadcrumb)-1) {
        $first_last .= ' last';
      }
      $breadcrumb[$l] = '<span class="breadcrumb-'. $l . $first_last .'">'. $link .'</span>';
    }
    return '<div class="breadcrumb">'. implode(' <span class="separator">»</span> ', $breadcrumb) .'</div>';
  }
}