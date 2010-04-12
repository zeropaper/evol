<?php

/**
 * implementation of hook_panels_layouts
 */
function evol_base_panels_layouts() {
  $items['base'] = array(
    'title' => t('Evol base'),
    'icon' => 'base.png',
    'theme' => 'base',
    'css' => 'base.css',
    'theme arguments' => array('id', 'content'),
    'panels' => array(
      'top' => t('Top'),
      'middle' => t('Middle'),
      'bottom' => t('Bottom')
    ),
  );

  return $items;
}

