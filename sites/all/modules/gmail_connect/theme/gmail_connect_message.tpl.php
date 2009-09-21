<?php
// $Id: gmail_connect_message.tpl.php,v 1.1 2009/05/04 22:18:06 elliottf Exp $

/**********************************************************/
/* gmail_connect_message.tpl.php - this theme template    */
/*  displays a message.                                   */
/*                                                        */
/* This program is free software: you can redistribute it */
/*  and/or modify it under the terms of the GNU General   */
/*  Public License as published by the Free Software      */
/*  Foundation, either version 3 of the License, or (at   */
/*  your option) any later version.                       */
/*                                                        */
/* This program is distributed in the hope that it will   */
/*  be useful, but WITHOUT ANY WARRANTY; without even the */
/*  implied warranty of MERCHANTABILITY or FITNESS FOR A  */
/*  PARTICULAR PURPOSE.  See the GNU General Public       */
/*  License for more details.                             */
/*                                                        */
/* You should have received a copy of the GNU General     */
/*  Public License along with this program.  If not, see  */
/*  <http://www.gnu.org/licenses/>.                       */
/*                                                        */
/* @author: Elliott Foster                                */
/* @copyright: Elliott Foster 2009                        */
/**********************************************************/

// AVAILABLE VARIABLES - uncomment the following lines to
// view the variables:
//print_r($header); // the message header object -- see imap_headerinfo()
//print_r($body); // the message body -- see imap_body()
?>
<div class="message_wrapper">
  <div class="message_header">
    <div class="message_from">From: <?php print $header->fromaddress ?></div>
    <div class="message_to">To: <?php print $header->toaddress ?></div>
    <?php if ($header->ccaddress) { ?>
      <div class="message_cc">CC: <?php print $header->ccaddress ?></div>
    <?php } ?>
    <div class="message_date">Date: <?php print date('M d, Y \a\t H:i', $header->udate) ?></div>
  </div>
  <div class="message_body">
    <?php print $body ?>
  </div>
</div>
