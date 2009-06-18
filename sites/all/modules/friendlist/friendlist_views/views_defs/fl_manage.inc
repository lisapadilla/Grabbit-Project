<?php

  $view = new view;
  $view->name = 'fl_manage';
  $view->description = 'Friendlist community management. Responsible for the tab creation and its management pages.';
  $view->tag = 'friendlist';
  $view->view_php = '';
  $view->base_table = 'friendlist_relations';
  $view->is_cacheable = FALSE;
  $view->api_version = 2;
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
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
  $handler->override_option('header_format', '2');
  $handler->override_option('header_empty', 0);
  $handler->override_option('footer_format', '1');
  $handler->override_option('footer_empty', 0);
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 36);
  $handler->override_option('use_pager', '1');
  $handler->override_option('use_more', 0);
  $handler->override_option('style_plugin', 'table');
  $handler = $view->new_display('page', 'Friends', 'page_1');
  $handler->override_option('fields', array(
    'picture' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'picture',
      'table' => 'users',
      'field' => 'picture',
      'relationship' => 'requestee_id',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
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
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<em>Friends since [last_update_time]<em>',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'date_format' => 'raw time ago',
      'custom_date_format' => '1',
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
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
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
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'current_user',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'requester_id',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'override' => array(
        'button' => 'Override',
      ),
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => 'global $user;
          $uid = arg(1);
          $account = user_load(array(\'uid\' =>$uid));
          if($account->uid == $user->uid){
          return TRUE;
          }',
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
    'active' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'active',
      'table' => 'friendlist_relation_types',
      'field' => 'active',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'oneway' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'oneway',
      'table' => 'friendlist_relation_types',
      'field' => 'oneway',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'rtid' => array(
      'operator' => 'in',
      'value' => array(
        '1' => '1',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'rtid',
      'table' => 'friendlist_relations',
      'field' => 'rtid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('footer', '<em>Friend relationships.<em>');
  $handler->override_option('footer_empty', 1);
  $handler->override_option('empty', '<em>This page shows all the friends you made. Currently you have not yet made any friends yet.</em>');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'picture' => 'picture',
      'name' => 'name',
      'last_update_time' => 'last_update_time',
      'action_link_requestee' => 'action_link_requestee',
    ),
    'info' => array(
      'picture' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_update_time' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'action_link_requestee' => array(
        'separator' => '',
      ),
    ),
    'default' => 'last_update_time',
  ));
  $handler->override_option('row_options', array(
    'inline' => array(
      'picture' => 'picture',
      'name' => 'name',
    ),
    'separator' => '',
  ));
  $handler->override_option('path', 'user/%/community/friends');
  $handler->override_option('menu', array(
    'type' => 'default tab',
    'title' => 'Friends',
    'description' => '',
    'weight' => '0',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'tab',
    'title' => 'Community',
    'description' => '',
    'weight' => '5',
  ));
  $handler = $view->new_display('page', 'Sent', 'page_2');
  $handler->override_option('fields', array(
    'picture' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'picture',
      'table' => 'users',
      'field' => 'picture',
      'relationship' => 'requestee_id',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
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
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
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
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<em>Sent [create_time] ago</em>',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'date_format' => 'raw time ago',
      'custom_date_format' => '1',
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
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
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
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'current_user',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'requester_id',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'override' => array(
        'button' => 'Override',
      ),
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => 'global $user;
          $uid = arg(1);
          $account = user_load(array(\'uid\' =>$uid));
          if($account->uid == $user->uid){
          return TRUE;
          }',
    ),
  ));
  $handler->override_option('filters', array(
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
    'active' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'active',
      'table' => 'friendlist_relation_types',
      'field' => 'active',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'oneway' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'oneway',
      'table' => 'friendlist_relation_types',
      'field' => 'oneway',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'rtid' => array(
      'operator' => 'in',
      'value' => array(
        '1' => '1',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'rtid',
      'table' => 'friendlist_relations',
      'field' => 'rtid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Sent Requests');
  $handler->override_option('footer', '<em>Friend relationships.<em>');
  $handler->override_option('footer_empty', 1);
  $handler->override_option('empty', '<em>This page lists the friend requests you send. You have no outgoing requests.</em>');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'picture' => 'picture',
      'name' => 'name',
      'message' => 'message',
      'create_time' => 'create_time',
      'action_link_requestee' => 'action_link_requestee',
    ),
    'info' => array(
      'picture' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'message' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'create_time' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'action_link_requestee' => array(
        'separator' => '',
      ),
    ),
    'default' => 'create_time',
  ));
  $handler->override_option('path', 'user/%/community/sent');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Sent',
    'description' => '',
    'weight' => '1',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'normal',
    'title' => 'Manage',
    'description' => '',
    'weight' => '0',
  ));
  $handler = $view->new_display('page', 'Received', 'page_3');
  $handler->override_option('fields', array(
    'picture' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'picture',
      'table' => 'users',
      'field' => 'picture',
      'relationship' => 'requester_id',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
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
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
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
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<em>Received [create_time] ago</em>',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'date_format' => 'raw time ago',
      'custom_date_format' => '1',
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
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
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
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'current_user',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'requestee_id',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => 'global $user;
          $uid = arg(1);
          $account = user_load(array(\'uid\' =>$uid));
          if($account->uid == $user->uid){
          return TRUE;
          }',
    ),
  ));
  $handler->override_option('filters', array(
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
    'active' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'active',
      'table' => 'friendlist_relation_types',
      'field' => 'active',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'oneway' => array(
      'operator' => '=',
      'value' => '0',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'oneway',
      'table' => 'friendlist_relation_types',
      'field' => 'oneway',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'rtid' => array(
      'operator' => 'in',
      'value' => array(
        '1' => '1',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'rtid',
      'table' => 'friendlist_relations',
      'field' => 'rtid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Received Requests');
  $handler->override_option('footer', '<em>Friend relationships.<em>');
  $handler->override_option('footer_empty', 1);
  $handler->override_option('empty', '<em>This page lists the requests you received. You have no incoming requests.</em>');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'picture' => 'picture',
      'name' => 'name',
      'message' => 'message',
      'create_time' => 'create_time',
      'action_link_requester' => 'action_link_requester',
    ),
    'info' => array(
      'picture' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'message' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'create_time' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'action_link_requester' => array(
        'separator' => '',
      ),
    ),
    'default' => 'create_time',
  ));
  $handler->override_option('path', 'user/%/community/received');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Received',
    'description' => '',
    'weight' => '2',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('page', 'Following', 'page_4');
  $handler->override_option('fields', array(
    'picture' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'picture',
      'table' => 'users',
      'field' => 'picture',
      'relationship' => 'requestee_id',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
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
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<em>Following for [last_update_time]</em>',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'date_format' => 'raw time ago',
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
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
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
  $handler->override_option('arguments', array(
    'uid' => array(
      'default_action' => 'default',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'default_argument_type' => 'current_user',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'requester_id',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'override' => array(
        'button' => 'Override',
      ),
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => 'global $user;
          $uid = arg(1);
          $account = user_load(array(\'uid\' =>$uid));
          if($account->uid == $user->uid){
          return TRUE;
          }',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => 'in',
      'value' => array(
        'OW_1_TO_2' => 'OW_1_TO_2',
        'OW_BOTH' => 'OW_BOTH',
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
    'active' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'active',
      'table' => 'friendlist_relation_types',
      'field' => 'active',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'oneway' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'oneway',
      'table' => 'friendlist_relation_types',
      'field' => 'oneway',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'rtid' => array(
      'operator' => 'in',
      'value' => array(
        '2' => '2',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'rtid',
      'table' => 'friendlist_relations',
      'field' => 'rtid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('footer', '<em>Fan relationships.<em>');
  $handler->override_option('footer_empty', 1);
  $handler->override_option('empty', '<em>This page lists the people you follow. You are not following anyone yet.</em>');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'picture' => 'picture',
      'name' => 'name',
      'last_update_time' => 'last_update_time',
      'action_link_requestee' => 'action_link_requestee',
    ),
    'info' => array(
      'picture' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_update_time' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'action_link_requestee' => array(
        'separator' => '',
      ),
    ),
    'default' => 'last_update_time',
  ));
  $handler->override_option('path', 'user/%/community/following');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Following',
    'description' => '',
    'weight' => '3',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $handler = $view->new_display('page', 'Followers', 'page_5');
  $handler->override_option('fields', array(
    'picture' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'exclude' => 0,
      'id' => 'picture',
      'table' => 'users',
      'field' => 'picture',
      'relationship' => 'requester_id',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'name' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'link_to_user' => 1,
      'overwrite_anonymous' => 0,
      'anonymous_text' => '',
      'exclude' => 0,
      'id' => 'name',
      'table' => 'users',
      'field' => 'name',
      'relationship' => 'requester_id',
      'override' => array(
        'button' => 'Use default',
      ),
    ),
    'last_update_time' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<em>Following you for [last_update_time]</em>',
        'make_link' => 0,
        'path' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
      ),
      'date_format' => 'raw time ago',
      'custom_date_format' => '1',
      'exclude' => 0,
      'id' => 'last_update_time',
      'table' => 'friendlist_statuses',
      'field' => 'last_update_time',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
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
      'default_argument_type' => 'current_user',
      'default_argument' => '',
      'validate_type' => 'php',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'uid',
      'table' => 'users',
      'field' => 'uid',
      'relationship' => 'requestee_id',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        '2' => 0,
        '3' => 0,
      ),
      'override' => array(
        'button' => 'Use default',
      ),
      'default_options_div_prefix' => '',
      'default_argument_user' => 0,
      'default_argument_fixed' => '',
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'page' => 0,
        'story' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_user_restrict_roles' => 0,
      'validate_argument_php' => 'global $user;
          $uid = arg(1);
          $account = user_load(array(\'uid\' =>$uid));
          if($account->uid == $user->uid){
          return TRUE;
          }',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => 'in',
      'value' => array(
        'OW_2_TO_1' => 'OW_2_TO_1',
        'OW_BOTH' => 'OW_BOTH',
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
    'active' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'active',
      'table' => 'friendlist_relation_types',
      'field' => 'active',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'oneway' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'oneway',
      'table' => 'friendlist_relation_types',
      'field' => 'oneway',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
    'rtid' => array(
      'operator' => 'in',
      'value' => array(
        '2' => '2',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'rtid',
      'table' => 'friendlist_relations',
      'field' => 'rtid',
      'override' => array(
        'button' => 'Use default',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('title', 'Followers');
  $handler->override_option('footer', '<em>Fan relationships.<em>');
  $handler->override_option('footer_empty', 1);
  $handler->override_option('empty', '<em>This page lists the people that follow you. You have nobody following you yet.</em>');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'desc',
    'columns' => array(
      'picture' => 'picture',
      'name' => 'name',
      'last_update_time' => 'last_update_time',
    ),
    'info' => array(
      'picture' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'name' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'last_update_time' => array(
        'sortable' => 0,
        'separator' => '',
      ),
    ),
    'default' => 'last_update_time',
  ));
  $handler->override_option('path', 'user/%/community/followers');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'Followers',
    'description' => '',
    'weight' => '4',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
  ));
  $views[$view->name] = $view;

