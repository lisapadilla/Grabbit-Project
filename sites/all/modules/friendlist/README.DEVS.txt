FRIENDLIST
==========

[Still incomplete]

This is what I consider to be the most powerful API to manage user relations.
It's concise, and (more importantly) to the point.

Even as a developer, please read the file README.txt which contains some
basic information about the database structure that you need to know to
follow this document without any trouble.


Function summary
----------------

  Relation types
  --------------

  friendlist_api_relation_type_add($name, $name_plural, $oneway, $active)
  - Adds a relation type

  friendlist_api_relation_type_load($rt)
  - Returns the relation type information

  friendlist_api_relation_types_load_all()
  - Returns _all_ of the relation type objects in an array of objects

  friendlist_api_relation_type_edit($rtid, $name, $name_plural, $oneway, $active)
  - Changes the relation type $rtid according to the passed parameters

  friendlist_api_relation_type_delete($rtid)
  - Deletes the relation type with id $rtid


  Relations
  --------------

    friendlist_api_relation_add($requester, $requestee, $rtid, $message, $user_generated=TRUE)
    - Adds a relation of type $rtid between $requester and $requestee, with
      message $message. If $user_generated is FALSE, the function won't
      generate Rules event. If there is a "denial" for a relation from
      $requestee to $requester, the disregarded flag is taken off.

    friendlist_api_relation_delete($requester, $requestee, $rtid, $message, $user_generated=TRUE)
    - Deletes a relation of type $rtid between $requester and $requestee, with
      message $message. If $user_generated is FALSE, the function won't
      generate Rules event. If there is an established relation from
      $requestee to $requester, the disregarded flag is set.

    friendlist_api_set_relation_field($requester, $requestee, $rtid, $field_name, $field_value)
    - Handy function that sets a specific field in an established relation

  Statuses
  --------

  friendlist_api_relation_status_get($requester, $requestee, $rtid)
  - Returns the status of the relation type $rtid between $requester and
    $requestee

  friendlist_api_status_data($status_name = '')
  - Returns the data structure that sets the allowed actions and user
    messages for each status. If $p is set, will only return the information
    for the status $status_name

  friendlist_api_relation_allowed_op($op, $requester, $requestee, $rtid)
  - $op can be 'add' or 'delete'. It will tell you of that operation is
    allowed for that relation. If user 1 has an established relation with user
    2, for example, then 'delete' will return TRUE

    friendlist_api_db_statuses($op, $requester, $requestee, $rtid, $status)
  - $op can be "count" or "select". If "select", it returns a database object
     after querying with AND for all the fields. $status can be an array of
     statuses, which will be OR'ed. If "count", it returns the number of
     rows returned by the query

The details
-----------

So, if you are desperate to try this module, and your hands are itching, here
is a quick overview which will cover two way and one way relations.

This section will run through the commands given above, and will explain
exactly what happens to the database structure when you run these
commands.

  Two way relations in detail
  -------------------------------

First of all, create a relation type -- call it "friend":

<code>
friendlist_api_relation_type_add('friend', 'friends', FALSE, TRUE );
</code>

The first two parameters are the relation's name, in singular and plural
forms. The third one is the "oneway" flag, which in this case is false. The
last parameter is TRUE to set the relation type as "active".

This function, like most functions in this API, will return 0 if everything
was good, or a number if things didn't go so well.

At this point, you should load this relation to see what the ID is (and to
get to know this API):

<code>
$relation_type = friendlist_api_relation_type_load('friend');
</code>

This function will take either a relation id, or a relation name, and will
fill the $relation variable with the result. i

The end result on the DB is:

+------+--------+---------+--------+--------+
| rtid | name   | name_p  | oneway | active |
+------+--------+---------+--------+--------+
|    1 | friend | friends |      0 |      1 | 
+------+--------+---------+--------+--------+

So:

<code>
$rtid = $relation_type->rtid;
</code>

At this point, you have the relation ID.

Now, assuming that you have two users, 1 and 6, you could create a relation
request between 1 and 6:

<code>
$requestee = user_load( array('uid' => 6) );
friendlist_api_relation_add(1, $requestee, $rtid, "Yes?");
</code>

There you are: at this point user "1" wants to establish a 2 way relation of
type "friend" with user 6. As with ANY other function in this API that takes
a user id, you can also pass the user object instead -- the API will do
the translation.

Since "friend" is a 2 way relation, at this point in the UI the user 6 will
see a request from user 1: I want to become your "friend".
The friendlist_relation table will look like this:
(Note: here I assume that rtid for "friend" is 1)

+-----+------------+-----------+-----+-------+-----------+-------------------+
|rid  |requester_id|requestee_id|rtid|message|create_time|tw_disregarded_time|
+-----+------------+-----------+-----+-------+-----------+-------------------+
| 32  |        1   |         6 |  1  |  Yes? | 1221847015|                 0 |
+-----+------------+-----------+-----+-------+-----------+-------------------+

At the same time, the "friendlist_statuses" table will look like this:

+--------------+--------------+------+-------------+------------+-----+
| requester_id | requestee_id | rtid | status      | rid_origin | rid |
+--------------+--------------+------+-------------+------------+-----+
|            1 |            6 |    1 | TW_1_TO_2_P |  32        |  32 | 
|            6 |            1 |    1 | TW_2_TO_1_P |  32        |   0 |
+--------------+--------------+------+-------------+------------+-----+

This is _really_ important to understand -- and there is some trickery
involved here as well, so that everything works beautifully with views and
with the DB structure in general.

The friendlist_statuses table is crucial here.
The first row says that the status between
1 and 6, for relation type 1 ("friend") is "TW_1_TO_2_P", and that the
originating row in the friendlist_relation table is "32" (the one that
contains the relation).

The second row is similar. It says that the status between 6 and 1
is TW_2_TO_1_P -- which means that 1 has a pending request to 6. The
originating row in the friendlist_relations table is, again 32. 

What about the "rid" column? That's actually how the friendlist_request table
finds its status. This is why it's absolutely crucial that it's set to
'0' for the second row. The second row in the friendlist_status table
is not the status of any existing relation. It's just "it". The first
row, however, is indeed the status associated to the relation just created.

To check the status:

<code>
friendlist_api_relation_status_get(1, 6, $rtid); # > TW_1_TO_2_P
</code>

If user 6 wants to DENY the friend request:

<code>
friendlist_api_relation_delete(6, 1, $rtid);
</code>

Basically, using "delete" will work even if a relation between 6 and 1 hadn't
been established, AND it will work as a "deny" to the relation between 1 and 6.

The result in terms of database will be:

+-----+------------+-----------+-----+-------+-----------+-------------------+
|rid  |requester_id|requestee_id|rtid|message|create_time|tw_disregarded_time|
+-----+------------+-----------+-----+-------+-----------+-------------------+
| 32  |        1   |         6 |  1  |  Yes? | 1221847015|       1221847075  |
+-----+------------+-----------+-----+-------+-----------+-------------------+

The crucial piece of information here is that number in the tw_disregarded_time
column: it means that the request was denied.
At the same time, the "friendlist_statuses" table will look like this:

+--------------+--------------+------+-------------+------------+-----+
| requester_id | requestee_id | rtid | status      | rid_origin | rid |
+--------------+--------------+------+-------------+------------+-----+
|            1 |            6 |    1 | TW_1_TO_2_D |  32        |  32 | 
|            6 |            1 |    1 | TW_2_TO_1_D |  32        |   0 |
+--------------+--------------+------+-------------+------------+-----+

The statuses have changed; nothing else has.

The status:

<code>
friendlist_api_relation_status_get(1, 6, $rtid); # > TW_1_TO_2_D
</code>

If user 6 wants to accept it:

<code>
friendlist_api_relation_add(6, 1, $rtid, "Accepted");
</code>

In this case, two records will exist: one that goes from 1 to 6, and one that
goes from 6 to 1:


+-----+------------+-----------+-----+-------+-----------+----------------+
|rid  |requester_id|requestee_id|rtid|message|create_time|tw_disregarded_t|
+-----+------------+-----------+-----+-------+-----------+----------------+
| 32  |        1   |         6 |  1  |       | 1221847015|              0 |
| 33  |        6   |         1 |  1  |       | 1221847195|              0 |
+-----+------------+-----------+-----+-------+-----------+----------------+

Note that the tw_disregarded_time has been set to 0.
At the same time, the "friendlist_statuses" table will look like this:

+--------------+--------------+------+-------------+------------+-----+
| requester_id | requestee_id | rtid | status      | rid_origin | rid |
+--------------+--------------+------+-------------+------------+-----+
|            1 |            6 |    1 | TW_BOTH     |  32        |  32 | 
|            6 |            1 |    1 | TW_BOTH     |  33        |  33 |
+--------------+--------------+------+-------------+------------+-----+


<code>
friendlist_api_relation_status_get(1, 6, $rtid); # > TW_BOTH
</code>

The status has now changed: for both users, it's now TW_BOTH. The interesting
part is again in rid_origin and rid: now both statuses have an originating
relation. So, in this case rid_origin == rid.


  One way relations in detail
  ---------------------------

One way relations are much easier to deal with compared to two way ones.

To create one:

<code>
friendlist_api_relation_type_add('fan', 'fans', FALSE, TRUE );
</code>

The end result on the DB is:

+------+--------+---------+--------+--------+
| rtid | name   | name_p  | oneway | active |
+------+--------+---------+--------+--------+
|    2 | fan    | fans    |      1 |      1 | 
+------+--------+---------+--------+--------+

Just like the "friend" relationship, load it:

<code>
$relation_type = friendlist_api_relation_type_load('fan');
</code>

And get the relation ID:

<code>
$rtid = $relation_type->rtid;
</code>

Assuming that the relation type ID is 2, if 1 wants to add 6 as a fan:


<code>
$requestee = user_load( array('uid' => 6) );
friendlist_api_relation_add(1, $requestee, $rtid, "Fan!");
</code>


+-----+------------+-----------+-----+-------+-----------+----------------+
|rid  |requester_id|requestee_id|rtid|message|create_time|tw_disregarded_t|
+-----+------------+-----------+-----+-------+-----------+----------------+
| 34  |        1   |         6 |  2  | Fan?  | 1221847015|              0 |
+-----+------------+-----------+-----+-------+-----------+----------------+

Note that the tw_disregarded_time column doesn't apply here.
The "friendlist_statuses" table will look like this:

+--------------+--------------+------+-------------+------------+-----+
| requester_id | requestee_id | rtid | status      | rid_origin | rid |
+--------------+--------------+------+-------------+------------+-----+
|            1 |            6 |    2 | OW_1_TO_2   |  34        |  34 | 
|            6 |            1 |    2 | OW_2_TO_1   |  34        |   0 |
+--------------+--------------+------+-------------+------------+-----+

The fields at this point should be self-explanatory. It's exactly the
same as two way relations, in terms of statuses. There are two statuses
set, both of them have an originating relationship, but only one is linked
to the relation ID through the rid field.

Interestingly, 6 could also become friends of 1:

<code>
friendlist_api_relation_add(6, 1, $rtid, "Me too!");
</code>

The end result is:

+-----+------------+-----------+-----+--------+-----------+----------------+
|rid  |requester_id|requestee_id|rtid|message |create_time|tw_disregarded_t|
+-----+------------+-----------+-----+--------+-----------+----------------+
| 34  |        1   |         6 |  2  | Fan?   | 1221847015|              0 |
| 35  |        6   |         1 |  2  | Me too!| 1221847095|              0 |
+-----+------------+-----------+-----+--------+-----------+----------------+

Those two records are independent from each other.
However, the statuses:

+--------------+--------------+------+-------------+------------+-----+
| requester_id | requestee_id | rtid | status      | rid_origin | rid |
+--------------+--------------+------+-------------+------------+-----+
|            1 |            6 |    2 | OW_BOTH     |  34        |  34 | 
|            6 |            1 |    2 | OW_BOTH     |  35        |  35 |
+--------------+--------------+------+-------------+------------+-----+

The status is OW_BOTH, which means that the users are each other's fans.

To query what is going on, you can do:

<code>
friendlist_api_db_statuses('select', 1, NULL, NULL, 'OW_BOTH');
</code>

Which will return a DB object with the list of relations with status
'OW_BOTH' originated from user 1. requestee and relation types won't matter.
To _count_ the results instead:

<code>
friendlist_api_db_statuses('count', 1, NULL, NULL, 'OW_BOTH');
</code>

This will return the number of relations with status 'OW_BOTH' for the user 1.


