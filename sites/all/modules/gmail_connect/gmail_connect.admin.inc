<?php
// $Id: gmail_connect.admin.inc,v 1.1 2009/05/04 22:18:06 elliottf Exp $

/**********************************************************/
/* gmail_connect.admin.inc - the callbacks for the admin  */
/*  pages created by the gmail_connect module.            */
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

/**
 * gmail_connect_settings - return the settings form
 *  for the GMail Connect module.
 */
function gmail_connect_settings() {
  $form = array();

  $form['gmail_connect_cache_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Cache Timeout'),
    '#default_value' => variable_get('gmail_connect_cache_timeout', 60),
    '#description' => t('Enter the number of seconds to store GMail messages in cache.'),
  );

  return system_settings_form($form);
}
