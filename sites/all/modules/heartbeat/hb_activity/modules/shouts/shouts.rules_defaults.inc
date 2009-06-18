<?php
// $Id $

/**
 * Implementation of hook_rules_defaults
 *
 * @return configured rules array
 */
function shouts_rules_defaults() {   
	return array (
	  'rules' => 
	  array (
	    'rules_17' => 
	    array (
	      '#type' => 'rule',
        '#categories' => array('heartbeat'),
	      '#set' => 'event_shout_post',
	      '#label' => 'heartbeat: After shouting, log shout message',
	      '#active' => 1,
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
	            'module' => 'User activity',
	          ),
	        ),
	      ),
	    ),
	  ),
	);
}