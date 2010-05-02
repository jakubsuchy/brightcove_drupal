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
  // Issue a BC request to list videos
  // For all videos, get a thumbnail URL
  // Theme a table with videos and a button to attach.

  sleep(2);
  $output = 'ahoj';
  modalframe_child_js(); //dialog internal area
  return drupal_json($output);
}
