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
    'zen',
    'adminimal',
    'adminimal_admin_menu',
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
    'imagemagick',
    'ual_chosen_library',
    'ual_mail_settings',
    'ual_summary_settings',
    'ual_common_field_bases',
    'ual_image_styles',
    'redux_ual',
    'ual_footer_content',
    'ual_frontend_tools',
    'ual_ds_view_modes',
    'ual_user_and_profile_settings',
    'ual_appearance_settings',
    'ual_permissions',
    'ual_wysiwyg',
    'ual_content_tools',
    'ual_user_management_tools',
    'ual_system_settings',
    'ual_authentication',
    'ual_homepage_hours',
    'ual_rooms_spaces',
    'ual_rooms_permissions',
    'ual_home_page',
    'ual_page_content_type',
    'ual_page_permissions',
    'ual_google_custom_search',
    'ual_ask',
    'ual_ga_settings',
    'siteimprove_analytics',
    'ual_events_source',
    'ual_readmore_and_teaser',
    'ual_media',
    'ual_media_permissions',
    'ual_personal_message',
    'ual_personal_message_permissions',
    'ual_content_alert',
    'ual_content_alert_permissions',
    'ual_environment_indicator',
    'ual_libguides_content',
    'ual_libguides_permissions',
    'ual_libguides_views',
    'ual_all_nodes_view',
    'ual_cse',
    'ual_homepage_search',
    'ual_news_events',
    'ual_library_locations',
    'ual_eq_structure',
    'ual_eq_permissions',
    'view_unpublished',
    'ual_content_permissions',
    'ual_webform_settings',
    'ual_webform_permissions',
    'ual_giving',
    'ual_giving_views',
    'ual_giving_permissions',
    'ual_giving_cta',
    'ual_dblogin',
    'ual_dblogin_form_placement',
    'ual_set_csp_frame_ancestors',
    'bookstore_linker',
    'paragraphs',
    'paragraphs_bundle_permissions',
    'ual_flexible_content_permissions',
    'ual_hero_media',
    'focal_point',
    'ual_paragraphs_ui',
  );

  $enabled_modules = array_keys(drush_module_list());
  $enabled_base_modules = array_intersect($base_modules, $enabled_modules);
  $disabled_base_modules = array_diff($base_modules, $enabled_base_modules);
  if(!empty($disabled_base_modules)) {
    drush_print("The following base module(s) were not enabled: \n" . implode($disabled_base_modules, ","));
    drush_print("Enabling....");
    drush_invoke_process("@self", "pm-enable", $disabled_base_modules);
  }
}
