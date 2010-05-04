Drupal.brightcove_cck = {};
Drupal.brightcove_cck.actions = {};

Drupal.behaviors.brightcove_cck_buttons = function(context) {
  $('.brightcove-cck-browse-button', context).click(Drupal.brightcove_cck.actions.browse);
};


Drupal.brightcove_cck.actions.browse = function() {
  var id = $(this).attr('rel');
  Drupal.modalFrame.open({onSubmit: Drupal.brightcove_cck.submit(id), url: Drupal.settings.basePath + 'brightcove_cck/browse', width: 800, height: 600, autoFit: false});
  return false;
}

Drupal.brightcove_cck.submit = function(settings) {
  return function(args) {
          $("#" + settings).val(args.selected)
  };
}
