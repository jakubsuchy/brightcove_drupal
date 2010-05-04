Drupal.brightcove_cck = {};

Drupal.behaviors.brightcove_cck_attach = function(context) {
  $('.brightcove-cck-attach-button', context).click(function() {
      });
};


Drupal.brightcove_cck.submit = function(settings) {
  return function(args) {
          alert(args);
  };
}
