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
  //if (!function_exists('evol_settings_default')) {
  //  include_once drupal_get_path('theme', 'evol') .'/includes/settings.inc';
  //}
  $defaults = array(
    'stylesheets' => array(
      'reset.css' => 'reset.css',
      'forms.css' => 'forms.css',
      'messages.css' => 'messages.css',
      'style.css' => 'style.css'
    ),
  );//evol_settings_default();
  
  // Merge the saved variables and their default values
  $settings = array_merge($defaults, $saved_settings);
  
  // Create the form using Forms API: http://api.drupal.org/api/6
  $form = array();
  
  $form['#element_validate'][] = 'evol_settings_validate';
  
//  $form['compass'] = array(
//    '#type' => 'fieldset',
//    '#tree' => TRUE,
//    '#title' => 'compass',
//  );
//  $form['compass']['include_paths'] = array(
//    '#type' => 'textarea',
//    '#title' => t('Include paths'),
//    '#default_value' => $settings['compass']['include_paths'],
//    '#description' => t('One path per line. Start path with "/" for an absolute path.'),
//  );
  
  $form['stylesheets'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Stylesheets'),
    '#options' => array(
      'reset.css' => t('Reset stylesheet'),
      'style.css' => t('Evol base style'),
      'messages.css' => t('Evol messages'),
      'forms.css' => t('Evol forms'),
    ),
    '#default_value' => (array)$settings['stylesheets'],
  );
  
  
  
  
  return $form;
}

/**
 * Validation function for the theme settings form
 * @param structured array $form
 * @param array $form_state
 */
function evol_settings_validate(&$form, &$form_state) {
//  zdpm($form_state);
}