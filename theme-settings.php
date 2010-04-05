<?php

/**
 * Theme settings form
 * @param array $saved_settings
 * @return structured FAPI array
 */
function evol_settings($saved_settings) {
  global $theme;
  // The default values for the theme variables. Make sure $defaults exactly
  // matches the $defaults in the template.php file.
  if (!function_exists('evol_settings_default')) {
    include_once drupal_get_path('theme', 'evol') .'/includes/settings.inc';
  }
  $defaults = evol_settings_default();
  
  // Merge the saved variables and their default values
  $settings = array_merge($defaults, $saved_settings);
  
  // Create the form using Forms API: http://api.drupal.org/api/6
  $form = _evol_page_style_settings_form($settings);
  
  return $form;
}

/**
 * Validation function for the theme settings form
 * @param structured array $form
 * @param array $form_state
 */
function evol_settings_validate(&$form, &$form_state) {
//  ztools_theme_setting_form_validate($form, $form_state);
}

/**
 * Submit handler for the theme settings form
 * @param structured array $form
 * @param array $form_state
 */
function evol_settings_submit(&$form, &$form_state) {
//  ztools_theme_setting_form_submit($form, $form_state);
}
