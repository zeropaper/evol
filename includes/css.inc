<?php


function evol_css_add($code, $selector, $return_only = FALSE) {
  static $pieces = array();
  $code_key = $code;//strtolower(preg_replace('/[^a-zA-Z0-9-:;]+/', '-', $code));
  $pieces[$code_key][$selector] = TRUE;
  
  $selectors = implode(",\n", array_keys($pieces[$code_key]));
  
  if (!$return_only) {
    theme('add_css_code', $code_key, "$selectors {\n  $code\n}");
  }
  return $css;
}