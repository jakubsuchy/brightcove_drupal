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
        'brightcove_cck_handler_field_video_date_multiple' => array(
          'parent' => 'brightcove_cck_handler_field_video_date',
          ),
        'brightcove_cck_handler_field_video_date' => array(
          'parent' => 'content_handler_field_multiple',
          ),
        'brightcove_cck_handler_field_video_tags_multiple' => array(
          'parent' => 'brightcove_cck_handler_field_video_tags',
          ),
        'brightcove_cck_handler_field_video_tags' => array(
          'parent' => 'content_handler_field_multiple',
          ),

        ),
      );
}

/**
  * This is NOT implementation of hook_views_data().
  * This is a helper function for hook_field_settings op = 'views data'.
  */
function _brightcove_cck_views_data($field) {
  $data = content_views_field_views_data($field);
  $db_info = content_database_info($field);
  $table_alias = content_views_tablename($field);

  $types = content_types();

  $text_fields = array(
      'name' => 'Name',
      'shortDescription' => 'Short description',
      'longDescription' => 'Long description',
      'playsTotal' => 'Plays total',
      'playsTrailingWeek' => 'Plays trailing week',
      );
  foreach ($text_fields as $bc_field => $text) {
    $data[$table_alias][$field['field_name'] .'_video_id_' . $bc_field]['title'] = t('Video: name');
    $data[$table_alias][$field['field_name'] .'_video_id_' . $bc_field]['field'] = array(
      'handler' => 'brightcove_cck_handler_field_video_multiple',
      'additional fields' => array($field['field_name'] . '_video_id' => $field['field_name'] . '_video_id'),
      'real field' => $field['field_name'] . '_video_id',
      'content_field_name' => $field['field_name'],
      'title' => t('Video: @name', array('@name' => $text)),
      'title short' => t('Video: @name', array('@name' => $text)),
      'click sortable' => FALSE,
      'help' => t('Video: @name - Appears in: @types', array('@types' => check_plain($types[$field['type_name']]['name']), '@name' => $text)),
      'access callback' => 'content_access',
      'access arguments' => array('view', $field),
    );
  }

  $date_fields = array(
      'creationDate' => 'Date Created',
      'publishedDate' => 'Date Published',
      'lastModifiedDate' => 'Last modified date',
      );
  foreach ($date_fields as $bc_field => $text) {
    $data[$table_alias][$field['field_name'] .'_video_id_' . $bc_field]['title'] = t('Video: name');
    $data[$table_alias][$field['field_name'] .'_video_id_' . $bc_field]['field'] = array(
      'handler' => 'brightcove_cck_handler_field_video_date_multiple',
      'additional fields' => array($field['field_name'] . '_video_id' => $field['field_name'] . '_video_id'),
      'real field' => $field['field_name'] . '_video_id',
      'content_field_name' => $field['field_name'],
      'title' => t('Video: @name', array('@name' => $text)),
      'title short' => t('Video: @name', array('@name' => $text)),
      'click sortable' => FALSE,
      'help' => t('Video: @name - Appears in: @types', array('@types' => check_plain($types[$field['type_name']]['name']), '@name' => $text)),
      'access callback' => 'content_access',
      'access arguments' => array('view', $field),
    );
  }

  $tag_fields = array(
      'tags' => 'Tags',
      );
  foreach ($tag_fields as $bc_field => $text) {
    $data[$table_alias][$field['field_name'] .'_video_id_' . $bc_field]['title'] = t('Video: name');
    $data[$table_alias][$field['field_name'] .'_video_id_' . $bc_field]['field'] = array(
      'handler' => 'brightcove_cck_handler_field_video_tags_multiple',
      'additional fields' => array($field['field_name'] . '_video_id' => $field['field_name'] . '_video_id'),
      'real field' => $field['field_name'] . '_video_id',
      'content_field_name' => $field['field_name'],
      'title' => t('Video: @name', array('@name' => $text)),
      'title short' => t('Video: @name', array('@name' => $text)),
      'click sortable' => FALSE,
      'help' => t('Video: @name - Appears in: @types', array('@types' => check_plain($types[$field['type_name']]['name']), '@name' => $text)),
      'access callback' => 'content_access',
      'access arguments' => array('view', $field),
    );
  }

  return $data;

}
