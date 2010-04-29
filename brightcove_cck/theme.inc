<?php

function theme_brightcove_cck_browse_button($element) {

  drupal_add_js(drupal_get_path('module', 'brightcove_cck') . '/js/browse.js');
  //Currently it's just a thin wrapper around the theme_button()
  //function which only returns a button of type submit. The themed
  //representation is just adapted to achieve an input html tag
  //of the type button.
  $button = theme('button', $element);
  return str_ireplace('type="submit"', 'type="button"', $button);
}

