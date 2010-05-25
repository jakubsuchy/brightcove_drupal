<?php
// $Id$

/**
 * @file
 * Admin settings for Brightcove module.
 */

/**
 * Form builder.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function brightcove_admin_settings() {

  $form['brightcove_read_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Brightcove Read API key'),
    '#maxlength' => 255,
    '#required' => TRUE,
    '#default_value' => variable_get('brightcove_read_api_key', ''),
    '#description' => t('A Brightcove Read API key according to your account at Brightcove Studio. Please check at <a href="http://my.brightcove.com">Brightcove studio</a> page.'),
  );
  $form['brightcove_write_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Brightcove Write API key'),
    '#maxlength' => 255,
    '#default_value' => variable_get('brightcove_write_api_key', ''),
    '#description' => t('A Brightcove Write API key according to your account at Brightcove Studio. Please check at <a href="http://my.brightcove.com">Brightcove studio</a> page. <strong>Requires at least a Professional account</strong>.'),
  );

  $form['brightcove_player'] = array(
    '#type' => 'textfield',
    '#title' => t('Brightcove Player ID'),
    '#required' => TRUE,
    '#default_value' => variable_get('brightcove_player', ''),
    '#description' => t('A Brightcove Player ID from BC Studio. Will be used to play all videos.'),
  );

/*  $form['brightcove_allow_public'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow public videos'),
    '#default_value' => variable_get('brightcove_allow_public', FALSE),
    '#description' => t('If public videos are allowed, users will be able to mark videos public. Public videos can be seen by anybody in the video browser.'),
    );*/
  $form['brightcove_default_image'] = array(
    '#type' => 'textfield',
    '#title' => t('Default image'),
    '#description' => t("In case a video doesn't have a thumbnail or still image, display an image from this path"),
    '#default_value' => variable_get('brightcove_default_thumbnail', brightcove_get_default_image()),
  );
  $form['status'] = array(
      '#type' => 'fieldset',
      '#title' => t('Status settings'),
      '#description' => t("Settings relating to the availability status of a video."),
      '#collapsible' => TRUE,
      );
  $form['status']['brightcove_check_for_unavailable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Check for unavailable videos'),
      '#description' => t("If checked, then the message below will be displayed if a recently uploaded video is not yet available."),
      '#default_value' => variable_get('brightcove_check_for_unavailable', TRUE),
      );
  $form['status']['brightcove_status_display_unavailable'] = array(
      '#type' => 'textarea',
      '#title' => t('Unavailable video message'),
      '#description' => t("If the checkbox above is checked, and you have a message below (which may contain HTML), it will be displayed if a video is not yet available for viewing."),
      '#default_value' => variable_get('brightcove_status_display_unavailable', 'This video is unavailable for the moment.'),
      );


  return system_settings_form($form);
}
