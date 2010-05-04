<?php
// $Id$

/**
  * @file brightcove_cck.browse.inc
  *       Holds a method to list all BC videos that are attachable to a field.
  */

/**
  * This function is a callback for modalframe window, providing an access to browse videos.
  *
  * @see brightcove_cck_menu()
  *
  * @param none
  *
  * @return A list of available videos that can be attached to a field.
  *
  * TODO: Allow limiting videos by user (own videos only).
  * TODO: Interesting feature would be to detect multiple values allowed in the
  *       parent field and allow attaching all videos at once.
  */
function brightcove_cck_browse() {
  modalframe_child_js(); //dialog internal area
  drupal_add_css(drupal_get_path('module', 'brightcove_cck') . '/brightcove_cck.browse.css');
  // Issue a BC request to list videos
  // For all videos, get a thumbnail URL
  // Theme a table with videos and a button to attach.
  $bc = _brightcove_initialize();
  $matches = array();

  try {
    $result = $bc->find('find_all_videos');
  } catch (Exception $error) {
    watchdog('brightcove', 'Finding videos in autocomplete failed.', array(), WATCHDOG_ERROR);
  }
  foreach($result as $video) {
    $item = array();
    $item['title'] = check_plain($video->name);
    if (!empty($video->thumbnailURL)) {
      $item['thumbnail'] = $video->thumbnailURL;
    } else {
      $item['thumbnail'] = drupal_get_path('module', 'brightcove_cck') . '/images/thumbnail.jpg';
    }
    $items[] = $item;
  }
  return '<div class="brightcove-browse-table">' . theme('brightcove_cck_browse_items', $items) . '</div>';
}
