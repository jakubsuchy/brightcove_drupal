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
  $preset_data = str_replace('lightbox2_imagecache_', '', $element['#formatter']);
  list($preset, $field) = split('__', $preset_data);

  if (isset($element['#item']['video_id'])) {  

    $video = brightcove_video_load($element['#item']['video_id']);
    $status = brightcove_status($element['#item']['video_id']);
    if ($status != BRIGHTCOVE_STATUS_COMPLETE && ($message = brightcove_expose_unavailable($status))) {
      return $message;
    } else if ($status != BRIGHTCOVE_STATUS_COMPLETE) {
      return FALSE;
    }

    if (!empty($video->thumbnailURL)) {
      $image = theme('imagecache', $preset, brightcove_remote_image($video->{$field}));
    } else {
      $image = theme('imagecache', $preset, brightcove_get_default_image());
    }
    return theme('brightcove_cck_formatter_lightbox2_player_' . $field, $element, $image, $preset);
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
function theme_brightcove_cck_lightbox2_player($element, $image = NULL, $preset = NULL) {
  if (!empty($element['#item']['video_id'])) {


    $field = str_replace('lightbox2_player_', '', $element['#formatter']);

    $video = brightcove_video_load($element['#item']['video_id']);
    $status = brightcove_status($element['#item']['video_id']);
    if ($status != BRIGHTCOVE_STATUS_COMPLETE && ($message = brightcove_expose_unavailable($status))) {
      return $message;
    } else if ($status != BRIGHTCOVE_STATUS_COMPLETE) {
      return FALSE;
    }

    $video_name = check_plain($video->name);

    if (!$image) {
      if (!empty($video->{$field})) {
        $image = theme('image', $video->{$field}, '', '', NULL, FALSE);
      } else {
        $image = theme('image', brightcove_get_default_image(), $video_name, $video_name, array('width' => 120, 'height' => 120), FALSE);
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

    $video_width = $width - 30;
    $video_height = $height - 30;
    $lightbox2_width = $width;
    $lightbox2_height = $height;
    $video_id = $element['#item']['video_id'];

  }
  if ($output) {
    return theme('brightcove_cck_lightbox2', $output, $video_id, $video_width, $video_height, $lightbox2_width, $lightbox2_height, $destination, $field, $element['#field_name'], $element['#type_name'], $preset);
  }

}

/**
  * Template preprocess for brightcove_cck_lightbox2 theme file.
  * Suggest templates based on a field and type name.
  */
function template_preprocess_brightcove_cck_lightbox2(&$vars) {
  $vars['template_files'] = array(
      'brightcove-cck-lightbox2--' . $vars['image_field'],
      'brightcove-cck-lightbox2--' . $vars['field_name'] . '--' . $vars['image_field'],
      'brightcove-cck-lightbox2--' . $vars['type_name'] . '--' . $vars['field_name'] . '--' . $vars['image_field'],
      );
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
  }
  if ($player) {
    return theme('brightcove_cck_player', $player, $element['#item']['video_id']);
  }
}


/**
  * Theme callback for Default thumbnail linked to node formatter.
  *
  * @param $element
  *  Element with the Video ID.
  * @return
  *  Link HTML code.
  */
function theme_brightcove_cck_node_link($element, $image = NULL) {
  if (!empty($element['#item']['video_id'])) {

    $field = str_replace('node_link_', '', $element['#formatter']);

    $video = brightcove_video_load($element['#item']['video_id']);
    $status = brightcove_status($element['#item']['video_id']);
    if ($status != BRIGHTCOVE_STATUS_COMPLETE && ($message = brightcove_expose_unavailable($status))) {
      return $message;
    } else if ($status != BRIGHTCOVE_STATUS_COMPLETE) {
      return FALSE;
    }

    if (!$image) {
      if (!empty($video->{$field})) {
        $image = theme('image', $video->{$field}, '', '', NULL, FALSE);
      } else {
        $image = theme('image', brightcove_get_default_image(), $video_name, $video_name, array('width' => 120, 'height' => 120), FALSE);
      }
    }

    $destination = 'node/' . $element['#node']->nid;

    $output = l($image, $destination, array('attributes' => array('class' => $element['#field_name'], 'title' => check_plain($element['#node']->name)), 'html' => TRUE));

    $video_id = $element['#item']['video_id'];

  }
  if ($output) {
    return theme('brightcove_cck_node_link', $output, $video_id, url($destination), $field, $element['#field_name'], $element['#type_name'], $preset);
  }

}

/**
  * Template preprocess for brightcove_cck_node_link theme file.
  * Suggest templates based on a field and type name.
  */
function template_preprocess_brightcove_cck_node_link(&$vars) {
  $vars['template_files'] = array(
      'brightcove-cck-node-link--' . $vars['image_field'],
      'brightcove-cck-node-link--' . $vars['field_name'] . '--' . $vars['image_field'],
      'brightcove-cck-node-link--' . $vars['type_name'] . '--' . $vars['field_name'] . '--' . $vars['image_field'],
      );
}

/**
  * Theme callback for imagecache image linking to node
  * 
  * @param $element
  *  Element with the Video ID.
  * @return
  *  Link HTML code.
  */
function theme_brightcove_cck_node_link_imagecache($element) {
  $preset_data = str_replace('node_link_imagecache_', '', $element['#formatter']);
  list($preset, $field) = split('__', $preset_data);

  if (isset($element['#item']['video_id'])) {  

    $video = brightcove_video_load($element['#item']['video_id']);
    $status = brightcove_status($element['#item']['video_id']);
    if ($status != BRIGHTCOVE_STATUS_COMPLETE && ($message = brightcove_expose_unavailable($status))) {
      return $message;
    } else if ($status != BRIGHTCOVE_STATUS_COMPLETE) {
      return FALSE;
    }

    if (!empty($video->{$field})) {
      $image = theme('imagecache', $preset, brightcove_remote_image($video->{$field}));
    } else {
      $image = theme('imagecache', $preset, brightcove_get_default_image());
    }
    return theme('brightcove_cck_formatter_node_link_' . $field, $element, $image, $preset);
  }
}

/**
  * Theme callback for Default thumbnail.
  *
  * @param $element
  *  Element with the Video ID.
  * @return
  *  Link HTML code.
  */
function theme_brightcove_cck_node_image($element, $image = NULL) {
  if (!empty($element['#item']['video_id'])) {

    $field = str_replace('node_image_', '', $element['#formatter']);

    $video = brightcove_video_load($element['#item']['video_id']);
    $status = brightcove_status($element['#item']['video_id']);
    if ($status != BRIGHTCOVE_STATUS_COMPLETE && ($message = brightcove_expose_unavailable($status))) {
      return $message;
    } else if ($status != BRIGHTCOVE_STATUS_COMPLETE) {
      return FALSE;
    }

    if (!$image) {
      if (!empty($video->{$field})) {
        $image = theme('image', $video->{$field}, '', '', NULL, FALSE);
      } else {
        $image = theme('image', brightcove_get_default_image(), $video_name, $video_name, array('width' => 120, 'height' => 120), FALSE);
      }
    }

    $output = $image;

    $video_id = $element['#item']['video_id'];
    $nid = $element['#node']->nid;

  }
  if ($output) {
    return theme('brightcove_cck_node_image', $output, $video_id, $nid, $field, $element['#field_name'], $element['#type_name']);
  }

}

/**
  * Template preprocess for brightcove_cck_node_image theme file.
  * Suggest templates based on a field and type name.
  */
function template_preprocess_brightcove_cck_node_image(&$vars) {
  $vars['template_files'] = array(
      'brightcove-cck-node-image--' . $vars['image_field'],
      'brightcove-cck-node-image--' . $vars['field_name'] . '--' . $vars['image_field'],
      'brightcove-cck-node-image--' . $vars['type_name'] . '--' . $vars['field_name'] . '--' . $vars['image_field'],
      );
}

/**
  * Theme callback for imagecache image
  * 
  * @param $element
  *  Element with the Video ID.
  * @return
  *  Link HTML code.
  */
function theme_brightcove_cck_node_image_imagecache($element) {
  $preset_data = str_replace('node_image_imagecache_', '', $element['#formatter']);
  list($preset, $field) = split('__', $preset_data);

  if (isset($element['#item']['video_id'])) {  

    $video = brightcove_video_load($element['#item']['video_id']);
    $status = brightcove_status($element['#item']['video_id']);
    if ($status != BRIGHTCOVE_STATUS_COMPLETE && ($message = brightcove_expose_unavailable($status))) {
      return $message;
    } else if ($status != BRIGHTCOVE_STATUS_COMPLETE) {
      return FALSE;
    }

    if (!empty($video->{$field})) {
      $image = theme('imagecache', $preset, brightcove_remote_image($video->{$field}));
    } else {
      $image = theme('imagecache', $preset, brightcove_get_default_image());
    }
    return theme('brightcove_cck_formatter_node_image_' . $field, $element, $image);
  }
}


