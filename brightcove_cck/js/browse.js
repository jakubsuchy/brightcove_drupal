/**
  * @file browse.js
  * Creates actions - browse and remove for Video form fields.
  */

Drupal.brightcove_cck = {};
Drupal.brightcove_cck.actions = {};

Drupal.behaviors.brightcove_cck_buttons = function(context) {
  $('.brightcove-cck-browse-button', context).click(Drupal.brightcove_cck.actions.browse);
  $('.brightcove-cck-remove-button', context).click(Drupal.brightcove_cck.actions.remove);
  // TODO: There should be a better selector for this - how do we add a class to cck element? (attributes didn't work)
  $('.form-text.form-autocomplete').change(Drupal.brightcove_cck.actions.change);
};

Drupal.brightcove_cck.actions.change = function() {
  $('.brightcove-cck-remove-button[rel="' + $(this).attr('id') + '"]').attr('disabled', '');
}
Drupal.brightcove_cck.actions.remove = function() {
  $('#' + $(this).attr('rel')).val('');
}

Drupal.brightcove_cck.actions.browse = function() {
  var id = $(this).attr('rel');
  Drupal.modalFrame.open({onSubmit: Drupal.brightcove_cck.submit(id), url: Drupal.settings.basePath + 'brightcove_cck/browse', width: 800, height: 600, autoFit: false});
  return false;
}

Drupal.brightcove_cck.submit = function(settings) {
  return function(args) {
    $("#" + settings).val(args.selected)
    $('.brightcove-cck-remove-button[rel="' + settings + '"]').attr('disabled', '');
  };
}
