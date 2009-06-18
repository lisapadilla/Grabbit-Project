==============================================================================
FRIENDLIST
==============================================================================

Description: Friendlist is a powerful module to manage user relationships.
Maintainer: mercmobily
Co-Maintainer: mariusooms



.----------------------------------------------------------------------------.
|                                - Contents -                                |
'----------------------------------------------------------------------------'

SECTION 1		Introduction
SECTION 1.1		Relations
SECTION 1.2		Statuses
--------------------------------------------------------------
SECTION 2		Theming and UI functions
--------------------------------------------------------------
SECTION 3		Module dependency
--------------------------------------------------------------
SECTION 4		Views Integration
SECTION 4.1		Default Views
SECTION 4.2		Views Tutorial - From scratch
SECTION 4.3		Views Tutorial - Picture support
SECTION 4.4		Views Tutorial - Friend feed logged in user
--------------------------------------------------------------
SECTION 5		Rules Integration
SECTION 5.1		Default Rules
SECTION 5.2		Rules Tutorial - From scratch
SECTION 5.3		Rules Tutorial - Two way without confirmation
--------------------------------------------------------------
SECTION 6		Styling friendlist



.----------------------------------------------------------------------------.
|                         - SECTION 1: Introduction -                        |
'----------------------------------------------------------------------------'

Friendlist is a powerful module to manage user relationships, but friendlist
doesn't just manage friends: using the Friendlist UI module, you can define as
many relation types as you like. Relations can be one way or two way, and can
be active or inactive. The module comes preset with two types of relations,
"friend" and "fan", which are set to active by default.



.----------------------------------------------------------------------------.
|                         - SECTION 1.1: Relations -                         |
'----------------------------------------------------------------------------'

There are two types of relationships:

* One way
* Two way

A one way relation is one that can exist without being mutual. No confirmation
or approval is needed or possible. 

In database terms, only one record exists for each one way relation.

A two way relations need to be mutual in order to be complete. For example, in
order for two people to be friends, user 1 needs to be friends with friends 2,
and vice versa. If mutuality is not there, there will be an expectation from
the other user to either accept or refuse the request.

In database terms, a mutual relation will have two records: one from user 1 to
user 2, and one from user 2 to user 1. On the other hand, a refused
relationship will have one record only: user 1 to user 2. The record will also
have a "disregarded" flag, which basically means "the other user has
declined". If the "disregarded" flag is not there, then the relation is
considered "pending".

Assume that user 1 is the requester, and user 2 is the requestee. user 1 wants
to be friends with user 2. A row gets created in the database, but that's not
enough: in order for the friendship to be mutual, user 2 needs ALSO to become
friends with user 1. user 2 at this point has two options:

- Disregard user 1's request. This will add a disregarded_time field to user
  1's request. User 1 won't be able to send new requests either, and (MOST
  importantly) won't be able to delete the denied request to user 2.
- Accept user 1's request. If this happens, effectively user 1 is now friends
  with user 2, and vice versa. 

This has the following implications:

- As already stated earlier, if user 1 has a disregarded friendship with user
  2, then user 1 is _stuck_ with it. This record is important to make sure
  that user 1 doesn't send more requests to user 2, prevent abuse.
- If user 2 decides LATER to become friends with user 1, then the friendship
  can be established right away. The friendship becomes mutual AND the
  disregarded field in user 1's record gets reset.
- If user 1 decides to STOP being friends with user 2, a disregarded flag will
  be set on user 2's request for being friends with him. This will prevent
  user 2 from sending further requests.



.----------------------------------------------------------------------------.
|                         - SECTION 1.2: Statuses -                          |
'----------------------------------------------------------------------------'

Statuses are a very, very crucial part of Friendlist. Statuses is what make
friendlist immensely powerful and unique (compared to other relation modules).
Here is a list of possible statuses, taken from the module's developers'
documentation:

------------------------------------------------------------------------------
 * --- IF THE RELATIONSHIP TYPE IS ONE WAY:
 * OW_NONE   : Inactive. On both sides.
 * OW_1_TO_2 : Active.  Relation $requester -> requestee
 * OW_2_TO_1 : Active.  Relation $requestee -> requester
 * OW_BOTH   : Active.  Relation $requester -> requestee AND vice-versa
 *
 * --- IF THE RELATIONSHIP TYPE IS TWO WAY:
 * TW_NONE     : Inactive. On both sides.
 * TW_1_TO_2_P : Inactive. $requester requested, $requestee didn't disregard
 * TW_1_TO_2_D : Inactive. $requester requested, $requestee disregarded
 * TW_2_TO_1_P : Inactive. $requestee requested, $requester didn't disregard
 * TW_2_TO_1_D : Inactive. $requestee requested, $requester disregarded
 * TW_BOTH     : Active. TWO WAY. They are each others "friends".
------------------------------------------------------------------------------

While it's not important that you know the name of each status, it is
important that you know they exist as this will help you deal with Views,
Rules, etc, as these statutes dictate the actions you can take.

Remember that a status is always considered from one user to the other. So, if
you have two users, Oscar and Tom, and you check the status of their two way
relationship:

* If Oscar -> Tom is TW_1_TO_2_P, then Tom -> Oscar will be TW_2_TO_1_P.
* If their relationship is established, then the status is always TW_BOTH.



.----------------------------------------------------------------------------.
|                  - SECTION 2: Theming and UI functions -                   |
'----------------------------------------------------------------------------'

Friendlist comes with FriendList UI, a powerful module that lets you actually
_do_ things with it. This module has two functions you will probably find
useful as a user/themer:

/**
 * function friendlist_ui_get_link($op, $account, $rtid)
 *
 * In friendlist, a friend can be added or deleted. This function
 * will return the right link (with the right text!) to add or delete
 * a user
 *
 * @param $op
 *   It could be 'add' or 'delete', depending on what type of link you
 *   want
 * @param $account
 *   The user object (or id) you want the links for
 * @param $rtid
 *   The relation type id you want the links for
 *
 * @return
 *    The link ready to be used.
 */


/**
 * function friendlist_ui_user_links($account)
 *
 * An HTML-formatted list of links for EVERY relation type for
 * the user. This function is used by the hook_user() hook
 * to show links about the user.
 *
 * @param $account
 *   The user object (or id) you want the links for
 *
 * @return
 *   HTML items, formatted with theme_item_list
 */

Especially the second one can be placed anywhere you like, and it will give
you the list of every action for any relation type. It's what the module
itself uses for the user profile pages.



.----------------------------------------------------------------------------.
|              - SECTION 3: Module Integration and Dependency -              |
'----------------------------------------------------------------------------'

Friendlist uses several other modules. The idea is to not reinvent the wheel, 
but harness the power of other modules. This has several advantages. 

For one, it creates consistency for the friendlist module as this prevents 
it in becoming a mash-up of code. It also helps the module stay specific 
in using other other modules which have an equal specific function. Some 
modules it depends on, while other modules add a specific functionality.

Dependent:
Views - http://drupal.org/project/views (Friendlist Blocks and Pages)
Rules - http://drupal.org/project/rules (Friendlist Notifications)

Not dependent, but strongly advised:
Token - http://drupal.org/project/token (Token support Rules and Activity_log)

Integrated:
Activity Log - http://drupal.org/project/activity_log (Activity Stream)
Popups - http://drupal.org/project/popups (Instant modal message support)
CCK Field Privacy - http://drupal.org/project/cck_field_privacy
Profile Privacy - http://drupal.org/project/profile_privacy (Pending)

NOTE: Some of these modules have not released official version yet and 
require dev installs. They all have been tested and are fully functional.



.----------------------------------------------------------------------------.
|                      - SECTION 4: Views Integration -                      |
'----------------------------------------------------------------------------'

Views is a very powerful and flexible module to create custom pages and blocks
that list content according to a specific database query. Because Views can be
intimidating at first you can the reference below for additional help or you
can install the advanced help module module.

http://views-help.doc.logrus.com/



.----------------------------------------------------------------------------.
|                       - SECTION 4.1: Default Views -                       |
'----------------------------------------------------------------------------'

The module comes with 4 pre-configured views, which should get most users up
and running. You can always use the pre-configured views as a guide when
creating your own views. They are named:
 
- friendlist_manage_oneway
- friendlist_public_oneway
- friendlist_manage_twoway 
- friendlist_public_twoway

- friendlist_manage_oneway
  This view consists of one page display only. It deals with all connections 
  the user has made to other users with the available actions. The default 
  path of this view is /connections/manage/oneway. It is only accessible by 
  the logged in user.

- friendlist_public_oneway
  This view consists of two block displays and two page displays. One pair of
  block and page display deal with the connections the current user has
  established. We refer to these as "following" connections. The second pair 
  of block and page display deals with connections others have made to the 
  current user. We refer to these as "follower" connections. Each block 
  display has a 'more' link that links to the users list of all following and 
  follower connections.

- friendlist_manage_twoway
  This view consists of three page displays. One for managing all TW_Both
  relationships. One for dealing with TW_1_TO_2_P relations from the requestee
  and another page for dealing with TW_1_TO_2_P from the requester. Their   
  paths are respectively, /connections/manage/twoway, /connections/send and
  /connections/received. They are only accessible by the logged in user.

- friendlist_public_twoway
  This view consists of one block display and one page display. They both deal
  with TW_BOTH relations and show the latest mutual connections in relation to
  to the current user. The block display has a 'more' link that links to the
  users list of all mutual connections.



.----------------------------------------------------------------------------.
|               - SECTION 4.2: Views Tutorial - From scratch -               |
'----------------------------------------------------------------------------'

*** Creating a "Relations between users" type view ***

______________________________________________________________________________

The scenario: 
Create a single view page that shows your established twoway connections, with
action links to manage your relations list.
______________________________________________________________________________

STEP 1 - Add view:
Select 'Add' from the views menu. Give the view a name, description and tag. 
IMPORTANT! For the view type, select "Relations between users" and click Next.

You now arrive at the edit screen for the added view. The view screen is made
up out of many different sections, they are named:
- Display menu
- View settings
- Basic settings
- Block settings (visible when adding a block)
- Page settings (visible when adding a page)
- Relationships
- Arguments
- Fields
- Sort criteria
- Filters
- Live preview

It is best to work your way down through these sections as they are listed in
a logical order.
______________________________________________________________________________

STEP 2 - Display menu:
Start by adding a page display. You will now have an additional display apart
from Defaults. Each display can have unique settings by clicking the provided
override button when changing a particular setting.
______________________________________________________________________________

STEP 3 - View settings:
Go through each setting and change it to your liking. For our example table
works best for "Style".
______________________________________________________________________________

STEP 4 - Page settings:
Click path and change the path to a suitable structure, e.g. relation/manage.
Update. Next click "No menu", select "Normal menu entry" and give it a title.
Update.
______________________________________________________________________________

STEP 5 - Relationships:
Click the + icon, this brings up the available relation groups. Select both
options "Relations: Requestee user" and "Relations: Requesting user". Add.
Views will ask you to give a Label for each relation. You can leave the
default suggestion. Update both.
______________________________________________________________________________

STEP 6 - Arguments:
We can actually skip this for our tutorial. Arguments become especially useful
for friendlist when using blocks in terms for visibility.
______________________________________________________________________________

STEP 7 - FIELDS:
Click the + icon, select Statuses from Groups and check "Statuses: Status".
You can use the default Label. Update. At this point the "Live preview" will
actually start to show some information if you have made some connections
between users. Click the + icon and add "User: Name" from the User Group menu.
Add. Relationship should be "Requestee". Update. Click the + icon and select
"Relations: Action from logged in user to requestee" under the Relations
Group. Add. Name the label Actions. Note: Don't pay to much attention to Live
preview, just take note of its behavior.
______________________________________________________________________________

STEP 8 - Sort Criteria:
This is a useful section to sort your data. We can skip this. Also, because we
use a table you have all kinds of sort options by clicking the cog icon next
to table under the "Basic settings" section.
______________________________________________________________________________

STEP 9 - Filters:
Click the + icon and select "Relations: Requester user is the currently logged
in user" from the Relations Group. Add. Check "is the logged user". Update.
Click the + icon and select "Statuses: Status" from the Status Group. Add. Set
settings to "Is one of" - "TW_BOTH". Update.
______________________________________________________________________________

STEP 10 - Live preview:
At this point you can check the Live preview and should return all the
established TW_BOTH connections the logged user has made together with the
available actions in a table format.
______________________________________________________________________________


That's it...and this is only scratching the surface of things you can do.
Customize the basics to your liking by adding send messages, time stamps when
the relation was created, custom core profile fields, user pictures, sort
options, role specific restrictions, header and footer information, add more
blocks and pages. The list goes on and on! The best advice we can give is
practice, practice, practice so you get to know your management system.



.----------------------------------------------------------------------------.
|             - SECTION 4.3: Views Tutorial - Picture support -              |
'----------------------------------------------------------------------------'

[TODO]



.----------------------------------------------------------------------------.
|             - SECTION 4.4: Views Tutorial - Friend feed logged in user -   |
'----------------------------------------------------------------------------'

[TODO]



.----------------------------------------------------------------------------.
|                      - SECTION 5: Rules Integration -                      |
'----------------------------------------------------------------------------'

The module is fully integrated with Rules. Rules is a replacement with more
features for the trigger module in core and the successor of the workflow-ng
module. Friendlist uses it for all notifications to and from users.



.----------------------------------------------------------------------------.
|                       - SECTION 5.1: Default Rules -                       |
'----------------------------------------------------------------------------'

The default rules included with friendlist are:

* Friendlist - Notify recipient: Now added
* Friendlist - Notify initiator: Remove
* Friendlist - Notify requester: Request send
* Friendlist - Notify requestee: Request send
* Friendlist - Notify requester: Request accepted
* Friendlist - Notify requestee: Request accepted
* Friendlist - Notify requester: Request cancelled
* Friendlist - Notify requestee: Request cancelled
* Friendlist - Notify requester: Request declined
* Friendlist - Notify requestee: Request declined
* Friendlist - Notify requester: Relation deleted
* Friendlist - Notify requestee: Relation deleted

We will be adding more rules to this list as friendlist continues its
expansion with features.

Note that each rules uses the site wide email as the sender email. You can set
this at admin/settings/site-information. This is to ensure that the users
email stays hidden. If your users emails are public, you can easily change
each rule to reflect this if you wish.



.----------------------------------------------------------------------------.
|               - SECTION 5.2: Rules Tutorial - From scratch -               |
'----------------------------------------------------------------------------'

Every rules as the same ingredients and involves a three step process. Where
each step has multiple configuration options.

Step 1 involves creating the rule and its specific event.
Step 2 involves setting the conditions for the rule.
Step 3 involves adding actions that will be taken when the conditions are met.



.----------------------------------------------------------------------------.
|       - SECTION 5.3: Rules Tutorial - Two way without confirmation -       |
'----------------------------------------------------------------------------'

[TODO]



.----------------------------------------------------------------------------.
|                      - SECTION 6: Styling friendlist -                     |
'----------------------------------------------------------------------------'

Styling is easy with a little bit of css knowledge. Below is an example of how
to style the available links of friendlist. You can just copy and paste this
code in to your style-sheet. Make sure you adjust the link classes, image
dimensions and image path. This technique can easily be applied to other areas
like replacing the relation name with an icon.

/* set li to block and specify width and height of your replacement image */

ul.friendlist-user-links-multiple li {
display: block;
height: 25px;
width: 150px;
}

/* The class of the link. Use text-indent to hide text. */

ul.friendlist-user-links-multiple li a.(replace with link class) {
display: block;
height: 25px;
text-indent: -9999px;
background: url(path/to/your/images/image.gif) no-repeat left bottom;
}

/* On hover the background will move from 'left bottom' to 'left top' */

ul.friendlist-user-links-multiple li a.(replace with link class):hover {
background-position: left top;
}







