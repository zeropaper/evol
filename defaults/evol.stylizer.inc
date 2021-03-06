<?php
// $Id: $

/**
 * @file
 * Bulk export of stylizer objects generated by Bulk export module.
 */

/**
 * Implementation of hook_default_stylizer()
 */
function evol_default_stylizer() {
  $styles = array();

  $style = new stdClass;
  $style->disabled = FALSE; /* Edit this to true to make a default style disabled initially */
  $style->api_version = 1;
  $style->name = 'evol';
  $style->admin_title = 'Evol';
  $style->admin_description = '';
  $style->settings = array(
    'name' => 'evol',
    'style_base' => 'pane_rounded_shadow',
    'palette' => array(
      'background' => '#FFFFFF',
      'text' => '#000000',
      'header-text' => '#000000',
      'header-border' => '#000000',
    ),
    'header_font' => array(
      'font' => '',
      'size' => '',
      'letter_spacing' => '3px',
      'word_spacing' => '',
      'decoration' => '',
      'weight' => '',
      'style' => '',
      'variant' => 'small-caps',
      'case' => '',
      'alignment' => '',
    ),
    'text_font' => array(
      'font' => 'Trebuchet MS, Trebuchet, Verdana, sans-serif',
      'size' => '',
      'letter_spacing' => '',
      'word_spacing' => '',
      'decoration' => '',
      'weight' => '',
      'style' => '',
      'variant' => '',
      'case' => '',
      'alignment' => '',
    ),
    'padding' => array(
      'top' => '',
      'right' => '',
      'bottom' => '',
      'left' => '',
    ),
    'header_border' => array(
      'thickness' => '',
      'style' => '',
    ),
  );
  $styles['evol'] = $style;

  return $styles;
}
