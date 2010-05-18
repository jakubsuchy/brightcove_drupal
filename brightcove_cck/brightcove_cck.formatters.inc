<?php
// $Id$

/**
  * @file
  * Formatters for video CCK field.
  */

/**
  * Template preprocess to prepare video ImageCache -> Lightbox2 display.
  *
  * @param $vars
  *  Variables with $vars['element'] containing the video data.
  */
function template_preprocess_brightcove_cck_lightbox2_imagecache(&$vars) {
  $element = $vars['element'];

  $preset_data = str_replace('lightbox2_imagecache_', '', $element['#formatter']);

  list($preset, $field) = split('__', $preset_data);

  if (isset($element['#item']['video_id'])) {  
    $video = brightcove_video_load($element['#item']['video_id']);

    if (!empty($video->{$field})) {
      $image = theme('imagecache', $preset, brightcove_remote_image($video->{$field}));
      $vars['output'] = theme('brightcove_cck_formatter_lightbox2_player_videoStillURL', $element, $image);
    }
  }
}

/**
  * Template preprocess to prepare video default display.
  *
  * @param $vars
  *  Variables with $vars[0] containing the video data.
  */
function template_preprocess_brightcove_cck_formatter_default(&$vars) {
  if (isset($vars[0]['#item']['video_id'])) {
    $bc = _brightcove_initialize();
    // We need to write a BC JavaScript to the page, which is not possible
    // with a simple drupal_add_js(), inline is needed.
    $script = 'document.write(unescape("%3Cscript src=\'http://admin.brightcove.com/js/BrightcoveExperiences.js\' type=\'text/javascript\'%3E%3C/script%3E"));';
    drupal_add_js($script, 'inline', 'header');
    $vars['player'] = $bc->embed('video', variable_get('brightcove_player', ''), $vars[0]['#item']['video_id'], $params);
    $vars['video_id'] = $vars[0]['#item']['video_id'];
  }
}



/**
  * Template preprocess to prepare video lightbox2 display.
  *
  * @param $vars
  *  Variables with $vars[0] containing the video data.
  */

function template_preprocess_brightcove_cck_formatter_lightbox2_player(&$vars) {
  $element = $vars['element'];
  $image = $vars['image'];
  
  // Preset name is also a field name in Media API.
  $preset = str_replace('lightbox2_player_', '', $element['#formatter']);

  if (!empty($element['#item']['video_id'])) {
    $video = brightcove_video_load($element['#item']['video_id']);
    if (!isset($video->id)) {
      if (!isset($video->id) && variable_get('brightcove_check_for_unavailable', TRUE) && ($unavailable_message = variable_get('brightcove_status_display_unavailable', 'This video is unavailable for the moment.'))) {
        $vars['output'] = theme('brightcove_unavailable_message', filter_xss($unavailable_message));
        return;
      } else if (!isset($video->id)) {
        $vars['output'] = '';
        return;
      }
    }

    if (!$image) {
      if (!empty($video->{$preset})) {
        $image = theme('image', $video->{$preset}, '', '', NULL, FALSE);
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

    $vars['video_width'] = $width[1];
    $vars['video_height'] = $height[1];
    
    $width = $width[1] + 30;
    $height = $height[1] + 30;
    $rel_full = 'lightframe[|width: ' . $width . 'px; height: ' . $height . 'px; overflow: visible;]'; // lightbox[' . check_plain($element['#field_name']) . ']';

    $vars['lightbox2_width'] = $width;
    $vars['lightbox2_height'] = $height;

    $vars['image_field'] = $preset;
    $vars['video_id'] = $element['#item']['video_id'];

    $vars['destination'] = url($destination);

    $vars['output'] = l($image, $destination, array('attributes' => array('rel' => $rel_full, 'class' => $element['#field_name'], 'title' => check_plain($video->name)), 'html' => TRUE));
  }
}
