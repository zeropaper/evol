<?php
// $Id: $

/**
 * @file styles/evol_page/evol_page.inc
 * Definition of the style.
 * 
 * Based  on rounded_corner.inc from panels.module
 * 
 */

function evol_page_get_path($file, $base_path = FALSE, $theme = 'evol') {
  $output = $base_path ? base_path() : '';
  return $output . drupal_get_path('theme', $theme) . '/' . $file;
}

// ---------------------------------------------------------------------------
// Panels hooks.

/**
 * Implementation of THEME_STYLENAME_panels_style().
 * 
 * Where THEME is the theme name, and STYLENAME matches this inc filename.
 */
function evol_evol_page_panels_styles() {
  return array(
    'evol_page' => array(
      'title' => t('Evol default page style'),
      'description' => t('Should be used as base style for a site template layout.'),
      'render panel' => 'evol_evol_page_style_render_panel',
      'render pane' => 'evol_evol_page_style_render_pane',
      'settings form' => 'evol_evol_page_style_settings_form',
      'hook theme' => array(
        'evol_evol_page_box' => array(
          'arguments' => array('content' => NULL),
          'path' => evol_page_get_path('plugins/panels/styles/evol_page'),
          'template' => 'evol-page-box',
        ),
      ),
    ),
  );
}

// ---------------------------------------------------------------------------
// Panels style plugin callbacks.

/**
 * Render callback.
 * 
 * Declared by name in THEME_STYLENAME_panels_style() above.
 *
 * @ingroup themeable
 */
function theme_evol_evol_page_style_render_panel($display, $panel_id, $panes, $settings) {
  $output = '';

  // Determine where to put the box. If empty or 'pane' around each pane. If
  // 'panel' then just around the whole panel.
  $where = empty($settings['evol_page_location']) ? 'pane' : $settings['evol_page_location'];

  $print_separator = FALSE;
  foreach ($panes as $pane_id => $pane) {
    $text = panels_render_pane($pane, $display->content[$pane_id], $display);
    if ($text) {
      // Add the separator if we've already displayed a pane.
      if ($print_separator) {
        $output .= '<div class="panel-separator"></div>';
      }

      if ($where == 'pane') {
        $output .= theme('evol_evol_page_box', $text);
      }
      else {
        $output .= $text;
        $print_separator = TRUE;
      }
    }
  }

  if ($where == 'panel') {
    $output = theme('evol_evol_page_box', $output);
  }

  evol_add_evol_page_css();

  return $output;
}

/**
 * Render callback for a single pane.
 */
function theme_evol_evol_page_style_render_pane($content, $pane, $display) {
  $output = theme('panels_pane', $content, $pane, $display);

  if (!$output) {
    return;
  }

  // Just stick a box around the standard theme_panels_pane.
  $output = theme('evol_evol_page_box', $output);
  evol_add_evol_page_css();
  return $output;
}

function evol_add_evol_page_css() {
  static $css_loaded;
  if (!$css_loaded == TRUE) {
    $filename = drupal_get_path('theme', 'evol') . '/plugins/styles/evol_page/evol_page.css';
    drupal_add_css($filename, 'module', 'all', FALSE);
    $css_loaded = TRUE;
  }
}

/**
 * Settings form callback. 
 */
function evol_evol_page_style_settings_form($style_settings) {
  $form['evol_page_location'] = array(
    '#type' => 'select',
    '#title' => t('Box around'),
    '#options' => array(
      'pane' => t('Each pane'),
      'panel' => t('Each panel'),
    ),
    '#default_value' => (isset($style_settings['evol_page_location'])) ? $style_settings['evol_page_location'] : 'pane',
    '#description' => t('Choose whether to include the box around each pane (piece of content) or panel (each column or region)'),
  );

  return $form;
}
