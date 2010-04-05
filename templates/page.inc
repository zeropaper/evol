<?php

/**
 * Preprocessor for page.tpl.php template file.
 */
function evol_preprocess_page(&$vars, $hook) {
//  evol_add_css('messages');
  // For easy printing of variables.
  $vars['logo_img']             = $vars['logo'] ? theme('image', substr($vars['logo'], strlen(base_path())), t('Home'), t('Home')) : '';
  $vars['linked_logo_img']      = $vars['logo_img'] ? l($vars['logo_img'], '<front>', array('attributes' => array('rel' => 'home'), 'title' => t('Home'), 'html' => TRUE)) : '';
  $vars['linked_site_name']     = $vars['site_name'] ? l($vars['site_name'], '<front>', array('attributes' => array('rel' => 'home'), 'title' => t('Home'))) : '';
  $vars['main_menu_links']      = theme('links', $vars['primary_links'], array('class' => 'links main-menu'));
  $vars['secondary_menu_links'] = theme('links', $vars['secondary_links'], array('class' => 'links secondary-menu'));
  
  // uncomment if you do understand what will happen
  // or set the ztools_use_reset_css variable to TRUE if zTools is installed
  #drupal_set_html_head('<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . drupal_get_path('theme', 'evol') .'/styles/reset.css" />');
  #$vars['head']                 = drupal_get_html_head();
  
  evol_body_classes($vars['body_classes'], $vars);
  
  $vars['messages']             .= $vars['show_messages'] ? theme('status_messages') : '';
}

function evol_body_classes(&$body_classes, $vars) {
  $classes = explode(' ', $body_classes);
  
  if (theme_get_setting('show_grid')) {
    $classes[] = 'show-grid';
  }
  
  // helps avoiding IE fixes and such
  if (function_exists('browscap_get_browser')) {
    $browser = browscap_get_browser();
    $classes[] = 'browser-'. strtolower($browser['browser']);
  }
  
  $body_classes = implode(' ', array_unique($classes));
}


function evol_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    foreach ($breadcrumb as $l => $link) {
      $first_last  = '';
      if ($l == 0) {
        $first_last .= ' first';
      }
      if ($l == count($breadcrumb)-1) {
        $first_last .= ' last';
      }
      $breadcrumb[$l] = '<span class="breadcrumb-'. $l . $first_last .'">'. $link .'</span>';
    }
    return '<div class="breadcrumb">'. implode(' <span class="separator">»</span> ', $breadcrumb) .'</div>';
  }
}