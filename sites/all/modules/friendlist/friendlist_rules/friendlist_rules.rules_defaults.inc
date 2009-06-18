<?php
// $Id: friendlist_rules.rules_defaults.inc,v 1.1.2.12 2009/01/13 12:05:51 mercmobily Exp $

/**
 * @file
 * Rules' pre-configured rules.
 */

// See: http://drupal.org/node/298634

function friendlist_rules_rules_defaults() {

  $config =

array (
  'rules' => 
  array (
    'rules_1' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_add',
      '#label' => 'Friendlist - Notify requester: Request send',
      '#active' => 1,
      '#weight' => '1',
      '#status' => 'default',
      '#conditions' => 
      array (
        1 => 
        array (
          '#type' => 'condition',
          '#name' => 'rules_condition_relation_status_compare',
          '#info' => 
          array (
            'label' => 'Request has been send, but not confirmed',
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
            'help' => 'TRUE is returned if the relation status equals the string in the input box',
            'module' => 'Friendlist Rules',
          ),
          '#settings' => 
          array (
            'status_param' => 'TW_NONE',
            '#argument map' => 
            array (
              'status_pre' => 'relation_status',
            ),
          ),
          '#weight' => 0,
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#settings' => 
          array (
            'from' => '',
            'subject' => 'You have requested [user2:user] to be your [rtid:name]',
            'message' => 'You have requested [user2:user] to be your [rtid:name]. Visit the following link to view all send out requests: [user1:site-url]/connections/send',
            '#argument map' => 
            array (
              'user1' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user2',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user1',
                  1 => 'user2',
                  2 => 'rtid',
                ),
              ),
            ),
          ),
          '#info' => 
          array (
            'label' => 'Send notification to requester',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#name' => 'rules_action_mail_to_user',
          '#type' => 'action',
        ),
      ),
    ),
    'rules_11' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_delete',
      '#label' => 'Friendlist - Notify requester: Request cancelled',
      '#active' => 1,
      '#weight' => '5',
      '#status' => 'default',
      '#conditions' => 
      array (
        2 => 
        array (
          '#weight' => 0,
          '#settings' => 
          array (
            'status_param' => 'TW_NONE',
            '#argument map' => 
            array (
              'status_post' => 'relation_status',
            ),
          ),
          '#info' => 
          array (
            'label' => 'Request has been canceled',
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
          '#type' => 'action',
          '#name' => 'rules_action_mail_to_user',
          '#info' => 
          array (
            'label' => 'Send notification to requester',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#settings' => 
          array (
            'from' => '',
            'subject' => 'You have cancelled your [rtid:name] request with [user2:user]',
            'message' => 'You have cancelled your [rtid:name] request with [user2:user]. Visit the following link to manage your other [rtid:name] requests, if any: [user1:site-url]/connections/send',
            '#argument map' => 
            array (
              'user1' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user2',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user1',
                  1 => 'user2',
                  2 => 'rtid',
                ),
              ),
            ),
          ),
        ),
      ),
    ),
    'rules_12' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_delete',
      '#label' => 'Friendlist - Notify requestee: Request cancelled',
      '#active' => 1,
      '#weight' => '6',
      '#status' => 'default',
      '#conditions' => 
      array (
        2 => 
        array (
          '#weight' => 0,
          '#settings' => 
          array (
            'status_param' => 'TW_NONE',
            '#argument map' => 
            array (
              'status_post' => 'relation_status',
            ),
          ),
          '#info' => 
          array (
            'label' => 'Request has been cancelled',
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
            'help' => 'TRUE is returned if the relation status equals the string in the input box',
            'module' => 'Friendlist Rules',
          ),
          '#type' => 'condition',
          '#name' => 'rules_condition_relation_status_compare',
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#type' => 'action',
          '#name' => 'rules_action_mail_to_user',
          '#info' => 
          array (
            'label' => 'Send notification to requestee',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#settings' => 
          array (
            'from' => '',
            'subject' => '[user1:user] has cancelled their [rtid:name] request with you',
            'message' => '[user1:user] has cancelled their [rtid:name] request with you. Visit the following link to view [user1:user]\'s profile: [user1:site-url]/user/[user1:uid]',
            '#argument map' => 
            array (
              'user2' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
              ),
            ),
          ),
        ),
      ),
    ),
    'rules_13' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_add',
      '#label' => 'Friendlist - Notify recipient: Now added',
      '#active' => 1,
      '#weight' => '-1',
      '#status' => 'default',
      '#conditions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          0 => 
          array (
            '#type' => 'condition',
            '#name' => 'rules_condition_relation_status_compare',
            '#info' => 
            array (
              'label' => 'Adding user from OW_NONE',
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
              'help' => 'TRUE is returned if the relation status equals the string in the input box',
              'module' => 'Friendlist Rules',
            ),
            '#settings' => 
            array (
              'status_param' => 'OW_NONE',
              '#argument map' => 
              array (
                'status_pre' => 'relation_status',
              ),
            ),
            '#weight' => 0,
          ),
          '#type' => 'OR',
          1 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Adding user from OW_2_TO_1',
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
              'help' => 'TRUE is returned if the relation status equals the string in the input box',
              'module' => 'Friendlist Rules',
            ),
            '#name' => 'rules_condition_relation_status_compare',
            '#settings' => 
            array (
              'status_param' => 'OW_2_TO_1',
              '#argument map' => 
              array (
                'status_pre' => 'relation_status',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#settings' => 
          array (
            'from' => '',
            'subject' => '[user1:user] is now your [rtid:name]',
            'message' => '[user1:user] is now your [rtid:name]. Visit the following link to view [user1:user]\'s profile: [user1:site-url]/user/[user1:uid]',
            '#argument map' => 
            array (
              'user2' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
              ),
            ),
          ),
          '#info' => 
          array (
            'label' => 'Send notification to added user',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#name' => 'rules_action_mail_to_user',
          '#type' => 'action',
        ),
      ),
    ),
    'rules_14' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_delete',
      '#label' => 'Friendlist - Notify initiator: Remove',
      '#active' => 1,
      '#weight' => '0',
      '#status' => 'default',
      '#conditions' => 
      array (
        1 => 
        array (
          0 => 
          array (
            '#name' => 'rules_condition_relation_status_compare',
            '#type' => 'condition',
            '#info' => 
            array (
              'label' => 'Stop following fan to OW_NONE',
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
              'help' => 'TRUE is returned if the relation status equals the string in the input box',
              'module' => 'Friendlist Rules',
            ),
            '#settings' => 
            array (
              'status_param' => 'OW_NONE',
              '#argument map' => 
              array (
                'status_post' => 'relation_status',
              ),
            ),
            '#weight' => 0,
          ),
          '#type' => 'OR',
          '#weight' => 0,
          1 => 
          array (
            '#weight' => 0,
            '#info' => 
            array (
              'label' => 'Stop following fan to OW_2_TO_1',
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
              'help' => 'TRUE is returned if the relation status equals the string in the input box',
              'module' => 'Friendlist Rules',
            ),
            '#name' => 'rules_condition_relation_status_compare',
            '#settings' => 
            array (
              'status_param' => 'OW_2_TO_1',
              '#argument map' => 
              array (
                'status_post' => 'relation_status',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#settings' => 
          array (
            'from' => '',
            'subject' => 'You are no longer a [rtid:name] of [user2:user]',
            'message' => 'You are no longer a [rtid:name] of [user2:user]. Visit the following link to view [user2:user]\'s profile: [user2:site-url]/user/[user2:uid]',
            '#argument map' => 
            array (
              'user1' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user2',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user2',
                  1 => 'rtid',
                ),
              ),
            ),
          ),
          '#info' => 
          array (
            'label' => 'Send notification to follower',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#name' => 'rules_action_mail_to_user',
          '#type' => 'action',
        ),
      ),
    ),
    'rules_2' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_add',
      '#label' => 'Friendlist - Notify requestee: Request send',
      '#active' => 1,
      '#weight' => '1',
      '#status' => 'default',
      '#conditions' => 
      array (
        1 => 
        array (
          '#weight' => 0,
          '#settings' => 
          array (
            'status_param' => 'TW_NONE',
            '#argument map' => 
            array (
              'status_pre' => 'relation_status',
            ),
          ),
          '#info' => 
          array (
            'label' => 'Request has been send, but not confirmed',
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
          '#type' => 'action',
          '#name' => 'rules_action_mail_to_user',
          '#info' => 
          array (
            'label' => 'Send notification to requestee',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#settings' => 
          array (
            'from' => '',
            'subject' => '[user1:user] added you as a [rtid:name]',
            'message' => '[user1:user] added you as a [rtid:name]. Visit the following link to respond to this request:
[user1:site-url]/connections/received',
            '#argument map' => 
            array (
              'user2' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
              ),
            ),
          ),
        ),
      ),
    ),
    'rules_3' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_add',
      '#label' => 'Friendlist - Notify requester: Request accepted',
      '#active' => 1,
      '#weight' => '3',
      '#status' => 'default',
      '#conditions' => 
      array (
        1 => 
        array (
          '#type' => 'condition',
          '#name' => 'rules_condition_relation_status_compare',
          '#info' => 
          array (
            'label' => 'Request has been accepted',
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
            'help' => 'TRUE is returned if the relation status equals the string in the input box',
            'module' => 'Friendlist Rules',
          ),
          '#settings' => 
          array (
            'status_param' => 'TW_BOTH',
            '#argument map' => 
            array (
              'status_post' => 'relation_status',
            ),
          ),
          '#weight' => 0,
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#settings' => 
          array (
            'from' => '',
            'subject' => '[user1:user] has accepted your [rtid:name] request',
            'message' => '[user1:user] has accepted your [rtid:name] request. You and [user1:user] are now [rtid:name_p]. Visit the following link to manage your [rtid:name_p]: [user2:site-url]/connections/manage/twoway',
            '#argument map' => 
            array (
              'user2' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user1',
                  1 => 'user2',
                  2 => 'rtid',
                ),
              ),
            ),
          ),
          '#info' => 
          array (
            'label' => 'Send notification to requester',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#name' => 'rules_action_mail_to_user',
          '#type' => 'action',
        ),
      ),
    ),
    'rules_4' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_add',
      '#label' => 'Friendlist - Notify requestee: Request accepted',
      '#active' => 1,
      '#weight' => '4',
      '#status' => 'default',
      '#conditions' => 
      array (
        1 => 
        array (
          '#settings' => 
          array (
            'status_param' => 'TW_BOTH',
            '#argument map' => 
            array (
              'status_post' => 'relation_status',
            ),
          ),
          '#info' => 
          array (
            'label' => 'Request has been accepted',
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
            'help' => 'TRUE is returned if the relation status equals the string in the input box',
            'module' => 'Friendlist Rules',
          ),
          '#name' => 'rules_condition_relation_status_compare',
          '#type' => 'condition',
          '#weight' => 0,
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#type' => 'action',
          '#name' => 'rules_action_mail_to_user',
          '#info' => 
          array (
            'label' => 'Send notification to requestee',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#settings' => 
          array (
            'from' => '',
            'subject' => 'You have accepted [user2:user] as a [rtid:name]',
            'message' => 'You have accepted [user2:user] as a [rtid:name]. You and [user2:user] are now [rtid:name_p]. Visit the following link to manage your [rtid:name_p]: [user1:site-url]/connections/manage/twoway',
            '#argument map' => 
            array (
              'user1' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user2',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user1',
                  1 => 'user2',
                  2 => 'rtid',
                ),
              ),
            ),
          ),
        ),
      ),
    ),
    'rules_10' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_delete',
      '#label' => 'Friendlist - Notify requestee: Relation deleted',
      '#active' => 1,
      '#weight' => '10',
      '#status' => 'default',
      '#conditions' => 
      array (
        1 => 
        array (
          '#weight' => 0,
          '#settings' => 
          array (
            'status_param' => 'TW_BOTH',
            '#argument map' => 
            array (
              'status_pre' => 'relation_status',
            ),
          ),
          '#info' => 
          array (
            'label' => 'Relation is mutual',
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
          '#type' => 'action',
          '#name' => 'rules_action_mail_to_user',
          '#info' => 
          array (
            'label' => 'Send notification to requestee',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#settings' => 
          array (
            'from' => '',
            'subject' => '[user1:user] has removed you from the [rtid:name_p] list',
            'message' => '[user1:user] has removed you from the [rtid:name_p] list. You can no longer become [rtid:name_p] with [rtid:name], unless requested.',
            '#argument map' => 
            array (
              'user2' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
              ),
            ),
          ),
        ),
      ),
    ),
    'rules_5' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_delete',
      '#label' => 'Friendlist - Notify requester: Request declined',
      '#active' => 1,
      '#weight' => '7',
      '#status' => 'default',
      '#conditions' => 
      array (
        0 => 
        array (
          '#weight' => 0,
          '#type' => 'condition',
          '#name' => 'rules_condition_relation_status_compare',
          '#info' => 
          array (
            'label' => 'Request has been declined',
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
            'help' => 'TRUE is returned if the relation status equals the string in the input box',
            'module' => 'Friendlist Rules',
          ),
          '#settings' => 
          array (
            'status_param' => 'TW_2_TO_1_D',
            '#argument map' => 
            array (
              'status_post' => 'relation_status',
            ),
          ),
        ),
        1 => 
        array (
          '#info' => 
          array (
            'label' => 'Relation is not mutual',
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
            'help' => 'TRUE is returned if the relation status equals the string in the input box',
            'module' => 'Friendlist Rules',
          ),
          '#weight' => 0,
          '#settings' => 
          array (
            'status_param' => 'TW_BOTH',
            '#argument map' => 
            array (
              'status_pre' => 'relation_status',
            ),
          ),
          '#name' => 'rules_condition_relation_status_compare',
          '#type' => 'condition',
          '#negate' => 1,
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#settings' => 
          array (
            'from' => '',
            'subject' => '[user1:user] has declined your [rtid:name] request',
            'message' => '[user1:user] has declined your [rtid:name] request. You and [user1:user] are not [rtid:name_p]. On top of that, you will not be able to send further [rtid:name] requests.',
            '#argument map' => 
            array (
              'user2' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user1',
                  1 => 'rtid',
                ),
              ),
            ),
          ),
          '#info' => 
          array (
            'label' => 'Send notification to requester',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#name' => 'rules_action_mail_to_user',
          '#type' => 'action',
          '#weight' => 0,
        ),
      ),
    ),
    'rules_6' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_delete',
      '#label' => 'Friendlist - Notify requestee: Request declined',
      '#active' => 1,
      '#weight' => '8',
      '#status' => 'default',
      '#conditions' => 
      array (
        2 => 
        array (
          '#name' => 'rules_condition_relation_status_compare',
          '#type' => 'condition',
          '#info' => 
          array (
            'label' => 'Request has been declined',
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
            'help' => 'TRUE is returned if the relation status equals the string in the input box',
            'module' => 'Friendlist Rules',
          ),
          '#settings' => 
          array (
            'status_param' => 'TW_2_TO_1_D',
            '#argument map' => 
            array (
              'status_post' => 'relation_status',
            ),
          ),
          '#weight' => -1,
        ),
        1 => 
        array (
          '#negate' => 1,
          '#weight' => 0,
          '#type' => 'condition',
          '#name' => 'rules_condition_relation_status_compare',
          '#settings' => 
          array (
            'status_param' => 'TW_BOTH',
            '#argument map' => 
            array (
              'status_pre' => 'relation_status',
            ),
          ),
          '#info' => 
          array (
            'label' => 'Relation is not mutual',
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
            'help' => 'TRUE is returned if the relation status equals the string in the input box',
            'module' => 'Friendlist Rules',
          ),
        ),
      ),
      '#actions' => 
      array (
        0 => 
        array (
          '#settings' => 
          array (
            'from' => '',
            'subject' => 'You have declined [user2:user] as a [rtid:name]',
            'message' => 'You have declined [user2:user] as a [rtid:name]. You and [user2:user] are not [rtid:name_p]. On top of that, [user2:user] will not be able to send further [rtid:name] requests to you.',
            '#argument map' => 
            array (
              'user1' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user2',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user2',
                  1 => 'rtid',
                ),
              ),
            ),
          ),
          '#info' => 
          array (
            'label' => 'Send notification to requestee',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#name' => 'rules_action_mail_to_user',
          '#type' => 'action',
          '#weight' => 0,
        ),
      ),
    ),
    'rules_9' => 
    array (
      '#type' => 'rule',
      '#set' => 'event_friendlist_delete',
      '#label' => 'Friendlist - Notify requester: Relation deleted',
      '#active' => 1,
      '#weight' => '9',
      '#status' => 'default',
      '#conditions' => 
      array (
        1 => 
        array (
          '#weight' => 0,
          '#settings' => 
          array (
            'status_param' => 'TW_BOTH',
            '#argument map' => 
            array (
              'status_pre' => 'relation_status',
            ),
          ),
          '#info' => 
          array (
            'label' => 'Relation is mutual',
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
          '#type' => 'action',
          '#name' => 'rules_action_mail_to_user',
          '#info' => 
          array (
            'label' => 'Send notification to requester',
            'label callback' => false,
            'arguments' => 
            array (
              'user' => 
              array (
                'type' => 'user',
                'label' => 'Recipient',
              ),
            ),
            'module' => 'System',
            'eval input' => 
            array (
              0 => 'subject',
              1 => 'message',
              2 => 'from',
            ),
          ),
          '#settings' => 
          array (
            'from' => '',
            'subject' => 'You have removed [user2:user] from your [rtid:name_p] list',
            'message' => 'You have removed [user2:user] from your [rtid:name_p] list. [user2:user] can no longer become your friend, unless you send a request.',
            '#argument map' => 
            array (
              'user1' => 'user',
            ),
            '#eval input' => 
            array (
              'token_rules_input_evaluator' => 
              array (
                'subject' => 
                array (
                  0 => 'user2',
                  1 => 'rtid',
                ),
                'message' => 
                array (
                  0 => 'user2',
                  1 => 'rtid',
                ),
              ),
            ),
          ),
          '#weight' => 0,
        ),
      ),
    ),
  ),
);

  return $config;
}
