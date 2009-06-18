<?php
// $Id: hb_activity.rules_defaults.inc,v 1.1.2.2 2008/12/28 20:33:49 stalski Exp $


/**
 * @file
 * Rules' pre-configured rules for default drupal core behaviour.
 */

/**
 * Implementation of hook_rules_defaults
 *
 * @return configured rules array
 */
function hb_activity_rules_defaults() {  	
	return	array (
	  'rules' => 
	  array (
	  
	  
      'rules_heartbeat_0' => 
      array (
        '#type' => 'rule',
        '#categories' => 
        array (
          0 => 'heartbeat',
        ),
        '#set' => 'event_node_update',
        '#label' => 'Heartbeat - user updates content',
        '#active' => 1,
        '#weight' => '0',
        '#status' => 'default',
        '#conditions' => 
        array (
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 5,
            '#type' => 'action',
            '#settings' => 
            array (
              'uid_param' => '[user:user-id]',
              'uid_target_param' => '[user:uid]',
              'nid_target_param' => '[node:nid]',
              'message_id_param' => 'heartbeat_edit_node',
              'variables_param' => '@username=|=[node:author-name-url]-|-@node_type=|=[node:type]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'uid_param' => 
                  array (
                    0 => 'user',
                  ),
                  'nid_target_param' => 
                  array (
                    0 => 'node',
                  ),
                  'variables_param' => 
                  array (
                    0 => 'node',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'user',
                  ),
                ),
              ),
            ),
            '#name' => 'hb_activity_rules_default_action',
            '#info' => 
            array (
              'label' => 'Logs relational user activity on node change',
              'label callback' => false,
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'nid_target_param',
                3 => 'message_id_param',
                4 => 'variables_param',
              ),
              'module' => 'Heartbeat activity',
            ),
          ),
        ),
      ),
      
      
	    'rules_heartbeat_1' => 
	    array (
	      '#type' => 'rule',
	      '#categories' => 
	      array (
	        0 => 'heartbeat',
	      ),
	      '#set' => 'event_node_insert',
	      '#label' => 'Heartbeat - user adds new page content',
	      '#active' => 1,
	      '#weight' => '10',
	      '#status' => 'altered',
	      '#conditions' => 
	      array (
	        0 => 
	        array (
	          '#type' => 'condition',
	          '#settings' => 
	          array (
	            '#argument map' => 
	            array (
	              'node' => 'node',
	            ),
	          ),
	          '#name' => 'rules_condition_content_is_published',
	          '#info' => 
	          array (
	            'label' => 'Created content is published',
	            'arguments' => 
	            array (
	              'node' => 
	              array (
	                'type' => 'node',
	                'label' => 'Inhoud',
	              ),
	            ),
	            'module' => 'Node',
	          ),
	          '#weight' => 0,
	        ),
	        1 => 
	        array (
	          '#weight' => 0,
	          '#info' => 
	          array (
	            'label' => 'Created content is Pagina',
	            'arguments' => 
	            array (
	              'node' => 
	              array (
	                'type' => 'node',
	                'label' => 'Inhoud',
	              ),
	            ),
	            'module' => 'Node',
	          ),
	          '#name' => 'rules_condition_content_is_type',
	          '#settings' => 
	          array (
	            'type' => 
	            array (
	              'page' => 'page',
	            ),
	            '#argument map' => 
	            array (
	              'node' => 'node',
	            ),
	          ),
	          '#type' => 'condition',
	        ),
	      ),
	      '#actions' => 
	      array (
	        0 => 
	        array (
	          '#type' => 'action',
	          '#settings' => 
	          array (
	            'uid_param' => '[user:user-id]',
	            'uid_target_param' => '0',
	            'nid_target_param' => '[node:nid]',
	            'message_id_param' => 'heartbeat_add_node',
	            'variables_param' => '@username=|=[user:user-name-url]-|-@node_type=|=[node:type]-|-@node_title=|=[node:title-link]-|-',
	            '#eval input' => 
	            array (
	              'token_rules_input_evaluator' => 
	              array (
	                'uid_param' => 
	                array (
	                  0 => 'user',
	                ),
	                'nid_target_param' => 
	                array (
	                  0 => 'node',
	                ),
	                'variables_param' => 
	                array (
	                  0 => 'node',
	                  1 => 'user',
	                ),
	              ),
	            ),
	          ),
	          '#name' => 'hb_activity_rules_default_action',
	          '#info' => 
	          array (
	            'label' => 'Logs relational user activity',
	            'eval input' => 
	            array (
	              0 => 'uid_param',
	              1 => 'uid_target_param',
	              2 => 'nid_target_param',
	              3 => 'message_id_param',
	              4 => 'variables_param',
	            ),
	            'module' => 'Heartbeat activity',
	          ),
	          '#weight' => 10,
	        ),
	      ),
	    ),
	    
	    
	    'rules_heartbeat_2' => 
	    array (
	      '#type' => 'rule',
	      '#categories' => 
	      array (
	        0 => 'heartbeat',
	      ),
	      '#set' => 'event_comment_insert',
	      '#label' => 'Heartbeat - user replies to content (all types)',
	      '#active' => 1,
	      '#weight' => '3',
	      '#status' => 'default',
	      '#conditions' => 
	      array (
	      ),
	      '#actions' => 
	      array (
	        0 => 
	        array (
	          '#weight' => 8,
	          '#info' => 
	          array (
	            'label' => 'Logs relational user activity',
	            'eval input' => 
	            array (
	              0 => 'uid_param',
	              1 => 'uid_target_param',
	              2 => 'nid_target_param',
	              3 => 'message_id_param',
	              4 => 'variables_param',
	            ),
	            'module' => 'Heartbeat activity',
	          ),
	          '#name' => 'hb_activity_rules_default_action',
	          '#settings' => 
	          array (
	            'uid_param' => '[user:user-id]',
	            'uid_target_param' => '[node:author-uid]',
	            'nid_target_param' => '[node:nid]',
	            'message_id_param' => 'heartbeat_add_comment',
	            'variables_param' => '@username=|=[user:user-name-url]  -|-@title=|=[node:title-link]-|-',
	            '#eval input' => 
	            array (
	              'token_rules_input_evaluator' => 
	              array (
	                'uid_param' => 
	                array (
	                  0 => 'user',
	                ),
	                'uid_target_param' => 
	                array (
	                  0 => 'node',
	                ),
	                'nid_target_param' => 
	                array (
	                  0 => 'node',
	                ),
	                'variables_param' => 
	                array (
	                  0 => 'node',
	                  1 => 'user',
	                ),
	              ),
	            ),
	          ),
	          '#type' => 'action',
	        ),
	      ),
	    ),
	    
	    
	    'rules_heartbeat_3' => 
	    array (
	      '#type' => 'rule',
	      '#categories' => 
	      array (
	        0 => 'heartbeat',
	      ),
	      '#set' => 'event_comment_update',
	      '#label' => 'Heartbeat - user changes a reply (update comment)',
	      '#active' => 0,
	      '#weight' => '0',
	      '#status' => 'default',
	      '#conditions' => 
	      array (
	      ),
	      '#actions' => 
	      array (
	        0 => 
	        array (
	          '#weight' => 5,
	          '#info' => 
	          array (
	            'label' => 'Logs relational user activity',
	            'eval input' => 
	            array (
	              0 => 'uid_param',
	              1 => 'uid_target_param',
	              2 => 'nid_target_param',
	              3 => 'message_id_param',
	              4 => 'variables_param',
	            ),
	            'module' => 'Heartbeat activity',
	          ),
	          '#name' => 'hb_activity_rules_default_action',
	          '#settings' => 
	          array (
	            'uid_param' => '[user:user-id]',
	            'uid_target_param' => '[node:author-uid]',
	            'nid_target_param' => '[node:nid]',
	            'message_id_param' => 'heartbeat_edit_comment',
	            'variables_param' => '@username=|=[user:user-name-url]-|-@title=|=[node:title-link]-|-',
	            '#eval input' => 
	            array (
	              'token_rules_input_evaluator' => 
	              array (
	                'uid_param' => 
	                array (
	                  0 => 'user',
	                ),
	                'uid_target_param' => 
	                array (
	                  0 => 'node',
	                ),
	                'nid_target_param' => 
	                array (
	                  0 => 'node',
	                ),
	                'variables_param' => 
	                array (
	                  0 => 'node',
	                  1 => 'user',
	                ),
	              ),
	            ),
	          ),
	          '#type' => 'action',
	        ),
	      ),
	    ),
	    
      
      'rules_heartbeat_4' => 
      array (
        '#type' => 'rule',
        '#categories' => 
        array (
          0 => 'heartbeat',
        ),
        '#set' => 'event_user_update',
        '#label' => 'Heartbeat - After user updates his account',
        '#active' => 1,
        '#weight' => '0',
        '#status' => 'default',
        '#conditions' => 
        array (
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Logs default user activity',
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'nid_target_param',
                3 => 'message_id_param',
                4 => 'variables_param',
              ),
              'module' => 'heartbeat',
            ),
            '#name' => 'hb_activity_rules_default_action',
            '#settings' => 
            array (
              'uid_param' => '[user:user-id]',
              'uid_target_param' => '0',
              'nid_target_param' => '0',
              'message_id_param' => 'heartbeat_edit_account',
              'variables_param' => '@username=|=[account:user-name-url]-|-',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'uid_param' => 
                  array (
                    0 => 'user',
                  ),
                  'variables_param' => 
                  array (
                    0 => 'account',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
      ),
      
      
	    'rules_heartbeat_5' => 
	    array (
	      '#type' => 'rule',
	      '#set' => 'event_node_insert',
	      '#label' => 'Heartbeat - user adds new NOT page content',
	      '#active' => 1,
	      '#weight' => '0',
	      '#status' => 'custom',
	      '#conditions' => 
	      array (
	        0 => 
	        array (
	          '#type' => 'condition',
	          '#settings' => 
	          array (
	            '#argument map' => 
	            array (
	              'node' => 'node',
	            ),
	          ),
	          '#name' => 'rules_condition_content_is_published',
	          '#info' => 
	          array (
	            'label' => 'Created content is published',
	            'arguments' => 
	            array (
	              'node' => 
	              array (
	                'type' => 'node',
	                'label' => 'Content',
	              ),
	            ),
	            'module' => 'Node',
	          ),
	          '#weight' => 0,
	        ),
	        1 => 
	        array (
	          '#negate' => 1,
	          '#weight' => 0,
	          '#info' => 
	          array (
	            'label' => 'Content is not of the page type',
	            'label callback' => false,
	            'arguments' => 
	            array (
	              'node' => 
	              array (
	                'type' => 'node',
	                'label' => 'Content',
	              ),
	            ),
	            'module' => 'Node',
	          ),
	          '#name' => 'rules_condition_content_is_type',
	          '#settings' => 
	          array (
	            'type' => 
	            array (
	              'page' => 'page',
	            ),
	            '#argument map' => 
	            array (
	              'node' => 'node',
	            ),
	          ),
	          '#type' => 'condition',
	        ),
	      ),
        '#actions' => 
        array (
          0 => 
          array (
            '#type' => 'action',
            '#settings' => 
            array (
              'uid_param' => '[user:user-id]',
              'uid_target_param' => '0',
              'nid_target_param' => '[node:nid]',
              'message_id_param' => 'heartbeat_add_node',
              'variables_param' => '@username=|=[user:user-name-url]-|-@node_type=|=[node:type]-|-@node_title=|=[node:title-link]-|-',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'uid_param' => 
                  array (
                    0 => 'user',
                  ),
                  'nid_target_param' => 
                  array (
                    0 => 'node',
                  ),
                  'variables_param' => 
                  array (
                    0 => 'node',
                    1 => 'user',
                  ),
                ),
              ),
            ),
            '#name' => 'hb_activity_rules_default_action',
            '#info' => 
            array (
              'label' => 'Logs relational user activity',
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'nid_target_param',
                3 => 'message_id_param',
                4 => 'variables_param',
              ),
              'module' => 'Heartbeat activity',
            ),
            '#weight' => 10,
          ),
        ),
      ),
      
	    
	    'rules_heartbeat_flag_1' => 
	    array (
	      '#type' => 'rule',
	      '#categories' => 
	      array (
	        0 => 'heartbeat',
	      ),
	      '#set' => 'event_heartbeat_flag_post',
	      '#label' => 'Heartbeat -  User flags another user choosing one of the flagged messages',
	      '#active' => 0,
	      '#weight' => '0',
	      '#status' => 'default',
	      '#conditions' => 
	      array (
	      ),
	      '#actions' => 
	      array (
	        0 => 
	        array (
	          '#weight' => 0,
	          '#info' => 
	          array (
	            'label' => 'Logs relational user activity when flagging a user',
	            'eval input' => 
	            array (
	              0 => 'uid_param',
	              1 => 'uid_target_param',
	              2 => 'message_id_param',
	              3 => 'access_param',
	              4 => 'variables_param',
	            ),
	            'module' => 'heartbeat',
	          ),
	          '#name' => 'heartbeat_flag_rules_action',
	          '#settings' => 
	          array (
	            'uid_param' => '[user:user-id]',
	            'uid_target_param' => '[flagged_user:uid]',
	            'message_id_param' => '[message_id:message-id-raw]',
	            'access_param' => '[access:message-access]',
	            'variables_param' => '@username=|=[user:user-name-url]-|-@username_target=|=[flagged_user:user-name-url]-|-',
	            '#eval input' => 
	            array (
	              'token_rules_input_evaluator' => 
	              array (
	                'uid_param' => 
	                array (
	                  0 => 'user',
	                ),
	                'uid_target_param' => 
	                array (
	                  0 => 'flagged_user',
	                ),
	                'message_id_param' => 
	                array (
	                  0 => 'message_id',
	                ),
	                'access_param' => 
	                array (
	                  0 => 'access',
	                ),
	                'variables_param' => 
	                array (
	                  0 => 'user',
	                  1 => 'flagged_user',
	                ),
	              ),
	            ),
	          ),
	          '#type' => 'action',
	        ),
	      ),
	    ),
	    
	    
	    
	    'rules_heartbeat_shout_1' => 
	    array (
	      '#type' => 'rule',
	      '#categories' => 
	      array (
	        0 => 'heartbeat',
	      ),
	      '#set' => 'event_shout_post',
	      '#label' => 'Heartbeat -  After shouting, log shout message',
	      '#active' => 0,
	      '#weight' => '6',
	      '#status' => 'custom',
	      '#conditions' => 
	      array (
	      ),
	      '#actions' => 
	      array (
	        0 => 
	        array (
	          '#weight' => 0,
	          '#type' => 'action',
	          '#settings' => 
	          array (
	            'uid_param' => '[user:uid]',
	            'uid_target_param' => '0',
	            'nid_target_param' => '',
	            'message_id_param' => 'heartbeat_shout',
	            'variables_param' => '@user=|=[user:user-name-url]-|-@message=|=[shout:comment-body-raw]-|-',
	            '#eval input' => 
	            array (
	              'token_rules_input_evaluator' => 
	              array (
	                'uid_param' => 
	                array (
	                  0 => 'user',
	                ),
	                'variables_param' => 
	                array (
	                  0 => 'user',
	                  1 => 'shout',
	                ),
	              ),
	            ),
	          ),
	          '#name' => 'hb_activity_rules_default_action',
	          '#info' => 
	          array (
	            'label' => 'Logs relational user activity',
	            'eval input' => 
	            array (
	              0 => 'uid_param',
	              1 => 'uid_target_param',
	              2 => 'nid_target_param',
	              3 => 'message_id_param',
	              4 => 'variables_param',
	            ),
	            'module' => 'Heartbeat activity',
	          ),
	        ),
	      ),
	    ),
	  ),
	);
  
}