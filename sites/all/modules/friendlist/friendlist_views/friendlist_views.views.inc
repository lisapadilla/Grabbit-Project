<?php
// $Id: friendlist_views.views.inc,v 1.1.2.11 2009/01/17 11:13:54 mariusooms Exp $

/**
 * @file
 * Friendlist's Views integration.
 */

/*
RESOURCES:

http://www.garfieldtech.com/blog/drupal-handler-rfc
This is a general description of "handlers". Not specific to Views.

http://blue.live4all.co.il/~mooffie/tmp/views_illustrated/
This is a collection of notes I wrote. I have more stuff I'm planning to put there. But please don't distribute the link: it's a temporary address.

http://views.doc.logrus.com/
There's the inline documentation.

http://groups.drupal.org/views-developers
Ask for advice here as well.
 */

function friendlist_views_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'friendlist_views'),
      ),
    'handlers' => array(

      'views_handler_field_friendlist_link' => array(
        'parent' => 'views_handler_field',
      ),

      'views_handler_field_friendlist_link_requester' => array(
        'parent' => 'views_handler_field_friendlist_link',
      ),

      'views_handler_field_friendlist_link_requestee' => array(
        'parent' => 'views_handler_field_friendlist_link',
      ),

      'views_handler_filter_relationship_type' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),

      'views_handler_filter_status' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),

    ),
  );


}

function friendlist_views_views_data() {

  $data = array(

    'friendlist_relations' => array(

      'table' => array(
        'group' => t('Relations'),

        'join' => array(
          'friendlist_statuses' => array(
            'left_field' => 'rid_origin',
            'field' => 'rid',
          ),
          'node' => array(
            'left_field' => 'uid',
            'field' => 'requestee_id',
          ),
        ),

        'base'  => array(
          'field' => 'rid',
          'title' => t('Relations between users'),
          'help'  => t("Relations between users in the system. They can be one-way or two ways"),
        ),
      ),


      'requester_id' => array(
        'title' => t('Requesting user'),
        'help' => t('The user who made the request'),
        'relationship' => array(
          'base' => 'users',
          'field' => 'uid',
          'handler' => 'views_handler_relationship',
          'label' => t('Requester'),
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_user_current',
        ),
      ),

      'requestee_id' => array(
        'title' => t('Requestee user'),
        'help' => t('The user who received the request'),
        'relationship' => array(
          'base' => 'users',
          'field' => 'uid',
          'handler' => 'views_handler_relationship',
          'label' => t('Requestee'),
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_user_current',
        ),

      ),

      'rtid' => array(
        'title' => t('The relation type ID'),
        'help' => t('The relation type ID you want to filter by. You can view the ID in the administration interface'),
        'filter' => array(
          'handler' => 'views_handler_filter_relationship_type',
        ),
      ),

      'message' => array(
        'title' => t('Message sent'),
        'help' => t('Message sent by the requesting user'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
      ),

      'create_time' => array(
        'title' => t('Date of the request'),
        'help' => t('When the friendship request was sent'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
      ),

      'tw_disregarded_time' => array(
        'title' => t('When the two-way relationship was disregarded'),
        'help' => t('When the relaton request (a two-way one) was denied'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_boolean_operator',
        ),
      ),

      'requestee_id_current' => array(
        'real field' => 'requestee_id',
        'title' => t('Requestee user is the currently logged in user'),
        'help' => t('Filter results so that only the current user is the requestee'),
        'filter' => array(
          'handler' => 'views_handler_filter_user_current',
        ),
      ),

      'requester_id_current' => array(
        'real field' => 'requester_id',
        'title' => t('Requester user is the currently logged in user'),
        'help' => t('Filter results so that only the current user is the requester'),
        'filter' => array(
          'handler' => 'views_handler_filter_user_current',
        ),
      ),

      'rid' => array(
        'title' => t('The relation ID'),
        'help' => t('This is only here to make sure that Views works'),
      ),

      'action_link_requester' => array(
        'field' => array(
          'title' => t('Action from logged in user to requester'),
          'help' => t('Links to act on the relationship with the user'),
          'handler' => 'views_handler_field_friendlist_link_requester',
        ),
      ),

      'action_link_requestee' => array(
        'field' => array(
          'title' => t('Action from logged in user to requestee'),
          'help' => t('Links to act on the relationship with the user'),
          'handler' => 'views_handler_field_friendlist_link_requestee',
        ),
      ),
    ),


    'friendlist_relation_types' => array(
      'table' => array(
        'group' => t('Relationship types'),

        /* No need to have this as a base, it will just confuse me and users
          'base' => array(
          'field' => 'rtid',
          'title' => t('Relation type'),
          'help' => t('A type of relation in FriendList'),
          'weight' => -10,
        ),*/

        'join' => array(
          'friendlist_relations' => array(
            'left_field' => 'rtid',
            'field' => 'rtid',
          ),
        ),
      ),


      'rtid' => array(
        'title' => t('Relation type ID'),
        'help' => t('The Relation type ID'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
      ),

      'name' => array(
        'title' => t('Name of the relation type'),
        'help' => t('Name of the relation type'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
      ),
      'name_p' => array(
        'title' => t('Plural form of the relation type'),
        'help' => t('Plural form of the relation type'),
        'field' => array(
          'handler' => 'views_handler_field',
          'click sortable' => TRUE,
        ),
      ),

      'oneway' => array(
        'title' => t('One way relation type'),
        'help' => t('Relation types that do not require confirmation'),
        'field' => array(
         'handler' => 'views_handler_field_boolean',
         'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_boolean_operator',
          'label' => t('One way'),
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),

      'active' => array(
        'title' => t('Active'),
        'help' => t('Active relation types'),
        'field' => array(
         'handler' => 'views_handler_field_boolean',
         'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_boolean_operator',
          'label' => t('One way'),
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
        ),
      ),
    ),

    'friendlist_statuses' => array(
      'table' => array(

        'base' => array(
          'field' => 'sid',
          'title' => t('Relation status'),
          'help' => t('Relation status between two users'),
          'weight' => -10,
        ),

        'group' => t('Statuses'),

        'join' => array(
          'friendlist_relations' => array(
            'left_field' => 'rid',
            'field' => 'rid', // MERC: friendlist_status' field
            'type' => 'INNER',
          ),

          // This is mercmobily testing with activity_log
          /*'activity_log' => array(
            'left_field' => 'uid',
            'field' => 'requester_id',
          ),*/

        ),
      ),

      'status' => array(
        'title' => t('Status'),
        'help' => t('The relation status'),
        'field' => array(
         'handler' => 'views_handler_field',
         'click sortable' => FALSE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_status',
          'label' => t('Status'),
        ),
      ),

      'requester_id' => array(
        'title' => t('Requesting user'),
        'help' => t('The user who made the request'),
        'relationship' => array(
          'base' => 'users',
          'field' => 'uid',
          'handler' => 'views_handler_relationship',
          'label' => t('Requester'),
        ),

        'filter' => array(
          'handler' => 'views_handler_filter_user_current',
          'label' => t('Status'),
        ),
      ),

      'requestee_id' => array(
        'title' => t('Requestee user'),
        'help' => t('The user who received the request'),
        'relationship' => array(
          'base' => 'users',
          'field' => 'uid',
          'handler' => 'views_handler_relationship',
          'label' => t('Requestee'),
        ),

        'filter' => array(
          'handler' => 'views_handler_filter_user_current',
          'label' => t('Status'),
        ),
      ),
      'last_update_time' => array(
        'title' => t('Date the status was set'),
        'help' => t('When the status was set'),
        'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
        ),
      ),

    ),
  );

  return $data;

}

