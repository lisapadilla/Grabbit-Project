$Id: README.txt,v 1.3 2009/02/24 21:27:12 george2 Exp $

EasyLogin Module

Allow users to log in via the URL.

Instructions
1/ Install the module by copying the module files to the desired modules directory

2/ Activate the module in admin/build/modules.

3/ Once activated, the module will: create a sub menu (MENU_LOCAL_TASK) on the user account page with their url, and if the user has the permission to reset their own password, a button to reset it.

4/ Two permissions are exposed, 'login from url', and 'reset own url'. Please grant as necessary. If a user has the 'administer users' permission set, they can reset users login urls

5/ This module will redirect the user after login if ?destination=[destination] ie (?destination=node/1) is appended to the login url. If login_destination is installed (http://drupal.org/project/login_destination), the user will be redirected as specified by login_destination.