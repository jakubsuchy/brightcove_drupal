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
class brightcove_cck_handler_field_video_date extends content_handler_field_multiple {
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

    // This is a generic handler - we take the BC video object field from real_field. Example:
    // real_field: field_bc_video_video_id
    // field: field_bc_video_video_id_name
    // field - real_field = 'name' -> Display 'name' field.
    $this->bc_field = str_replace($this->real_field . '_', '', $this->field);

  }

    function admin_summary() {
      return '';
    }

  function options(&$options) {
    parent::options($options);
    $field = $this->content_field;

    // Override views_handler_field_node's default label
    $options['label'] = '';
    $options['format'] = 'default';
    $options['date_format'] = 'small';
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
    $time = time();

    $form['date_format'] = array(
        '#type' => 'select',
        '#title' => t('Date format'),
        '#options' => array(
          'small' => format_date($time, 'small'),
          'medium' => format_date($time, 'medium'),
          'large' => format_date($time, 'large'),
          'custom' => t('Custom'),
          'raw time ago' => t('Time ago'),
          'time ago' => t('Time ago (with "ago" appended)'),
          'raw time span' => t('Time span (future dates start with - )'),
          'time span' => t('Time span (with "ago/hence" appended)'),
          ),
        '#default_value' => isset($this->options['date_format']) ? $this->options['date_format'] : 'small',
        );
    $form['custom_date_format'] = array(
        '#type' => 'textfield',
        '#title' => t('Custom date format'),
        '#description' => t('If "Custom", see <a href="http://us.php.net/manual/en/function.date.php" target="_blank">the PHP docs</a> for date formats. If "Time ago" this is the the number of different units to display, which defaults to two.'),
        '#default_value' => isset($this->options['custom_date_format']) ? $this->options['custom_date_format'] : '',
        '#process' => array('views_process_dependency'),
        '#dependency' => array('edit-options-date-format' => array('custom', 'raw time ago', 'time ago', 'raw time span', 'time span')),
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
      if (isset($video->{$this->bc_field})) {
        $value = floor($video->{$this->bc_field} / 1000);
        $time_diff = $_SERVER['REQUEST_TIME'] - $value; // will be positive for a datetime in the past (ago), and negative for a datetime in the future (hence)
        switch ($format) {
          case 'raw time ago':
            return format_interval($time_diff, is_numeric($custom_format) ? $custom_format : 2);
          case 'time ago':
            return t('%time ago', array('%time' => format_interval($time_diff, is_numeric($custom_format) ? $custom_format : 2)));
          case 'raw time span':
            return ($time_diff < 0 ? '-' : '') . format_interval(abs($time_diff), is_numeric($custom_format) ? $custom_format : 2);
          case 'time span':
            return t(($time_diff < 0 ? '%time hence' : '%time ago'), array('%time' => format_interval(abs($time_diff), is_numeric($custom_format) ? $custom_format : 2)));
          case 'custom':
            return format_date($value, $format, $custom_format);
          default:
            return format_date($value, $format);
        }
      }
    }
    return theme('views_nodate');
  }

}
