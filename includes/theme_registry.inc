<?php
//$callbacks = array();
//$theme = 'themename';
//
//$exp = "/function {$theme}_([^(]*)\((.*)\)[\\s]*{.*/";
//
//
//$content = "
//function themename_should_be_found_1(\$arg1, \$arg2 = array()) {
//
//function themename_should_be_found_2( ) {
//
//function themename_should_be_found_3() {
//
//function themename_should_be_found_4() {//
//
//function _themename_should_NOT_be_found() {
//
//}
//";
//
//$found = preg_match_all($exp, $content, $callbacks);
//zdpm($callbacks);
//return $found;

/**
 * Search for theme functions
 * At the moment, only "non-template" functions will be found
 */
function _evol_search_functions($file = NULL) {
  global $theme;
  static $files = array();
  
  if ($file) {
    include $file;
    $new = array();
    $base = array(
      'file' => basename($file),
      'path' => dirname($file),
    );
    
    $exp = "/function (theme|template|{$theme})(_preprocess|)_([^(]*)\((.*)\)[\\s]*{.*/";
    
    $callbacks = array();
    if ($content = file_get_contents($file)) {
      $found = preg_match_all($exp, $content, $callbacks);
      if ($found) {
        foreach ($callbacks[3] as $i => $hook) {
          if ($hook) {
            if ($callbacks[2][$i] != '_preprocess') {
              $new[$hook] = array(
                'function'  => $theme .'_'. $hook,
                'arguments' => _evol_search_functions_clean_args($callbacks[4][$i]),
              ) + $base;
            }
            else {
              $new[$hook] = array(
                'template' => str_replace('_', '-', $hook),
              ) + $base;
            }
          }
        }
      }
    }
    
    if (count($new)) {
      $files = array_merge($files, $new);
    }
  }
  
  return $files;
}

/**
 * Clean the arguments found by the _evol_search_functions() function
 * @param string $args_string
 *  Something like "$arg1, &$arg2, $arg3 = array()"
 * @return array
 *  An array with like array('arg1' => NULL, 'arg2' => NULL, 'arg3' => array())
 */
function _evol_search_functions_clean_args($args_string) {
  $args = array();
  foreach (array_map('trim', explode(',', $args_string)) as $arg) {
    $arg = explode('$', $arg);
    $arg = array_map('trim', explode('=', $arg[1]));
    if ($arg[0]) {
      $args[$arg[0]] = $arg[1] ? $arg[1] : NULL;
    }
  }
  return $args;
}

/**
 * Implementation of the hook_theme()
 * @param array $existing
 * @param string $type
 *  If Evol is used as main theme: "theme" should be passed here
 *  If Evol is used as base theme: "base_theme" should be passed
 * @param string $theme
 *  The name of the theme (should be "evol")
 * @param string $path
 *  Should be the path to evol
 * @return array
 *  An array containing the theme hooks
 *  
 *  @test
 *   <code>drupal_rebuild_theme_registry();
init_theme();
$reg = theme_get_registry();
$hooks = array(
'breadcrumb' => $reg['breadcrumb'],
'page' => $reg['page'],
//'node' => $reg['node'],
);
dpm($hooks);</code>
 *
 */
function _evol_theme(&$registry, $type, $theme, $path) {
  $new = array();
  file_scan_directory($path .'/templates', '.inc', array('.', '..', 'CVS', '.svn'), '_evol_search_functions');
  $overrides = (array)_evol_search_functions();
  
  foreach ($overrides as $hook => $params) {
    
    if (!isset($registry[$hook])) {
      $params['type'] = $type;
      $new[$hook] = $params;
      
      
    }
    else {
      
      $registry[$hook]['type'] = $type;
      $registry[$hook]['path'] = $path .'/templates';//$params['path'];
      $registry[$hook]['file'] = $params['file'];
      $registry[$hook]['include files'][] = $path .'/templates/'. $params['file'];
      $registry[$hook]['theme path'] = $params['path'];
      $registry[$hook]['theme paths'][] = $params['path'];
      $registry[$hook]['preprocess functions'][] = $theme .'_preprocess_'. $hook;
      
//      $new[$hook]['type'] = $params['theme'];
//      $new[$hook]['preprocess functions'] = array_merge($registry[$hook]['preprocess functions'], array($theme .'_preprocess_'. $hook));
    }
    
  }
  
  
  $registry['page']['path'] = drupal_get_path('theme', $theme) . '/templates';
  
  if (module_exists('panels_everywhere') && variable_get('panels_everywhere_site_template_enabled', FALSE)) {
    if (!file_exists($params['path'] .'/panels-everywhere-page.tpl.php')) {
      $registry['page']['path'] = drupal_get_path('module', 'panels_everywhere') . '/theme';
      $registry['page']['template'] = 'page';
    }
    else {
      $registry['page']['template'] = 'panels-everywhere-page';
      $registry['page']['include files'][] = $path .'/templates/page.inc';
    }
    
    $overrides['page']['arguments']['show_blocks'] = FALSE;
    
    
    if (isset($overrides['page'])) {
      if ($overrides['page']['path'] && !in_array($overrides['page']['path'], $registry['page']['theme paths'])) {
        $registry['page']['theme paths'][] = $overrides['page']['path'];
      }
      
      if ($key = array_search($theme .'_preprocess_page', $registry['page']['preprocess functions'])) {
        unset($registry['page']['preprocess functions'][$key]);
      }
      $registry['page']['preprocess functions'][] = $theme .'_preprocess_page';
    }
  }
  zdpm($registry['page']['preprocess functions']);
  return $new;
}