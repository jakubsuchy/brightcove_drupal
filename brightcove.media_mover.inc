<?php
// $Id$

/**
 * @file
 * Functions to implement Media Mover behavior for Brightcove.
 *
 * Origin: http://drupalcode.org/viewvc/drupal/contributions/modules/brightcove/includes/brightcove.media_mover.inc?revision=1.1.2.2&content-type=text%2Fplain&view=co&pathrev=DRUPAL-6--1
 * Parts created by Aaron Winborn - http://advomatic.com
 */

/**
 * Upload a video to Brightcove through Media Mover.
 */
function brightcove_mm_upload_video($file, $configuration) {
  $title = $configuration['brightcove_mm_default_title'];
  $description = $configuration['brightcove_mm_default_description'];
  $tags = '';
  $node = NULL;

  $length = isset($configuration['brightcove_mm_description_length']) ? $configuration['brightcove_mm_description_length'] : 300;

  if ($file['nid']) {
    $node = node_load($file['nid']);
    if ($node) {
      $title = $node->title;
      if ($body = truncate_utf8(strip_tags($node->body), $length, TRUE, TRUE)) {
        $description = $body;
      }
    }
    else {
      watchdog('brightcove', 'Unable to upload !file to Brightcove, as it belongs to node %nid which has been deleted.', array('!file' => l($file['filepath'], $file['filepath']), '%nid' => $file['nid']), WATCHDOG_ERROR);
    }
  }

  $filepath = media_mover_api_config_current_file($file);
  $fileinfo = pathinfo($filepath);

  // Create an array of required meta data.
  $meta = array(
      'name' => $title,
      'shortDescription' => $description,
      'referenceId' => brightcove_generate_reference(),
      );
  $video_id = brightcove_upload_video($filepath, $meta);

  watchdog('brightcove_mediamover', 'Successfully uploaded video to Brightcove: @video', array('@video' => $title, '!id' => $video_id), WATCHDOG_NOTICE);
  return $title . ' [id:' . $video_id . ']';
}

/**
 * Media Mover configuration form element for Brightcove.
 *
 * @see brightcove_validate_configuration().
 */
function brightcove_mm_config($configuration) {
  $form['brightcove_mm_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('Upload to Brightcove configuration'),
      '#element_validate' => array('brightcove_mm_validate_configuration', array('brightcove_mm_config'))
      );

  $form['brightcove_mm_config']['brightcove_mm_default_title'] = array(
      '#title' => t('Default title'),
      '#type' => 'textfield',
      '#default_value' => $configuration['brightcove_mm_default_title'] ? $configuration['brightcove_mm_default_title'] : '',
      '#description' => t('Videos which do not belong to a node will be given this title.'),
      );

  $form['brightcove_mm_config']['brightcove_mm_default_description'] = array(
      '#title' => t('Default description'),
      '#type' => 'textarea',
      '#default_value' => $configuration['brightcove_mm_default_description'] ? $configuration['brightcove_mm_default_description'] : 'Default description',
      '#description' => t('Videos which do not belong to a node will be given this description.'),
      );
  $form['brightcove_mm_config']['brightcove_mm_description_length'] = array(
      '#title' => t('Description length'),
      '#description' => t('If description is inherited from a node, how many characters from body to take?'),
      '#type' => 'textfield',
      '#size' => 10,
      '#default_value' => $configuration['brightcove_mm_description_length'] ? $configuration['brightcove_mm_description_length'] : 300,
      );

  return $form;
}

/**
 * Media Mover configuration form element for Brightcove.
 */
function brightcove_mm_complete_config($configuration) {
  $form['brightcove_mm_complete_config'] = array(
      '#type' => 'fieldset',
      '#title' => t('Attach Brightcove video to a CCK video field configuration'),
      '#element_validate' => array('brightcove_mm_complete_validate_configuration', array('brightcove_mm_complete_config'))
      );

  $fields = array();
  foreach (content_fields() as $field) {
    if ($field['type'] == 'brightcove_video') {
      $fields[$field['field_name']] = $field['widget']['label'] . " (" . $field['type_name'] . ')';
    }
  }
  $form['brightcove_mm_complete_config']['brightcove_mm_config_complete_field'] = array(
      '#type' => 'select',
      '#title' => t('Attach to these CCK fields'),
      '#description' => t('Select the CCK fields to attach uploaded videos to.'),
      '#options' => $fields,
      '#default_value' => $configuration['brightcove_mm_config_complete_field'],
      );

  return $form;
}

/**
  * Complete operation for Media Mover - will attach a video to CCK field.
  */
function brightcove_mm_complete_video($file, $configuration) {
  if (!$file['nid']) {
    watchdog('brightcove_mediamover', 'Did not find a node for attaching video to (complete phase)');
    return FALSE;
  }

  $node = node_load($file['nid']);
  $field = $configuration['brightcove_mm_config_complete_field'];

  if (!($video = $file['storage_file'])) {
    $video = $file['process_file'];
  }
  if (!empty($video) && isset($node->{$field})) {
    $id = brightcove_parse_id($video);
    $node->{$field}[0] = array('video_id' => brightcove_parse_id($video));
    node_save($node);
    watchdog('brightcove_mediamover', 'Attached a video %video to node %node (%nid)', array('%video' => $video, '%node' => $node->title, '%nid' => $node->nid), WATCHDOG_NOTICE);
  }
}

