<?php
// $Id: gmail_connect_counts.tpl.php,v 1.1 2009/05/04 22:18:06 elliottf Exp $

/**********************************************************/
/* gmail_connect_counts.tpl.php - this theme template     */
/*  handles the display of the message counts from the    */
/*  IMAP request.                                         */
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
//print_r($messages); // the messages returned from GMail
//print_r($links); // the links to use with the module
?>
<div class="message_counts">
  <?php if (is_array($messages)) { ?>
    <ul>
    <?php foreach ($messages as $type => $count) { ?>
      <li><?php print $count . ' ' . $type ?></li>
    <?php } ?>
    </ul>
  <?php } else { ?>
    <?php print $messages ?>
  <?php }?>
</div>
<div class="message_links">
  <ul>
    <?php foreach ($links as $link) { ?>
      <li><?php print $link ?></li>
    <?php } ?>
  </ul>
</div>
