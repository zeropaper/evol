<?php
function evol_preprocess_designkit(&$vars) {
  $vars['compiled_filepath'] = FALSE;
  $vars['color_coding'] = '';
  
  $color = (array)theme_get_setting('designkit_color');
  $color_coding = array();
  foreach ($color as $name => $info) {
    if (strpos($name, 'cc_') === 0) {
      $color_code[str_replace('cc_', '', $name)] = $info;
      unset($color[$name]);
    }
  }
  $image = theme_get_setting('designkit_image');
  
  // retrieve the css_code
  // @see evol_add_css_code()
  $added = theme('add_css_code');
  if (function_exists('ctools_include') && $added) {
    ctools_include('css');
    $vars['compiled_filepath'] = ctools_css_store('designkit-evol-'. md5($added), $added, FALSE);
//    drupal_add_css($vars['compiled_path'], 'theme', 'all');
    $added = $vars['compiled_filepath'] ? '' : $added;
  }
  $vars['added'] = $added;
//  $vars['debug'] = var_export($vars, TRUE);
}