<?php
// $Id: evol.inc,v 1.2 2010/07/26 18:24:27 merlinofchaos Exp $

/**
 * Implementation of hook_panels_layouts().
 */
$plugin = array(
  'title' => t('Evol'),
  'category' => t('Theme: Evol'),
  'icon' => 'evol.png',
  'theme' => 'evol',
  'admin theme' => 'evol_admin',
  'css' => 'evol.css',
  'admin css' => 'evol-admin.css',
  'panels' => array(
    'header' => t('Header'),
    'left' => t('Left sidebar'),
    'content' => t('Content'),
    'right' => t('Right sidebar'),
    'footer' => t('Footer')
  ),
);

/**
 * Override or insert evol variables into the templates.
 */
function template_preprocess_evol(&$vars) {
  $vars['evol_classes'] = '';
  if ($vars['content']['left'] != '' && $vars['content']['right'] != '') {
    $vars['evol_classes'] = 'sidebars';
  }
  else {
    if ($vars['content']['left'] != '') {
      $vars['evol_classes'] .= ' sidebar-left';
    }
    if ($vars['content']['right'] != '') {
      $vars['evol_classes'] .= ' sidebar-right';
    }
  }
}
