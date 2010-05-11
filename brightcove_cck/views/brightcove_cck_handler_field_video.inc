<?php
// $Id: content_handler_field.inc,v 1.1.2.17 2009/07/22 20:46:55 markuspetrux Exp $

/**
 * @file
 * The subclass adds basic field and formatter info,
 * for field-specific subclasses to use if they need to.
 *
 * Fields could extend this class if they want field and formatter handling
 * but don't want the multiple value grouping options created by
 * content_handler_field_multiple.
 */
class brightcove_cck_handler_field_video extends content_handler_field_multiple {
  var $content_field;

  function construct() {
    parent::construct();
    $this->content_field = content_fields($this->definition['content_field_name']);
  }

  function init(&$view, $options) {
    $field = $this->content_field;
    parent::init($view, $options);
    if ($field['multiple']) {
      $this->additional_fields['delta'] = 'delta';
    }
    // Make sure we grab enough information to build a pseudo-node with enough
    // credentials at render-time.
    $this->additional_fields['type'] = array('table' => 'node', 'field' => 'type');
    $this->additional_fields['nid'] = array('table' => 'node', 'field' => 'nid');
    $this->additional_fields['vid'] = array('table' => 'node', 'field' => 'vid');
  }

  function options(&$options) {
    parent::options($options);
    $field = $this->content_field;

    // Override views_handler_field_node's default label
    $options['label'] = '';
    $options['format'] = 'default';
  }

  /**
   * Provide formatter option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // TODO: do we want the 'link to node' checkbox ?
    // That's usually formatters business...

    $field = $this->content_field;
    $options = $this->options;
      
    unset($form['format']);
    unset($form['label_type']);
    $form['label'] = array( 
      '#type' => 'textfield', 
      '#title' => t('Label'), 
      '#default_value' => isset($this->options['label']) ? $this->options['label'] : '', 
      '#description' => t('The label for this field that will be displayed to end users if the style requires it.'),
    );
  }

  function label() {
    return $this->options['label'];
  }

  function options_validate($form, &$form_state) { }

  function render($values) {
    $value = $values->{$this->field_alias};
    if (empty($value)) {
      return '';
    }
    $video = brightcove_video_load($value);
    if (!empty($video)) {
      return check_plain($video->name);
    }
    return '';
  }

}
