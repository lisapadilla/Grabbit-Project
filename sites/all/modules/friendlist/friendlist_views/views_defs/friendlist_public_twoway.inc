<?php

  $view = new view;
  $view->name = 'friendlist_public_twoway';
  $view->description = 'Old style friendlist view. Included for backwards compatibility';
  $view->tag = 'friendlist';
  $view->view_php = '';
  $view->base_table = 'friendlist_relations';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'requestee_id' => array(
      'label' => 'Requestee',
      'required' => 0,
      'id' => 'requestee_id',
      'table' => 'friendlist_relations',
      'field' => 'requestee_id',
      'relationship' => 'none',
    ),
    'requester_id' => array(
      'label' => 'Requester',
      'required' => 0,
      'id' => 'requester_id',
      'table' => 'friendlist_relations',
      'field' => 'requester_id',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('fields', array(
    'name' => array(
      'label' => '',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'requester_id',
    ),
  ));
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'user',
      'default_argument' => '',
      'validate_type' => 'none',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'requestee_id',
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => 'in',
      'value' => array(
        'TW_BOTH' => 'TW_BOTH',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'friendlist_statuses',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('title', 'Connections');
  $handler->override_option('empty', 'No available connections.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('use_more', 1);
  $handler->override_option('style_plugin', 'grid');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'columns' => '5',
    'alignment' => 'horizontal',
  ));
  $handler = $view->new_display('block', 'Connections block', 'block_1');
  $handler->override_option('title', 'Latest connections');
  $handler->override_option('style_plugin', 'list');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'type' => 'ul',
  ));
  $handler->override_option('block_description', 'Latest friends');
  $handler->override_option('block_caching', -1);
  $handler = $view->new_display('page', 'Connections page', 'page_1');
  $handler->override_option('title', 'All current connections');
  $handler->override_option('items_per_page', 50);
  $handler->override_option('use_pager', '1');
  $handler->override_option('path', 'connections/%/connected');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
  $views[$view->name] = $view;