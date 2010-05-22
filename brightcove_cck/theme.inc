<?php

/**
  * Theme callback for a Brightcove browse button.
  * Currently it's just a thin wrapper around the theme_button()
  * function which only returns a button of type submit. The themed
  * representation is just adapted to achieve an input html tag
  * of the type button.
  *
  * @see nodereference_explorer.module
  */
function theme_brightcove_cck_browse_button($element) {
  drupal_add_js(drupal_get_path('module', 'brightcove_cck') . '/js/browse.js');
  $button = theme('button', $element);
  return str_ireplace('type="submit"', 'type="button"', $button);
}

/**
  * Theme callback for Brightcove browse table item.
  *
  * @param item
  * Video item.
  *
  * @return
  * Themed item form.
  */
function theme_brightcove_cck_browse_item($item) {
  return drupal_get_form('brightcove_cck_browser_form' . $item['video_id'], $item);
}

/**
  * Theme callback for Brightcove browse table.
  *
  * @param $items
  * Array of video items.
  *
  * @return
  * Themed browse table.
  */
function theme_brightcove_cck_browse_items($items) {
  $rowcount = 0;
  $activerow = 0;
  $rows = array();
  foreach($items as $item) {
    $themed = theme('brightcove_cck_browse_item', $item);
    $rowcount++;
    if ($rowcount == 4) {
      $activerow++;
      $rowcount = 1;
    }
    $rows[$activerow][] = $themed;
  }
  return theme('table', array(), $rows);
}


