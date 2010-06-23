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
 */
function _evol_search_functions($file = NULL, $clear = FALSE) {
  global $_theme_scan;
  $theme = $_theme_scan;
  
  static $files = array();
  
  if ($clear) {
    $files = array();
  }
  
  if ($file) {
    include $file;
    $new = array();
    $base = array(
      'file' => basename($file),
      'path' => dirname($file),
    );
    
    $base = array (
      'arguments'             => array(),
      'file'                  => basename($file),
      'include files'         => array($file),
      'path'                  => dirname($file),
//      'pattern'               => 'pattern',
//      'preprocess functions'  => 'preprocess functions',
      'theme path'            => dirname($file),
      'theme paths'           => array(dirname($file)),
//      'type'                  => 'type'
    );
            
    $exp = "/function (theme|template|{$theme})(_preprocess|)_([^(]*)\((.*)\)[\\s]*{.*/";
    $exp = "/function (theme|template|{$theme})(_preprocess|)_([^(]*)\((.*)\)[\\s]*{(.*)/";
    
    
    $callbacks = array();
    if ($content = file_get_contents($file)) {
      $found = preg_match_all($exp, $content, $callbacks);
      if ($found) {
        foreach ($callbacks[3] as $i => $hook) {
          if ($hook) {
            if ($callbacks[2][$i] != '_preprocess') {
              $new[$hook] = array(
                'function'  => $callbacks[1][$i] .'_'. $hook,
                'arguments' => _evol_search_functions_clean_args($callbacks[4][$i]),
              ) + $base;
            }
            else {
              $definition = array(
                'template' => str_replace('_', '-', $hook),
              );
              // in the case of a preprocess theming, the arguments might be defined as comments after the "{"
              // example:
              // function mytheme_preprocess_myhook() {//$arg1, $arg2
              $args_string = trim(substr($callbacks[5][$i], 2));
              $args = _evol_search_functions_clean_args($args_string);
              if (count($args)) {
//                zdpm($hook .' argument(s): '. implode(', ', array_keys($args)));
                $definition['arguments'] = $args;
              }
              $new[$hook] = $definition + $base;
            }
          }
        }
//        if ($theme != 'evol') {
//          zdpm($new[$hook]);
//        }
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
      $args[$arg[0]] = isset($arg[1]) && $arg[1] ? $arg[1] : NULL;
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
  global $_theme_scan;
  $_theme_scan = $theme;
  
  // clears the $_theme_scan
  _evol_search_functions(NULL, TRUE);
  
  // search the implementations
  file_scan_directory($path .'/templates', '.inc', array('.', '..', 'CVS', '.svn'), '_evol_search_functions');
  $overrides = (array)_evol_search_functions();
    
  $new = array();
  
  foreach ($overrides as $hook => $params) {
    
    
    $params['type'] = $type;
    
    // if the isn't found within the registry, it's considered as "new"
    if (!isset($registry[$hook])) {
      
      $new[$hook] = $params;
      
    }
    else {
      
      $registry[$hook]['type'] = $params['type'];
//      $registry[$hook]['path'] = $params['path'];
//      $registry[$hook]['file'] = $params['file'];
//      $registry[$hook]['theme path'] = $params['path'];
      
      _evol_add_unique_at_end('./'. $params['path'] .'/'. $params['file'], $registry[$hook]['include files']);
      
      _evol_add_unique_at_end($params['path'], $registry[$hook]['theme paths']);
      
      _evol_add_unique_at_end($theme .'_preprocess_'. $hook, $registry[$hook]['preprocess functions']);
    }
    
  }

  
  // The following lines are aimed to make the themes playing nicely with
  // panels_everywhere module
  $page = &$registry['page'];
  
  $page['path'] = $path . '/templates';
  
  
  if (module_exists('panels_everywhere') && variable_get('panels_everywhere_site_template_enabled', FALSE)) {
    if (!file_exists($page['path'] .'/panels-everywhere-page.tpl.php')) {
      $page['path'] = drupal_get_path('module', 'panels_everywhere') . '/theme';
      $page['template'] = 'page';
    }
    else {
      $page['template'] = 'panels-everywhere-page';
      _evol_add_unique_at_end($path .'/templates/page.inc', $page['include files']);
    }
    
    // Blocks by default is something who should not happend (IMO)
    // 
    // $overrides['page']['arguments']['show_blocks'] = FALSE;
    $page['arguments']['show_blocks'] = FALSE;
    
    _evol_add_unique_at_end($page['path'], $page['theme paths']);
    _evol_add_unique_at_end($theme .'_preprocess_page', $page['preprocess functions']);
  }
  
  
//  zdpm("\n--------\nFOUND:\n". implode("\n", array_keys($overrides)) ."\n--------\nNEW:\n". implode("\n", array_keys($new)));
  return $new;
}

function _evol_add_unique_at_end($value, &$array) {
  $found = array_search($value, $array);
  if ($found !== FALSE) {
//    zdpm($value .' found at '. $found);
    unset($array[$found]);
  }
  $array[] = $value;
}