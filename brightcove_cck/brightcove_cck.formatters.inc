<?php

/**
  * Theme callback for Default thumbnail -> Lightbox2 player formatter.
  */
function theme_brightcove_cck_lightbox2_player($element) {
  if (isset($element['#item']['video_id'])) {

    $video = brightcove_video_load($element['#item']['video_id']);

    if (!empty($video->thumbnailURL)) {
      $image = theme('image', $video->thumbnailURL, '', '', NULL, FALSE);
    } else {
      $image = t('Play video');
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
