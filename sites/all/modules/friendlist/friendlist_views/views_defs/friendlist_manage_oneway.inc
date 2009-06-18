<?php

  $view = new view;
  $view->name = 'friendlist_manage_oneway';
  $view->description = 'Old style friendlist view. Included for backwards compatibility';
  $view->tag = 'friendlist';
  $view->view_php = '';
  $view->base_table = 'friendlist_relations';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Default', 'default');
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
    'status' => array(
      'label' => 'Status',
      'exclude' => 0,
      'id' => 'status',
      'table' => 'friendlist_statuses',
      'field' => 'status',
      'relationship' => 'none',
    ),
    'name' => array(
      'label' => 'Name',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'requestee_id',
    ),
    'name_1' => array(
      'label' => 'Name',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name_1',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'requester_id',
    ),
  ));
  $handler->override_option('filters', array(
    'oneway' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'oneway',
      'table' => 'friendlist_relation_types',
      'field' => 'oneway',
      'relationship' => 'none',
    ),
    'requester_id_current' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'requester_id_current',
      'table' => 'friendlist_relations',
      'field' => 'requester_id_current',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '2' => 2,
    ),
  ));
  $handler->override_option('title', 'Oneway Management');
  $handler->override_option('header_format', '1');
  $handler->override_option('header_empty', 0);
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 25);
  $handler->override_option('use_pager', '1');
  $handler->override_option('use_more', 0);
  $handler->override_option('style_plugin', 'table');
  $handler = $view->new_display('page', 'Management', 'page_1');
  $handler->override_option('fields', array(
    'name' => array(
      'label' => 'Name',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'requestee_id',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'message' => array(
      'label' => 'Message sent',
      'exclude' => 0,
      'id' => 'message',
      'table' => 'friendlist_relations',
      'field' => 'message',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'last_update_time' => array(
      'label' => 'Connected',
      'date_format' => 'custom',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'last_update_time',
      'table' => 'friendlist_statuses',
      'field' => 'last_update_time',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'action_link_requestee' => array(
      'label' => 'Actions',
      'text' => '',
      'exclude' => 0,
      'id' => 'action_link_requestee',
      'table' => 'friendlist_relations',
      'field' => 'action_link_requestee',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('header', '<em>This page lists all your oneway connections.</em>');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 1);
  $handler->override_option('empty', '<h3>You have no oneway connections.</h3>');
  $handler->override_option('empty_format', '2');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'name' => 'name',
      'message' => 'message',
      'last_update_time' => 'last_update_time',
      'action_link_requestee' => 'action_link_requestee',
    ),
    'info' => array(
      'name' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'message' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_update_time' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'action_link_requestee' => array(
        'separator' => '',
      ),
    ),
    'default' => 'last_update_time',
  ));
  $handler->override_option('path', 'connections/manage/oneway');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Oneway management',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'tab',
    'title' => 'Relations',
    'weight' => '0',
  ));

