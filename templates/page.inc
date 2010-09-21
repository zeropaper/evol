<?php

/**
 * Add a piece of CSS code who will afterward processed
 * within theme('designkit')
 * @param string $id
 * @param string $code
 */
function evol_add_css_code($id = NULL, $code = NULL) {
  static $static = array();
  if (empty($id)) {
    return implode("\n/*  */\n", $static);
  }
  $static[$id] = $code;
}

/**
 * Preprocessor for page.tpl.php template file.
 */
function evol_preprocess_page(&$vars, $hook) {
  if (function_exists('designkit_preprocess_page')) {
    call_user_func_array('designkit_preprocess_page', $vars);
  }
  
  if (module_exists('jquery_update')) {
    jquery_update_preprocess_page($vars);
  }
  
  $evol_styles_path = drupal_get_path('theme', 'evol') .'/styles';
  $evol_styles = theme_get_setting('stylesheets');
  
  
  $modules_css = &$vars['css']['all']['module'];
  $additionals = array();
  if ($evol_styles['reset.css']) {
    $additionals[$evol_styles_path .'/reset.css'] = TRUE;
  }
  $modules_css = array_merge($additionals, $modules_css);
  
  
  $themes_css = &$vars['css']['all']['theme'];
  $additionals = array();
  foreach ($evol_styles as $style => $check) {
    if ($style != 'reset.css' && $style == $check) {
      $additionals[$evol_styles_path .'/'. $check] = TRUE;
    }
  }
  $themes_css = array_merge($additionals, $themes_css);
  
  $vars['styles'] = drupal_get_css($vars['css']);
  
  $vars['designkit'] = !empty($vars['designkit']) ? $vars['designkit'] : theme('designkit');
  
  
  if (isset($vars['admin']) && module_exists('panels_everywhere') && variable_get('panels_everywhere_site_template_enabled', FALSE)) {
    $vars['content'] = $vars['admin'] . $vars['content'];
    unset($vars['admin']);
  }
  
  // http://wiki.developers.facebook.com/index.php/JavaScript_Client_Library
  if ($vars['fb_enable']) {
    $vars['closure'] .= '<div id="FB_HiddenIFrameContainer" style="display:none; position:absolute; left:-100px; top:-100px; width:0px; height: 0px;"><!-- --></div>';
  }
  
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