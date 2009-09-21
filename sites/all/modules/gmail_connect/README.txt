=====================================================
 GMail Connect
=====================================================
This module provides a message count block and a
basic inbox for users' GMail accounts.  The user must
have IMAP access enabled for their GMail account in
order to use this module.

The module allows users to view, delete, and send
"auto-reply" messages.  The auto-reply message is
nice for users that recieve a lot of email and can't
keep up with all new messages.  The text used in the
auto-reply can be set per user on the /user/$uid/edit
page.

=====================================================
 Known Issues
=====================================================
 * the count in the block and the GMail connect user
   tab are not cached and therefore can be different
   than the new messagrs in the inbox.

=====================================================
 TODO
=====================================================
 * cache full inbox for entire session and only get
   new/changed messages from the server
 * Add more jQuery for viewing messages/paging
 * Support attachments on email
 * Allow user to reply to messages (not just auto-
   reply)

=====================================================
 Contact
=====================================================
Questions or comments?  Email me:
  Elliott Foster
  http://codebrews.com
  elliottf@codebrews.com
