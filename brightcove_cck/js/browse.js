Drupal.brightcove_cck = {};
Drupal.brightcove_cck.actions = {};

Drupal.behaviors.brightcove_cck_buttons = function(context) {
  $('.brightcove-cck-browse-button', context).click(Drupal.brightcove_cck.actions.browse);
};


Drupal.brightcove_cck.actions.browse = function() {
  Drupal.modalFrame.open({url: Drupal.settings.basePath + 'brightcove_cck/browse', width: 800, height: 600, autoFit: false});
  return false;
}
