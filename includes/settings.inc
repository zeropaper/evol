<?php
function evol_settings_default() {
  return array(
    'show_grid' => 0,
  );
}


function _evol_page_style_settings_form($settings) {
  $form = array();
  
  if (module_exists('filefield') || module_exists('text')) {
    $fields = content_fields();
    
    foreach ($fields as $field) {
      if ($field['module'] == 'filefield') {
        $bgk_options[$field['field_name']] = $field['widget']['label'];
      }
      elseif ($field['module'] == 'text') {
        $style_options[$field['field_name']] = $field['widget']['label'];
      }
    }
    
    
    if (count($bgk_options)) {
      $form['background_image'] = array(
        '#type'         => 'fieldset',
        '#tree'         => TRUE,
        '#title'        => t('Backgrounds'),
        '#description'  => '@todo description',
      );
      
      array_unshift($bgk_options, '- '. t('None') .' -');
      $form['background_image']['field'] = array(
        '#title'          => t('Image field'),
        '#type'           => 'select',
        '#options'        => $bgk_options,
        '#default_value'  => $settings['background_image']['field'],
      );
      
      if (module_exists('imagecache')) {
        
        $preset_options = array();
        foreach (imagecache_presets() as $preset_id => $preset) {
          $preset_options[$preset_id] = $preset_id;
        }
        
        if (count($preset_options)) {
          array_unshift($preset_options, '- '. t('None') .' -');
          $form['background_image']['preset'] = array(
            '#title'          => t('Image preset'),
            '#type'           => 'select',
            '#options'        => $preset_options,
            '#default_value'  => $settings['background_image']['preset'],
          );
        }
        
      }
      
    }
    
    if (count($style_options)) {
      array_unshift($style_options, '- '. t('None') .' -');
      $form['style_field'] = array(
        '#title'          => t('Background image field'),
        '#type'           => 'select',
        '#options'        => $style_options,
        '#default_value'  => $settings['style_field'],
      );
    }
    
  }
  
  return $form;
}