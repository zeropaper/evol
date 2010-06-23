<?php
// $Id$

/**
 * Initialize theme settings
 */
if (is_null(theme_get_setting('show_grid'))) {
  global $theme_key;
  evol_include('settings');
  // The default values for the theme variables. Make sure $defaults exactly
  // matches the $defaults in the theme-settings.php file.
  if (!function_exists('evol_settings_default')) {
    include_once drupal_get_path('theme', 'evol') .'/includes/settings.inc';
  }
  // Using function_exists() to prevent a possible bug if the theme is used as maintenance theme at install
  include_once dirname(__FILE__) .'/includes/settings.inc';
  $defaults = function_exists('evol_settings_default') ? evol_settings_default() : array();

  // Get default theme settings.
  $settings = theme_get_settings($theme_key);
  // Don't save the toggle_node_info_ variables.
  if (module_exists('node')) {
    foreach (node_get_types() as $type => $name) {
      unset($settings['toggle_node_info_' . $type]);
    }
  }
  
  // Save default theme settings.
  variable_set(
    str_replace('/', '_', 'theme_'. $theme_key .'_settings'),
    array_merge($defaults, $settings)
  );
  
  // Force refresh of Drupal internals.
  theme_get_setting('', TRUE);
}


/**
 * Implementation of the hook_theme()
 * @param array $existing
 * @param string $type
 * @param string $theme
 * @param string $path
 * @return array
 *  An array with the new/overrided themeing functions
 * 
 * @see hook_theme()
 */
function evol_theme(&$registry, $type, $theme, $path) {
  evol_include('theme_registry');
  $new = _evol_theme($registry, $type, $theme, $path);
  return $new;
}

/**
 * Implements hook_preprocess()
 * 
 * @param array $vars
 *  An array (reference) containing the variables who will be made available in your .tpl.php files
 * @param string $hook
 */
//function evol_preprocess(&$vars, $hook) {
//  global $theme_key, $theme_info;
//  
//  static $loaded = array();
//  if (empty($loaded[$hook])) {
//    zdpm($hook .': '. $theme_key);
//    evol_include($hook);
//    evol_template($hook);
//    evol_include($hook, $theme_key);
//    evol_template($hook, $theme_key);
//    $loaded[$hook] = TRUE;
//  }
//}




/**
 * Contextually adds 960 Grid System classes.
 *
 * The first parameter passed is the *default class*. All other parameters must
 * be set in pairs like so: "$variable, 3". The variable can be anything available
 * within a template file and the integer is the width set for the adjacent box
 * containing that variable.
 *
 *  class="<?php print evol('grid-16', $var_a, 6); ?>"
 */
function evol() {
  $args = func_get_args();
  $default = array_shift($args);
  // Get the type of class, i.e., 'grid', 'pull', 'push', etc.
  // Also get the default unit for the type to be procesed and returned.
  list($type, $return_unit) = explode('-', $default);

  // Process the conditions.
  $flip_states = array('var' => 'int', 'int' => 'var');
  $state = 'var';
  foreach ($args as $arg) {
    if ($state == 'var') {
      $var_state = !empty($arg);
    }
    elseif ($var_state) {
      $return_unit = $return_unit - $arg;
    }
    $state = $flip_states[$state];
  }

  $output = '';
  // Anything below a value of 1 is not needed.
  if ($return_unit > 0) {
    $output = $type . '-' . $return_unit;
  }
  return $output;
}

function _evol_css_safe($string) {
  return str_replace('_', '-', $string);
//  return function_exists('views_css_safe') ? views_css_safe($string) : str_replace('_', '-', $string);
}


function _evol_add_template(&$vars, $hook) {
  $template_hook = _evol_css_safe($hook);
  $vars['template_files'][] = $template_hook;
  
  if (strpos($template_hook, 'views-view') === 0 && isset($vars['view'])) {
    $vars['template_files'] = array();
    $vars['template_files'][] = _evol_css_safe($template_hook .'--'. $vars['view']->name);
    $vars['template_files'][] = _evol_css_safe($template_hook .'--'. $vars['view']->name .'--'. $vars['view']->display[$vars['view']->current_display]->display_plugin);
    $vars['template_files'][] = _evol_css_safe($template_hook .'--'. $vars['view']->name .'--'. $vars['view']->current_display);
    $vars['template_files'] = array_unique($vars['template_files']);
  }
  
  if (isset($vars['account']) && $vars['account']->uid) {
    $vars['template_files'][] = _evol_css_safe($template_hook .'--uid-'. $vars['account']->uid);
  }
  
  if (isset($vars['node'])) {
    $vars['template_files'][] = _evol_css_safe($template_hook .'-'. $vars['node']->type);
    $vars['template_files'][] = _evol_css_safe($template_hook .'-nid-'. $vars['node']->nid);
  }
}

function evol_include($hook, $theme = 'evol') {
  $path = ($theme == 'evol' ? dirname(__FILE__) : drupal_get_path('theme', $theme)) .'/includes';
  $filepath = $path .'/'. $hook .'.inc';
  if (file_exists($filepath)) {
    include_once $filepath;
    return TRUE;
  }
  return FALSE;
}

function evol_template($hook, $theme = 'evol') {
  $path = drupal_get_path('theme', $theme) .'/templates';
  $filepath = $path .'/'. $hook .'.inc';
  if (file_exists($filepath)) {
    include_once $filepath;
  }
}

//function evol_add_js($hook, $scope = 'header', $defer = FALSE, $cache = TRUE, $preprocess = TRUE) {
//  $path = drupal_get_path('theme', 'evol') .'/scripts';
//  drupal_add_js($path .'/'. $hook .'.js', 'theme', $scope, $defer, $cache, $preprocess);
//}


function evol_add_js($file, $module = 'evol', $dir = 'js') {
  zdpm($file .' '. $theme .' '. $dir .' '. $media);
  drupal_add_js(drupal_get_path('theme', $theme) . "/$dir/$file.js");
}



function evol_add_css($hook, $theme = 'evol', $dir = 'css', $media = 'all', $preprocess = TRUE) {
  // ensure backward compatibility
  if ($theme == 'evol') {
    $dir = 'styles';
  }
  zdpm($hook .' '. $theme .' '. $dir .' '. $media);
  $path = drupal_get_path('theme', $theme) .'/'. $dir;
  drupal_add_css($path .'/'. $hook .'.css', 'theme', $media, $preprocess);
}

/**
 * Overwrite theme_image()
 * 
 * @param string $path
 * @param string $alt
 * @param string $title
 * @param array $attributes
 * @return string
 * 
 * @see theme_image()
 */
function evol_image($path, $alt = '', $title = '', $attributes = NULL) {
  $attributes = drupal_attributes($attributes);
  $url = (url($path) == $path) ? $path : (base_path() . $path);
  
  return '<img src="'. check_url($url) .'" alt="'. check_plain($alt) .'" title="'. check_plain($title) .'" '. drupal_attributes($attributes) .' />';
}



/**
 * Create and image tag for an imagecache derivative
 *
 * @param $presetname
 *   String with the name of the preset used to generate the derivative image.
 * @param $path
 *   String path to the original image you wish to create a derivative image
 *   tag for.
 * @param $alt
 *   Optional string with alternate text for the img element.
 * @param $title
 *   Optional string with title for the img element.
 * @param $attributes
 *   Optional drupal_attributes() array. If $attributes is an array then the
 *   default imagecache classes will not be set automatically, you must do this
 *   manually.
 * @param $getsize
 *   If set to TRUE, the image's dimension are fetched and added as width/height
 *   attributes.
 * @return
 *   HTML img element string.
 */
function evol_imagecache($presetname, $path, $alt = '', $title = '', $attributes = NULL, $getsize = TRUE) {
  // Check is_null() so people can intentionally pass an empty array of
  // to override the defaults completely.
  if (is_null($attributes)) {
    $attributes = array('class' => 'imagecache imagecache-'. $presetname);
  }
  if ($getsize && ($image = image_get_info(imagecache_create_path($presetname, $path)))) {
    $attributes['width'] = $image['width'];
    $attributes['height'] = $image['height'];
  }

  $attributes = drupal_attributes($attributes);
  $imagecache_url = imagecache_create_url($presetname, $path);
  
  return '<img src="'. $imagecache_url .'" alt="'. check_plain($alt) .'" title="'. check_plain($title) .'" '. $attributes .' />';
}

function evol_preprocess_admin_toolbar(&$vars) {
  $vars['collapsed'] = TRUE;
  foreach ($vars['tree'] as $depth => $menus) {
    foreach ($menus as $href => $links) {
      $class = ($depth > 0) ? 'collapsed' : '';
      if ($depth > 0 && admin_in_active_trail($href)) {
        $class = '';
        $vars['collapsed'] = FALSE;
      }
      $id = str_replace('/', '-', $href);

      // If we aren't on the top level menu, provide a way to get to the top level page.
      if ($depth > 0 && !empty($links)) {
        $links['view-all'] = array(
          'title' => t('View all'),
          'href' => $href,
        );
      }
      // fix the HTML...
      foreach ($links as &$link) {
        $link['title'] = str_replace("<span class='icon'></span>", '<span class="icon"><!--  --></span>', $link['title']);
      }
      $vars["tree_{$depth}"][$id] = theme('links', $links, array('class' => "links clear-block $class", 'id' => "admin-toolbar-{$id}"));
    }
  }
}
