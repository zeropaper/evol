<?php

function evol_form_element($element, $value) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();
  
  $output = '<div class="form-item form-item-'. str_replace('_', '-', $element['#type']) .'"';
  if (!empty($element['#id'])) {
    $output .= ' id="'. $element['#id'] .'-wrapper"';
  }
  $output .= ">\n";
  $required = !empty($element['#required']) ? '<span class="form-required" title="'. $t('This field is required.') .'">*</span>' : '';

  if (!empty($element['#title'])) {
    $title = $element['#title'];
    if (!empty($element['#id'])) {
      $output .= ' <label for="'. $element['#id'] .'">'. $t('!title: !required', array('!title' => filter_xss_admin($title), '!required' => $required)) ."</label>\n";
    }
    else {
      $output .= ' <label>'. $t('!title: !required', array('!title' => filter_xss_admin($title), '!required' => $required)) ."</label>\n";
    }
  }

  $output .= " $value\n";

  if (!empty($element['#description'])) {
    $output .= ' <div class="description">'. $element['#description'] ."</div>\n";
  }

  $output .= "</div>\n";

  return $output;
}

function evol_pony() {
  return 'pony';
}

//function evol_pony_should_not_be_found() {
//  return 'pony';
//}


/**
 * Overrides theme_fieldset().
 */
function evol_fieldset(&$element) {
  evol_add_js('fieldset');
  $attr = isset($element['#attributes']) ? $element['#attributes'] : array();
  $attr['class'] = !empty($attr['class']) ? $attr['class'] : '';
  $attr['class'] .= ' fieldset';
  $attr['class'] .= !empty($element['#collapsible']) || !empty($element['#collapsed']) ? ' collapsible' : '';
  $attr['class'] .= !empty($element['#collapsed']) ? ' collapsed' : '';
  $attr = drupal_attributes($attr);

  $description = !empty($element['#description']) ? "<div class='description'>{$element['#description']}</div>" : '';
  $children = !empty($element['#children']) ? $element['#children'] : '';
  $value = !empty($element['#value']) ? $element['#value'] : '';
  $content = $description . $children . $value;

  $title = !empty($element['#title']) ? $element['#title'] : '';
  if (!empty($element['#collapsible']) || !empty($element['#collapsed'])) {
    $title = l($title, $_GET['q'], array('fragment' => 'fieldset'));
  }

  $output = "<div $attr>";
  $output .= $title ? "<h2 class='fieldset-title'>$title</h2>" : '';
  $output .= "<div class='fieldset-content clear-block'>$content</div>";
  $output .= "</div>";
  return $output;
}