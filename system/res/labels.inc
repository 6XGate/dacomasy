<?php
/////////////////////////////////////////////////////////////////////////////
// Copyright (C)2005 6XGate Incorporated
//
// This file is part of Dacomasy
//
// Dacomasy is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// Dacomasy is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
/////////////////////////////////////////////////////////////////////////////
/**
 * Includes all the constants for referencing labels.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Resources
 * @version $SixXGate: webapps/dacomasy/www/system/res/labels.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

/**#@+ Label Catagories */
	
	define('__DACOMASY_LABELCAT_MISC',				0x00000000, TRUE);
	define('__DACOMASY_LABELCAT_BUTTONS',			0x01000000, TRUE);
	define('__DACOMASY_LABELCAT_HEADERS',			0x02000000, TRUE);
	define('__DACOMASY_LABELCAT_PAGESS',			0x03000000, TRUE);
	
/**#@-*/

/**#@+ Button Labels */
	
	define('__DACOMASY_LABEL_OK',					__DACOMASY_LABELCAT_BUTTONS + 0x1, TRUE);
	define('__DACOMASY_LABEL_CANCEL',				__DACOMASY_LABELCAT_BUTTONS + 0x2, TRUE);
	define('__DACOMASY_LABEL_CHANGEPWD',			__DACOMASY_LABELCAT_BUTTONS + 0x3, TRUE);
	define('__DACOMASY_LABEL_EDIT',					__DACOMASY_LABELCAT_BUTTONS + 0x4, TRUE);
	define('__DACOMASY_LABEL_DEL',					__DACOMASY_LABELCAT_BUTTONS + 0x5, TRUE);
	define('__DACOMASY_LABEL_ADDNEW',				__DACOMASY_LABELCAT_BUTTONS + 0x6, TRUE);
	define('__DACOMASY_LABEL_MOVEUP',				__DACOMASY_LABELCAT_BUTTONS + 0x7, TRUE);
	define('__DACOMASY_LABEL_MOVEDN',				__DACOMASY_LABELCAT_BUTTONS + 0x8, TRUE);
	define('__DACOMASY_LABEL_CLOSE',				__DACOMASY_LABELCAT_BUTTONS + 0x9, TRUE);
	define('__DACOMASY_LABEL_LICENSE',				__DACOMASY_LABELCAT_BUTTONS + 0xA, TRUE);
	define('__DACOMASY_LABEL_YES',					__DACOMASY_LABELCAT_BUTTONS + 0xB, TRUE);
	define('__DACOMASY_LABEL_NO',					__DACOMASY_LABELCAT_BUTTONS + 0xC, TRUE);
	
/**#@-*/

/**#@+ Dialog Labels */
	
	define('__DACOMASY_LABEL_SYSINFO',				__DACOMASY_LABELCAT_MISC + 0x1, TRUE);
	define('__DACOMASY_LABEL_SERVERSW',				__DACOMASY_LABELCAT_MISC + 0x2, TRUE);
	define('__DACOMASY_LABEL_SERVEROS',				__DACOMASY_LABELCAT_MISC + 0x3, TRUE);
	define('__DACOMASY_LABEL_USERAGENT',			__DACOMASY_LABELCAT_MISC + 0x4, TRUE);
	define('__DACOMASY_LABEL_PHPVER',				__DACOMASY_LABELCAT_MISC + 0x5, TRUE);
	define('__DACOMASY_LABEL_MAXOF',				__DACOMASY_LABELCAT_MISC + 0x6, TRUE);
	define('__DACOMASY_LABEL_MINOF',				__DACOMASY_LABELCAT_MISC + 0x7, TRUE);
	
/**#@-*/

/**#@+ Header Labels */
	
	define('__DACOMASY_LABEL_PANELS',				__DACOMASY_LABELCAT_HEADERS + 0x1, TRUE);
	define('__DACOMASY_LABEL_APPVERSION',			__DACOMASY_LABELCAT_HEADERS + 0x2, TRUE);
	
/**#@-*/

/**#@+ Page Title Labels */
	
	define('__DACOMASY_LABEL_ABOUT',				__DACOMASY_LABELCAT_PAGESS + 0x1, TRUE);
	define('__DACOMASY_LABEL_ADDRECORD',			__DACOMASY_LABELCAT_PAGESS + 0x2, TRUE);
	define('__DACOMASY_LABEL_EDITRECORD',			__DACOMASY_LABELCAT_PAGESS + 0x3, TRUE);
	define('__DACOMASY_LABEL_DELRECORD',			__DACOMASY_LABELCAT_PAGESS + 0x4, TRUE);
	define('__DACOMASY_LABEL_MOVEECORD',			__DACOMASY_LABELCAT_PAGESS + 0x5, TRUE);
	
/**#@-*/

?>