/**
  * @file browse.js
  * Creates actions - browse and remove for Video form fields.
  */

Drupal.brightcove_cck = {};
Drupal.brightcove_cck.actions = {};

Drupal.behaviors.brightcove_cck_buttons = function(context) {
  $('.brightcove-cck-browse-button', context).click(Drupal.brightcove_cck.actions.browse);
  $('.brightcove-cck-upload-button', context).click(Drupal.brightcove_cck.actions.upload);
  $('.brightcove-cck-remove-button', context).click(Drupal.brightcove_cck.actions.remove);
  $('.form-text.brightcove-video-field').change(Drupal.brightcove_cck.actions.change);
};

Drupal.brightcove_cck.actions.change = function() {
  $('.brightcove-cck-remove-button[rel="' + $(this).attr('id') + '"]').attr('disabled', '');
}
Drupal.brightcove_cck.actions.remove = function() {
  $('#' + $(this).attr('rel')).val('');
}

Drupal.brightcove_cck.actions.browse = function() {
  var id = $(this).attr('rel');
  var field_name = $('#' + id).attr('rel');
  Drupal.modalFrame.open({onSubmit: Drupal.brightcove_cck.submit(id), url: Drupal.settings.basePath + 'brightcove_cck/browse/' + Drupal.settings.brightcove_cck[field_name].node_type + '/' + Drupal.settings.brightcove_cck[field_name].field_name + '/' + Drupal.settings.brightcove_cck[field_name].nid, width: 950, height: 600, autoFit: false});
  return false;
}

Drupal.brightcove_cck.actions.upload = function() {
  var id = $(this).attr('rel');
  var field_name = $('#' + id).attr('rel');
  Drupal.modalFrame.open({onSubmit: Drupal.brightcove_cck.submit(id), url: Drupal.settings.basePath + 'brightcove_cck/upload/' + Drupal.settings.brightcove_cck[field_name].node_type + '/' + Drupal.settings.brightcove_cck[field_name].field_name + '/' + Drupal.settings.brightcove_cck[field_name].nid, width: 950, height: 600, autoFit: false});
  return false;
}

Drupal.brightcove_cck.submit = function(settings) {
  return function(args) {
    $("#" + settings).val(args.selected)
    $('.brightcove-cck-remove-button[rel="' + settings + '"]').attr('disabled', '');
  };
}
