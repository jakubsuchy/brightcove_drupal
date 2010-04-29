Drupal.brightcove_cck = {};
Drupal.brightcove_cck.actions = {};

Drupal.behaviors.brightcove_cck_buttons = function(context) {
    $('.brightcove-cck-browse-button', context).click(Drupal.brightcove_cck.actions.browse);
};


Drupal.brightcove_cck.actions.browse = function() {
 var options = {
      // TODO these options need to be (1) specific to modalframe dialog instances
      // and (2) presented in the settings form or translated from the options
      // there. autoFit is necessary to prevent the dialog from changing size all
      // the time.
url: 'brightcove_cck/browse',
autoFit: false
};
Drupal.modalFrame.open({url: 'brightcove_cck/browse'});
}
