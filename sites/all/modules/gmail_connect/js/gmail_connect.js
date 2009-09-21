// $Id: gmail_connect.js,v 1.1 2009/05/04 22:18:06 elliottf Exp $

/**********************************************************/
/* gmail_connect.js - handle the JavaScript operations of */
/*  the gmail_connect module.                             */
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

if (Drupal.jsEnabled) {
  $(document).ready(function() {
    $('.gmail_connect_delete').click(function() {
      var id_ary = this.id;
      id_ary = id_ary.split('-');
      var id = id_ary[1];

      $('#message-'+id).fadeOut("slow", function() { ajax_delete(id); });
      return false;
    });
  });

  /**
   * ajax_delete - submit the delete request
   *  via  AJAX.
   */
  function ajax_delete(mid) {
    // handle sites that don't use clean URLs... this might not
    // be a catch-all
    $.get(Drupal.settings.basePath + ((location.href.indexOf('?q=') != -1) ? '?q=' : '') + 'gmail_connect/js/delete/' + mid);
  }
}
