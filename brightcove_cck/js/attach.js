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
/**
  * Overriding Drupal.modalFrameChild.behaviors.parseLinks function from
  * modalframe in order to ensure that pager links do not point to
  * target="_new"
  * Just return for now.
  */
Drupal.modalFrameChild.behaviors.parseLinks = function(context) {
  return;
};


