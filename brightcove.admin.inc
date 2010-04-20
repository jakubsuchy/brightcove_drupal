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

  $form['brightcove_allow_public'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow public videos'),
    '#default_value' => variable_get('brightcove_allow_public', FALSE),
    '#description' => t('If public videos are allowed, users will be able to mark videos public. Public videos can be seen by anybody in the video browser.'),
  );

  return system_settings_form($form);
}
