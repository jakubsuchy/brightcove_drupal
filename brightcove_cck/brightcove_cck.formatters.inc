<?php

/**
  * @file
  * Formatters for video CCK field.
  */

/**
  * Theme callback for Lightbox2 with imagecache player.
  * @param $element
  *  Element with the Video ID.
  * @return
  *  Player HTML code.
  */
function theme_brightcove_cck_lightbox2_imagecache($element) {
  $preset = str_replace('lightbox2_imagecache_', '', $element['#formatter']);
  if (isset($element['#item']['video_id'])) {  

    $video = brightcove_video_load($element['#item']['video_id']);
    if (!isset($video->id) && variable_get('brightcove_check_for_unavailable', TRUE) && ($unavailable_message = variable_get('brightcove_status_display_unavailable', 'This video is unavailable for the moment.'))) {
      return theme('brightcove_unavailable_message', filter_xss($unavailable_message));
    } else if (!isset($video->id)) {
      return FALSE;
    }
    if (!empty($video->thumbnailURL)) {
      $image = theme('imagecache', $preset, brightcove_remote_image($video->thumbnailURL));
      return theme('brightcove_cck_formatter_lightbox2_player', $element, $image);
    }
  }
}

/**
  * Theme callback for Default thumbnail -> Lightbox2 player formatter.
  *
  * @param $element
  *  Element with the Video ID.
  * @return
  *  Player HTML code.
  */
function theme_brightcove_cck_lightbox2_player($element, $image = NULL) {
  if (!empty($element['#item']['video_id'])) {
    $video = brightcove_video_load($element['#item']['video_id']);
    if (!isset($video->id)) {
      if (!isset($video->id) && variable_get('brightcove_check_for_unavailable', TRUE) && ($unavailable_message = variable_get('brightcove_status_display_unavailable', 'This video is unavailable for the moment.'))) {
        return theme('brightcove_unavailable_message', filter_xss($unavailable_message));
      } else if (!isset($video->id)) {
        return FALSE;
      }
    }

    if (!$image) {
      if (!empty($video->thumbnailURL)) {
        $image = theme('image', $video->thumbnailURL, '', '', NULL, FALSE);
      } else {
        $image = t('Play video');
      }
    }
    $destination = 'brightcove_cck_player/' . $element['#node']->nid . '/' . $element['#field_name'] . '/' . $element['#item']['#delta'];

    $bc = _brightcove_initialize();
    // Ugly hack to support width and height of a video - get a BC player and check it's dimensions.
    $player = $bc->embed('video', variable_get('brightcove_player', ''),  $element['#item']['video_id'], $params);
    //<param name="width" value="486" />
    preg_match('/<param name="width" value="(\d{1,5})" \/>/', $player, $width);
    preg_match('/<param name="height" value="(\d{1,5})" \/>/', $player, $height);

    $width = $width[1] + 30;
    $height = $height[1] + 30;
    $rel_full = 'lightframe[|width: ' . $width . 'px; height: ' . $height . 'px; overflow: visible;]'; // lightbox[' . check_plain($element['#field_name']) . ']';

    $output = l($image, $destination, array('attributes' => array('rel' => $rel_full, 'class' => $element['#field_name'], 'title' => check_plain($video->name)), 'html' => TRUE));

    return $output;
  } else {
    return FALSE;
  }

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
    dpm($player);
    return $player;
  } else {
    return FALSE;
  }
}

