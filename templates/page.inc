<?php


function evol_add_css_code($id = NULL, $code = NULL) {
  static $static = array();
  $dbg = debug_backtrace();
//  zdpm($dbg[2]['args'][1] ."\n". $code);
  if (empty($id)) {
//    $output = '';
//    foreach ($static as $id => $code) {
//      $output .= "\n/* $id */\n";
//    }
    return implode("\n/*  */\n", $static);
  }
//  if (!array_key_exists($id, $static)) {
//    zdpm($id .': '. $code);
//  }
  $static[$id] = $code;
}

/**
 * Preprocessor for page.tpl.php template file.
 */
function evol_preprocess_page(&$vars, $hook) {
  
  
  
  // make a deep clean reset of the style by adding the reset stylesheet before all others
  drupal_set_html_head('<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . drupal_get_path('theme', 'evol') .'/styles/reset.css" />');
  $vars['head'] = drupal_get_html_head();
  
//  zdpm(module_exists('jquery_update'), function_exists('jquery_update_preprocess_page'));
  if (module_exists('jquery_update')) {
    jquery_update_preprocess_page($vars);
  }
  
  if (isset($vars['admin']) && module_exists('panels_everywhere') && variable_get('panels_everywhere_site_template_enabled', FALSE)) {
    $vars['content'] = $vars['admin'] . $vars['content'];
    unset($vars['admin']);
  }
  
  // http://wiki.developers.facebook.com/index.php/JavaScript_Client_Library
  if ($vars['fb_enable']) {
    $vars['closure'] .= '<div id="FB_HiddenIFrameContainer" style="display:none; position:absolute; left:-100px; top:-100px; width:0px; height: 0px;"><!-- --></div>';
  }
  
  $vars['designkit'] = theme('designkit');
  evol_body_classes($vars['body_classes'], $vars);
}

function evol_body_classes(&$body_classes, $vars) {
  $classes = explode(' ', $body_classes);
  if (module_exists('domain')) {
  	$domain = domain_get_domain();
  	$classes[] = 'active-domain-'. $domain['domain_id'];
  }
  $vars['fb_enable'] = module_exists('fb');
  
  if (theme_get_setting('show_grid_helper')) {
    $classes[] = 'show-grid-helper';
  }
  
  // helps avoiding IE fixes with an other stylesheet and such
  if (function_exists('browscap_get_browser')) {
    $browser = browscap_get_browser();
    $classes[] = 'browser-'. $browser['browser'];
  }
  
  if (isset($vars['node']) && $vars['node']->nid) {
    $classes[] = 'node-'. $vars['node']->nid;
    $classes[] = 'node-'. $vars['node']->type;
  }
  
  if (isset($vars['user']) && $vars['user']->uid) {
    $classes[] = 'user-'. $vars['user']->uid;
    $classes[] = 'user-role-'. implode(' user-role-', $vars['user']->roles);
  }
  
  foreach ($classes as $c => $class) {
    $classes[$c] = trim(preg_replace('/[^a-z0-9- ]+/', '-', strtolower($class)));
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