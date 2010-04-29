<?php

function brightcove_cck_browse() {
  sleep(2);
  $output = 'ahoj';
  modalframe_child_js(); //dialog internal area
  return drupal_json($output);
}
