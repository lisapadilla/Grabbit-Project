<?php

  $view = new view;
  $view->name = 'friendlist_manage_twoway';
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
  $handler->override_option('access', array(
    'type' => 'role',
    'role' => array(
      '2' => 2,
    ),
  ));
  $handler->override_option('title', 'Twoway Management');
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
    'last_update_time' => array(
      'label' => 'Connected',
      'date_format' => 'time ago',
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
  $handler->override_option('filters', array(
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
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
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
  $handler->override_option('header', '<em>This page lists all your established twoway connections.</em>');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 1);
  $handler->override_option('empty', '<h3>You not made any twoway connections.</h3>');
  $handler->override_option('empty_format', '2');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'name' => 'name',
      'last_update_time' => 'last_update_time',
      'action_link_requestee' => 'action_link_requestee',
    ),
    'info' => array(
      'name' => array(
        'sortable' => 1,
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
  $handler->override_option('path', 'connections/manage/twoway');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Twoway management',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'tab',
    'title' => 'Relations',
    'weight' => '0',
  ));
  $handler = $view->new_display('page', 'Send', 'page_2');
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
      'label' => 'Message',
      'exclude' => 0,
      'id' => 'message',
      'table' => 'friendlist_relations',
      'field' => 'message',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'create_time' => array(
      'label' => 'Date request',
      'date_format' => 'time ago',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'create_time',
      'table' => 'friendlist_relations',
      'field' => 'create_time',
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
  $handler->override_option('filters', array(
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
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => 'in',
      'value' => array(
        'TW_1_TO_2_P' => 'TW_1_TO_2_P',
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
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Connection requests: Send');
  $handler->override_option('header', '<em>This page lists the connection requests you send.</em>');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 1);
  $handler->override_option('empty', '<h3>You have no outgoing requests.</h3>');
  $handler->override_option('empty_format', '2');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'name' => 'name',
      'message' => 'message',
      'create_time' => 'create_time',
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
      'create_time' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'action_link_requestee' => array(
        'separator' => '',
      ),
    ),
    'default' => 'create_time',
  ));
  $handler->override_option('path', 'connections/send');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Twoway send',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Manage',
    'weight' => '0',
  ));
  $handler = $view->new_display('page', 'Received', 'page_3');
  $handler->override_option('fields', array(
    'name' => array(
      'label' => 'Name',
      'link_to_user' => 1,
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'requester_id',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'message' => array(
      'label' => 'Message',
      'exclude' => 0,
      'id' => 'message',
      'table' => 'friendlist_relations',
      'field' => 'message',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'create_time' => array(
      'label' => 'Date request',
      'date_format' => 'time ago',
      'custom_date_format' => '',
      'exclude' => 0,
      'id' => 'create_time',
      'table' => 'friendlist_relations',
      'field' => 'create_time',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'action_link_requester' => array(
      'label' => 'Actions',
      'text' => '',
      'exclude' => 0,
      'id' => 'action_link_requester',
      'table' => 'friendlist_relations',
      'field' => 'action_link_requester',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'requestee_id_current' => array(
      'operator' => '=',
      'value' => 1,
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'requestee_id_current',
      'table' => 'friendlist_relations',
      'field' => 'requestee_id_current',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'status' => array(
      'operator' => 'in',
      'value' => array(
        'TW_1_TO_2_P' => 'TW_1_TO_2_P',
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
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Connection requests: Received');
  $handler->override_option('header', '<em>This page lists the connection requests you received.</em>');
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 1);
  $handler->override_option('empty', '<h3>You have no incoming requests.</h3>');
  $handler->override_option('empty_format', '2');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'name' => 'name',
      'message' => 'message',
      'create_time' => 'create_time',
      'action_link_requester' => 'action_link_requester',
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
      'create_time' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'action_link_requester' => array(
        'separator' => '',
      ),
    ),
    'default' => 'create_time',
  ));
  $handler->override_option('path', 'connections/received');
  $handler->override_option('menu', array(
    'type' => 'normal',
    'title' => 'Twoway received',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'weight' => 0,
  ));
