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
 * Includes all the constants for referencing errors and error messages.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Resources
 * @version $SixXGate: webapps/dacomasy/www/system/res/errors.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

/**#@+ Error Catagory */
	
/** General Errors */		define ('__DACOMASY__ERRORCAT_GENERAL',							0x00000000, TRUE);
/** Module Errors */		define ('__DACOMASY__ERRORCAT_MODULE',							0x01000000, TRUE);
/** Database Errors */		define ('__DACOMASY__ERRORCAT_SQL',								0x02000000, TRUE);
	
/**#@-*/

/**#@+ Error Sub Catagories */
	
/** General */			define ('__DACOMASY__ERRORSUB_GENERAL',							0x000000, TRUE);
/** Syntax */			define ('__DACOMASY__ERRORSUB_SYNTAX',							0x010000, TRUE);
/** I/O */				define ('__DACOMASY__ERRORSUB_IO',								0x020000, TRUE);
/** Memory */			define ('__DACOMASY__ERRORSUB_MEM',								0x030000, TRUE);
	
/**#@-*/
	
/**#@+ General Errors */
	
	/**#@+ General Error */
		
		/** No Error Occurred */
		define ('__DACOMASY_ERROR_SUCCESSFUL',						__DACOMASY__ERRORCAT_GENERAL + __DACOMASY__ERRORSUB_GENERAL + 0x0, TRUE);
		
	/**#@-*/
	
	/**#@+ I/O Error */
		
		/** Missing required authentication keys in dacomasy.ini */
		define('__DACOMASY_ERROR_FAILAUTHCONFIG',				__DACOMASY__ERRORCAT_GENERAL + __DACOMASY__ERRORSUB_IO + 0x1, TRUE);
		
	/**#@-*/
	
/**#@-*/

/**#@+ Module Errors */
	
	/**#@+ General Module Error */
		
		/** Invalid Panel Error */
		define ('__DACOMASY_ERROR_PANELINVALID',					__DACOMASY__ERRORCAT_MODULE + __DACOMASY__ERRORSUB_GENERAL + 0x1, TRUE);
		
	/**#@-*/
	
	/**#@+ Module Syntax Error */
		
		/** Module Format not Valid */
		define ('__DACOMASY_ERROR_MODULENOTVALID',					__DACOMASY__ERRORCAT_MODULE + __DACOMASY__ERRORSUB_SYNTAX + 0x1, TRUE);
		
	/**#@-*/
	
	/**#@+ Module Error, IO Related */
		
		/** Module File not Found */
		define ('__DACOMASY_ERROR_MODULENOTFOUND',					__DACOMASY__ERRORCAT_MODULE + __DACOMASY__ERRORSUB_IO + 0x1, TRUE);
		
	/**#@-*/
	
/**#@-*/

/**#@+ SQL Error */
	
	/**#@+ SQL Syntax Error */
		
		/** Invalid Query */
		define ('__DACOMASY_ERROR_INVALIDQUERY',					__DACOMASY__ERRORCAT_SQL + __DACOMASY__ERRORSUB_SYNTAX + 0x1, TRUE);
		
	/**#@-*/
	
	/**#@+ SQL Error, IO Related */
		
		/** Unable to Connect */
		define ('__DACOMASY_ERROR_CONNECTINGTOSQLSERVER',			__DACOMASY__ERRORCAT_SQL + __DACOMASY__ERRORSUB_IO + 0x1, TRUE);
		/** Database not Found */
		define ('__DACOMASY_ERROR_NOSUCHDATABASE',					__DACOMASY__ERRORCAT_SQL + __DACOMASY__ERRORSUB_IO + 0x2, TRUE);
		
	/**#@-*/
	
/**#@-*/

?>