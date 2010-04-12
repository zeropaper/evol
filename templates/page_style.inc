<?php

function evol_preprocess_page_style(&$vars) {
  $page_style = theme_get_setting('page_style');
  $vars = array_merge($vars, $page_style);
  
  $vars['page_style'] = $page_style;
}