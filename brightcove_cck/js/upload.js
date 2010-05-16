/**
  * @file upload.js
  * Handles submitting upload form - making a throbber.
  */

Drupal.brightcove_cck = {};

Drupal.behaviors.brightcove_cck_upload = function(context) {
  $('#brightcove-cck-upload-form').submit(Drupal.brightcove_cck.upload);
 //  <div class="ahah-progress ahah-progress-throbber"><div class="throbber">&nbsp;</div></div>
};

Drupal.brightcove_cck.upload = function() {
  $('#brightcove-cck-upload-form #edit-submit').replaceWith('<div class="ahah-progress ahah-progress-throbber"><div class="throbber">&nbsp;</div><div>' + Drupal.t('The video is being created, please wait.') + '</div></div>');
};
