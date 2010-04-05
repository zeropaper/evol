<?php

function evol_preprocess_node(&$vars) {
  $node = &$vars['node'];
  $classes = array('node');
  if ($node->sticky) {
    $classes[] = 'sticky';
  }
  if ($vars['teaser']) {
    $classes[] = 'node-teaser';
  }
  if (!$node->status) {
    $classes[] = 'node-unpublished';
  }
  
  if (isset($node->taxonomy) && is_array($node->taxonomy)) {
    foreach ($node->taxonomy as $tid => $term) {
      $classes[] = 'term-'. $tid;
    }
  }
  
  $vars['classes'] = implode(' ', drupal_map_assoc($classes));
  
  
}