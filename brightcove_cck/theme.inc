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
  * Theme callback for Brightcove CCK formatter.
  * Returns an embedded player with default site player.
  *
  * @param $element
  *  Element with the Video ID.
  * @return
  *  Player HTML code.
  */
function theme_brightcove_cck_formatter_default($element) {
  if (isset($element['#item']['video_id'])) {
    $bc = _brightcove_initialize();
    // We need to write a BC JavaScript to the page, which is not possible
    // with a simple drupal_add_js(), inline is needed.
    $script = 'document.write(unescape("%3Cscript src=\'http://admin.brightcove.com/js/BrightcoveExperiences.js\' type=\'text/javascript\'%3E%3C/script%3E"));';
    drupal_add_js($script, 'inline', 'header');
    $player = $bc->embed('video', variable_get('brightcove_player', ''),  $element['#item']['video_id'], $params);
    return $player;
  } else {
    return FALSE;
  }
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
    }
    $rows[$activerow][] = $themed;
  }
  return theme('table', array(), $rows);
}
function theme_brightcove_cck_lightbox2_player($element) {
  if (isset($element['#item']['video_id'])) {
  dpm($element);
  dpm($element['#item']);
  dpm("B");
  }
}
