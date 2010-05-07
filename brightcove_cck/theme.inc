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
    $bc = _brightcove_initialize();
    try {
      $video = $bc->find('find_video_by_id', $element['#item']['video_id']);
    } catch (Exception $error) {
      watchdog('brightcove', 'Loading Brightcove video failed.', array(), WATCHDOG_ERROR);
      return FALSE;
    }
    if (!empty($video->thumbnailURL)) {
      $image = theme('image', $video->thumbnailURL, '', '', NULL, FALSE);
    } else {
      $image = t('Play video');
    }
    $destination = 'brightcove_cck_player/' . $element['#node']->nid . '/' . $element['#field_name'] . '/' . $element['#item']['#delta'];


    // Ugly hack to support width and height of a video - get a BC player and check it's dimensions.
    $player = $bc->embed('video', variable_get('brightcove_player', ''),  $element['#item']['video_id'], $params);
    //<param name="width" value="486" />
    preg_match('/<param name="width" value="(\d{1,5})" \/>/', $player, $width);
    preg_match('/<param name="height" value="(\d{1,5})" \/>/', $player, $height);

    $width = $width[1] + 30;
    $height = $height[1] + 30;
    $rel_full = 'lightframe[|width: ' . $width . 'px; height: ' . $height . 'px; overflow: visible;] lightbox[' . check_plain($element['#field_name']) . ']';

    $output = l($image, $destination, array('attributes' => array('rel' => $rel_full, 'class' => $element['#field_name'], 'title' => check_plain($video->name)), 'html' => TRUE));

    return $output;
  } else {
    return FALSE;
  }

}
