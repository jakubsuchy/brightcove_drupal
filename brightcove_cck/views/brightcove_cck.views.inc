<?php

/**
 * Implementation of hook_views_handlers().
 */
function brightcove_cck_views_handlers() {
  return array(
      'info' => array(
        'path' => drupal_get_path('module', 'brightcove_cck') .'/views',
        ),
      'handlers' => array(
        'brightcove_cck_handler_field_video_multiple' => array(
          'parent' => 'brightcove_cck_handler_field_video',
          ),
        'brightcove_cck_handler_field_video' => array(
          'parent' => 'content_handler_field_multiple',
          ),
        ),
      );
}
