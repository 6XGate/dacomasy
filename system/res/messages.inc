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
 * Includes all the constants for referencing messages.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Resources
 * @version $SixXGate: webapps/dacomasy/www/system/res/messages.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

/**#@+ Message Catagory */
	
	define('__DACOMASY_MSGCAT_MISC',				0x00000000, TRUE);
	define('__DACOMASY_MSGCAT_FORMVALID',			0x01000000, TRUE);
	
/**#@-*/

/**#@+ Message Sub-Catagory */
	
	/**#@+ Basic Message Sub-Catagory */
		
		define('__DACOMASY_MSGSUB_MISC',				__DACOMASY_MSGCAT_MISC + 0x000000, TRUE);
		
	/**#@-*/
	
	/**#@+ Form Message Sub-Catagory */
		
		define('__DACOMASY_MSGSUB_FORMVALID_MISC',		__DACOMASY_MSGCAT_FORMVALID + 0x000000, TRUE);
		define('__DACOMASY_MSGSUB_FORMVALID_TEXT',		__DACOMASY_MSGCAT_FORMVALID + 0x010000, TRUE);
		define('__DACOMASY_MSGSUB_FORMVALID_FILE',		__DACOMASY_MSGCAT_FORMVALID + 0x020000, TRUE);
		define('__DACOMASY_MSGSUB_FORMVALID_NUM',		__DACOMASY_MSGCAT_FORMVALID + 0x030000, TRUE);
		define('__DACOMASY_MSGSUB_FORMVALID_LIST',		__DACOMASY_MSGCAT_FORMVALID + 0x040000, TRUE);
		define('__DACOMASY_MSGSUB_FORMVALID_DATETIME',	__DACOMASY_MSGCAT_FORMVALID + 0x050000, TRUE);
		
	/**#@-*/
	
/**#@-*/

/**#@+ Misc Message */
	
	define('__DACOMASY_MSG_ADDFAILED',			__DACOMASY_MSGSUB_MISC + 0x1, TRUE);
	define('__DACOMASY_MSG_ADDSUCCESS',			__DACOMASY_MSGSUB_MISC + 0x2, TRUE);
	define('__DACOMASY_MSG_EDITFAILED',			__DACOMASY_MSGSUB_MISC + 0x3, TRUE);
	define('__DACOMASY_MSG_EDITSUCCESS',		__DACOMASY_MSGSUB_MISC + 0x4, TRUE);
	define('__DACOMASY_MSG_DELFAILED',			__DACOMASY_MSGSUB_MISC + 0x5, TRUE);
	define('__DACOMASY_MSG_DELSUCCESS',			__DACOMASY_MSGSUB_MISC + 0x6, TRUE);
	define('__DACOMASY_MSG_MOVEFAILED',			__DACOMASY_MSGSUB_MISC + 0x7, TRUE);
	
/**#@-*/

/**#@+ Form Validation Message */
	
	/**#@+ General Field Validation Message */
		
		define('__DACOMASY_MSG_FORMINVALID',			__DACOMASY_MSGSUB_FORMVALID_MISC, TRUE);
		define('__DACOMASY_MSG_NONULL',					__DACOMASY_MSGSUB_FORMVALID_MISC + 0x1, TRUE);
		
	/**#@-*/
	
	/**#@+ Text-Type Field Validation Message */
		
		define('__DACOMASY_MSG_TEXTTOOBIG',				__DACOMASY_MSGSUB_FORMVALID_TEXT + 0x1, TRUE);
		define('__DACOMASY_MSG_PWDTOOBIG',				__DACOMASY_MSGSUB_FORMVALID_TEXT + 0x2, TRUE);
		define('__DACOMASY_MSG_PWDTOOSMALL',			__DACOMASY_MSGSUB_FORMVALID_TEXT + 0x3, TRUE);
		define('__DACOMASY_MSG_PWDNOTMATCH',			__DACOMASY_MSGSUB_FORMVALID_TEXT + 0x4, TRUE);
		define('__DACOMASY_MSG_LINKNONULL',				__DACOMASY_MSGSUB_FORMVALID_TEXT + 0x5, TRUE);
		
	/**#@-*/
	
	/**#@+ File-Type Field Validation Message */
		
		define('__DACOMASY_MSG_FILETOOBIG',				__DACOMASY_MSGSUB_FORMVALID_FILE + 0x1, TRUE);
		define('__DACOMASY_MSG_NOTAIMAGE',				__DACOMASY_MSGSUB_FORMVALID_FILE + 0x2, TRUE);
		
	/**#@-*/
	
	/**#@+ Numaric Field Validation Message */
		
		define('__DACOMASY_MSG_NUMTOOBIG',				__DACOMASY_MSGSUB_FORMVALID_NUM + 0x1, TRUE);
		define('__DACOMASY_MSG_NUMTOOSMALL',			__DACOMASY_MSGSUB_FORMVALID_NUM + 0x2, TRUE);
		define('__DACOMASY_MSG_NOTANUMBER',				__DACOMASY_MSGSUB_FORMVALID_NUM + 0x3, TRUE);
		define('__DACOMASY_MSG_TOOMANYDECIMAL',			__DACOMASY_MSGSUB_FORMVALID_NUM + 0x4, TRUE);
		
	/**#@-*/
	
	/**#@+ List-Type Field Validation Message */
		
		define('__DACOMASY_MSG_INVALIDSELECTION',		__DACOMASY_MSGSUB_FORMVALID_LIST + 0x1, TRUE);
		
	/**#@-*/
	
	/**#@+ Date or Time Field Validation Message */
		
		define('__DACOMASY_MSG_INVALIDDATE',			__DACOMASY_MSGSUB_FORMVALID_DATETIME + 0x1, TRUE);
		define('__DACOMASY_MSG_INVALIDTIME',			__DACOMASY_MSGSUB_FORMVALID_DATETIME + 0x2, TRUE);
		define('__DACOMASY_MSG_INVALIDDT',				__DACOMASY_MSGSUB_FORMVALID_DATETIME + 0x3, TRUE);
		
	/**#@-*/

/**#@-*/
?>