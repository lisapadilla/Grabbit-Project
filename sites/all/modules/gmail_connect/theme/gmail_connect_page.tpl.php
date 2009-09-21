<?php
// $Id: gmail_connect_page.tpl.php,v 1.1 2009/05/04 22:18:06 elliottf Exp $

/**********************************************************/
/* gmail_connect_page.tpl.php - this theme template       */
/*  handles the display of the messages on the profile.   */
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
//print_r($pager); // the links to use with the module
?>
<div class="message_box">

  <?php if ($pager) { ?>
    <div class="pager">
      <?php print $pager ?>
    </div>
  <?php } ?>

  <div class="messages">
    <?php print $messages ?>
  </div>

  <?php if ($pager) { ?>
    <div class="pager">
      <?php print $pager ?>
    </div>
  <?php } ?>

</div>
