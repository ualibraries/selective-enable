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
    'aliases' => array('sel-en'),
  );

  return $items;
}

function drush_ual_selective_enable() {
  $base_modules = array(
    'views',
    'views_field_view',
    'views_content_cache',
    'panels',
    'panels_node',
    'panels_ipe',
    'ctools_custom_content',
    'ctools_access_ruleset',
    'views_content',
    'views_ui',
    'features',
    'context',
    'context_ui',
    'field_ui',
    'context_error',
    'customerror',
    'migrate',
    'ual_migrate',
    'ual_login_disable',
    'date',
    'date_api',
    'date_popup',
    'computed_field',
    'node_export',
    'field_collection',
    'field_collection_deploy',
    'link',
    'jquery_update',
    'ual_website_alerts',
    'conditional_styles',
    'path',
    'pathauto',
    'path_alias_xt',
    'metatag',
    'metatag_views',
    'metatag_context',
    'globalredirect',
    'rabbit_hole',
    'rh_node',
    'rh_taxonomy',
    'webform',
    'webform_multiple_file',
    'honeypot',
    'smtp',
    'override_node_options',
    'entityreference_autocomplete',
    'views_ui_basic',
    'services',
    'rest_server',
    'regions',
    'job_scheduler',
    'feeds',
    'feeds_ui',
    'feeds_jsonpath_parser',
    'feeds_xpathparser',
    'roleassign',
    'genpass',
    'nocurrent_pass',
    'composer_manager',
    'composer_manager_sa',
    'owlcarousel',
    'owlcarousel_fields',
    'owlcarousel_ui',
    'owlcarousel_views',
    'entity_token',
    'cacheexclude',
    'imagemagick'
  );

  $enabled_modules = array_keys(drush_module_list());
  $enabled_base_modules = array_intersect($base_modules, $enabled_modules);
  $disabled_base_modules = array_diff($base_modules, $enabled_base_modules);
  if(!empty($disabled_base_modules)) {
    drush_print("The following base module(s) were not enabled: \n" . implode($disabled_base_modules, ","));
    drush_print("Enabling....");
    drush_module_enable($disabled_base_modules);
  }
}
