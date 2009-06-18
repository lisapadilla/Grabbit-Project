<?php
// $Id: friendlist_activity.rules_defaults.inc,v 1.1.2.4 2009/02/22 20:59:53 stalski Exp $

/**
 * @file
 * Rules' pre-configured rules.
 */

/**
 * Implementation of hook_rules_defaults();
 *
 * @return array rules structure
 */
function friendlist_activity_rules_defaults() {
	$rules = array (
	  'rules' => 
	  array (
	  
	
	    'rule_heartbeat_friendlist_add' =>
	    array(
	      '#type' => 'rule',
	      '#set' => 'event_friendlist_add',
	      '#label' => 'Heartbeat - users added relation to another user',
	      '#active' => 1,
	      '#weight' => '-1',
	      '#status' => 'default',
	      '#conditions' =>
	      array(
	        0 =>
	        array(
	          '#weight' => 0,
	          0 =>
	          array(
	            '#type' => 'condition',
	            '#name' => 'rules_condition_relation_status_compare',
	            '#info' =>
	            array(
	              'label' => 'Adding user from OW_NONE',
	              'label callback' => FALSE,
	              'arguments' =>
	              array(
	                'relation_status' =>
	                array(
	                  'label' => 'Relation status',
	                  'type' => 'relation_status',
	                  'description' => 'The relation to compare',
	                ),
	              ),
	              'help' => 'TRUE is returned if the relation status equals the string in the input box',
	              'module' => 'Friendlist Rules',
	            ),
	            '#settings' =>
	            array(
	              'status_param' => 'OW_NONE',
	              '#argument map' =>
	              array(
	                'status_pre' => 'relation_status',
	              ),
	            ),
	            '#weight' => 0,
	          ),
	          '#type' => 'OR',
	          1 =>
	          array(
	            '#weight' => 0,
	            '#info' =>
	            array(
	              'label' => 'Adding user from OW_2_TO_1',
	              'label callback' => FALSE,
	              'arguments' =>
	              array(
	                'relation_status' =>
	                array(
	                  'label' => 'Relation status',
	                  'type' => 'relation_status',
	                  'description' => 'The relation to compare',
	                ),
	              ),
	              'help' => 'TRUE is returned if the relation status equals the string in the input box',
	              'module' => 'Friendlist Rules',
	            ),
	            '#name' => 'rules_condition_relation_status_compare',
	            '#settings' =>
	            array(
	              'status_param' => 'OW_2_TO_1',
	              '#argument map' =>
	              array(
	                'status_pre' => 'relation_status',
	              ),
	            ),
	            '#type' => 'condition',
	          ),
	        ),
	      ),
	      '#actions'  => 
	        array (
	          0 => 
	          array (
	            '#weight' => 0,
	            '#info' => 
	            array (
	              'label' => 'Logs relational user activity 1->2',
	              'label callback' => false,
	              'eval input' => 
	              array (
	                0 => 'uid_param',
	                1 => 'uid_target_param',
	                2 => 'message_id_param',
	                3 => 'variables_param',
	              ),
	              'module' => 'Friendlist Rules',
	            ),
	            '#name' => 'hb_activity_rules_users_action',
	            '#settings' => 
	            array (
	              'uid_param' => '[user1:uid]',
	              'uid_target_param' => '[user2:uid]',
	              'message_id_param' => 'heartbeat_become_friends',
	              'variables_param' => '@user1=|=[user1:user-name-url]-|-#relation_type=|=[rtid:name_p]-|-@user2=|=[user2:user-name-url]-|-',
	              '#eval input' => 
	              array (
	                'token_rules_input_evaluator' => 
	                array (
	                  'uid_param' => 
	                  array (
	                    0 => 'user1',
	                  ),
	                  'uid_target_param' => 
	                  array (
	                    0 => 'user2',
	                  ),
	                  'variables_param' => 
	                  array (
	                    0 => 'user1',
	                    1 => 'user2',
	                    2 => 'rtid',
	                  ),
	                ),
	              ),
	            ),
	            '#type' => 'action',
	          ),
          ),
	    ),
	  
	  
		  
	    'rule_heartbeat_friendlist_accepted' =>
	    array(
	      '#type' => 'rule',
	      '#set' => 'event_friendlist_add',
	      '#label' => 'Heartbeat - users accepted relation with another user',
	      '#active' => 1,
	      '#weight' => '3',
	      '#status' => 'default',
	      '#conditions' =>
	      array(
	        1 =>
	        array(
	          '#weight' => 0,
	          '#settings' =>
	          array(
	            'status_param' => 'TW_BOTH',
	            '#argument map' =>
	            array(
	              'status_post' => 'relation_status',
	            ),
	          ),
	          '#info' =>
	          array(
	            'label' => 'Request has been accepted',
	            'label callback' => FALSE,
	            'arguments' =>
	            array(
	              'relation_status' =>
	              array(
	                'label' => 'Relation status',
	                'type' => 'relation_status',
	                'description' => 'The relation to compare',
	              ),
	            ),
	            'help' => 'TRUE is returned if the relation status equals the string in the input box',
	            'module' => 'Friendlist Rules',
	          ),
	          '#name' => 'rules_condition_relation_status_compare',
	          '#type' => 'condition',
	        ),
	      ),
	      '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Logs relational user activity 1->2',
              'label callback' => false,
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'message_id_param',
                3 => 'variables_param',
              ),
              'module' => 'Friendlist Rules',
            ),
            '#name' => 'hb_activity_rules_users_action',
            '#settings' => 
            array (
              'uid_param' => '[user1:uid]',
              'uid_target_param' => '[user2:uid]',
              'message_id_param' => 'heartbeat_become_friends',
              'variables_param' => '@user1=|=[user1:user-name-url]-|-#relation_type=|=[rtid:name_p]-|-@user2=|=[user2:user-name-url]-|-',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'uid_param' => 
                  array (
                    0 => 'user1',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'user2',
                  ),
                  'variables_param' => 
                  array (
                    0 => 'user1',
                    1 => 'user2',
                    2 => 'rtid',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
          1 => 
          array (
            '#type' => 'action',
            '#settings' => 
            array (
              'uid_param' => '[user2:uid]',
              'uid_target_param' => '[user1:uid]',
              'message_id_param' => 'heartbeat_become_friends',
              'variables_param' => '@user1=|=[user2:user-name-url]-|-#relation_type=|=[rtid:name]-|-@user2=|=[user1:user-name-url]-|-',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'uid_param' => 
                  array (
                    0 => 'user2',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'user1',
                  ),
                  'variables_param' => 
                  array (
                    0 => 'user1',
                    1 => 'user2',
                    2 => 'rtid',
                  ),
                ),
              ),
            ),
            '#name' => 'hb_activity_rules_users_action',
            '#info' => 
            array (
              'label' => 'Logs relational user activity 2->1',
              'label callback' => false,
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'message_id_param',
                3 => 'variables_param',
              ),
              'module' => 'Friendlist Rules',
            ),
            '#weight' => 3,
          ),
        ),
	    ),
    
    
	    /*
      'rule_heartbeat_friendlist' => 
      array (
        '#type' => 'rule',
        '#categories' => 
        array (
          0 => 'heartbeat',
        ),
        '#set' => 'event_friendlist_add',
        '#label' => 'Heartbeat - users become relation type friend with another user',
        '#active' => 1,
        '#weight' => '0',
        '#status' => 'altered',
        '#conditions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#type' => 'condition',
            '#settings' => 
            array (
              'status_param' => 'TW_BOTH',
              '#argument map' => 
              array (
                'status_post' => 'relation_status',
              ),
            ),
            '#name' => 'rules_condition_relation_status_compare',
            '#info' => 
            array (
              'label' => 'after adding , relation is established',
              'label callback' => false,
              'arguments' => 
              array (
                'relation_status' => 
                array (
                  'label' => 'Relation status',
                  'type' => 'relation_status',
                  'description' => 'The relation to compare',
                ),
              ),
              'module' => 'Friendlist Rules',
            ),
          ),
        ),
        '#actions' => 
        array (
          0 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Logs relational user activity 1->2',
              'label callback' => false,
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'message_id_param',
                3 => 'variables_param',
              ),
              'module' => 'Friendlist Rules',
            ),
            '#name' => 'hb_activity_rules_users_action',
            '#settings' => 
            array (
              'uid_param' => '[user1:uid]',
              'uid_target_param' => '[user2:uid]',
              'message_id_param' => 'heartbeat_become_friends',
              'variables_param' => '@user1=|=[user1:user-name-url]-|-#relation_type=|=[rtid:name_p]-|-@user2=|=[user2:user-name-url]-|-',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'uid_param' => 
                  array (
                    0 => 'user1',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'user2',
                  ),
                  'variables_param' => 
                  array (
                    0 => 'user1',
                    1 => 'user2',
                    2 => 'rtid',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
          1 => 
          array (
            '#type' => 'action',
            '#settings' => 
            array (
              'uid_param' => '[user2:uid]',
              'uid_target_param' => '[user1:uid]',
              'message_id_param' => 'heartbeat_become_friends',
              'variables_param' => '@user1=|=[user2:user-name-url]-|-#relation_type=|=[rtid:name]-|-@user2=|=[user1:user-name-url]-|-',
              '#eval input' => 
              array (
                'token_rules_input_evaluator' => 
                array (
                  'uid_param' => 
                  array (
                    0 => 'user2',
                  ),
                  'uid_target_param' => 
                  array (
                    0 => 'user1',
                  ),
                  'variables_param' => 
                  array (
                    0 => 'user1',
                    1 => 'user2',
                    2 => 'rtid',
                  ),
                ),
              ),
            ),
            '#name' => 'hb_activity_rules_users_action',
            '#info' => 
            array (
              'label' => 'Logs relational user activity 2->1',
              'label callback' => false,
              'eval input' => 
              array (
                0 => 'uid_param',
                1 => 'uid_target_param',
                2 => 'message_id_param',
                3 => 'variables_param',
              ),
              'module' => 'Friendlist Rules',
            ),
            '#weight' => 3,
          ),
        ),
      ),*/
	  
	  
	  ),
	);
  return $rules;  
}