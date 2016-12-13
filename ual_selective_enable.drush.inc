<?php

/**
 * Implements hook_drush_help().
 */
function ual_selective_enable_drush_help($section) {
  switch ($section) {
    case 'drush:ual-selective-enable':
      return dt('Selectively enable modules against a predefined list.');
  }
}

/**
 * Implements hook_drush_command().
 */
function ual_selective_enable_drush_command() {
  $items = array();

  $items['ual-selective-enable'] = array(
    'description' => 'Selectively enable modules against a list',
    'callback' => 'drush_ual_selective_enable',
    'options' => array(
      'base_modules' => 'A JSON file containing the required modules'
    ),
    'aliases' => array('sel-en'),
  );

  return $items;
}

function drush_ual_selective_enable() {
  $config_filename = drush_get_option('base_modules', NULL);
  $config_handle = fopen($config_filename, 'r');

  if(!$config_handle) {
    ual_selective_enable_fatal_error("Could not open $config_filename");
  }
  $config_json = fread($config_handle, filesize($config_filename));
  if(!$config_handle) {
    ual_selective_enable_fatal_error("Could not read $config_filename");
  }
  $parsed_json = json_decode($config_json, TRUE);
  if(!$parsed_json) {
    ual_selective_enable_fatal_error("Could not parse $config_filename");
  }
  if(!isset($parsed_json['base_modules'])) {
    ual_selective_enable_fatal_error("No base_modules key was specified in $config_filename");
  }

  $base_modules = $parsed_json['base_modules'];
  $enabled_modules = array_keys(drush_module_list());
  $enabled_base_modules = array_intersect($base_modules, $enabled_modules);
  $disabled_base_modules = array_diff($base_modules, $enabled_base_modules);
  if(!empty($disabled_base_modules)) {
    drush_print("The following base module(s) were not enabled: \n" . implode($disabled_base_modules, ","));
    drush_print("Enabling....");
    drush_invoke_process("@self", "pm-enable", $disabled_base_modules);
  }

}

function ual_selective_enable_fatal_error($message) {
  $message = "Error: " . $message;
  drush_print($message);
  drush_log($message, 'error');
  exit();
}
