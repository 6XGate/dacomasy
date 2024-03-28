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
// This DocBlock will contain the master todo list.
/**
 * Loads all the file needed to use Dacomasy and initializes the it.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @version $SixXGate: webapps/dacomasy/www/system/dacomasy.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 *
 * @todo Add field creation, validation, and update code for ModulePermissions.
 * @todo Find and fix all message that need to be made multi-lingual
 * @todo Add missing error handling (setting last error).
 * @todo Make sure of extended error information system.
 * @todo Write better comments documenting internal function workings.
 * @todo Cleanup and debug code.
 * @todo Secure code.
 * @todo Make sure all fields have thier own styles.
 * @todo Cleanup HTML, CSS, and JavaScript.
 * @todo Make sure call links and redirecting JavaScript code includes the session id number.
 * @todo Finish the XML-RPC server.  Need a XML-RPC client to test against.
 *
 * @tutorial Dacomasy.pkg
 */

$ByRefNull = NULL;

/**#@+ @ignore */

// Pre-initialization, this is for sanity and security sake.
require_once('system/preinit.inc');

// Resource Constans and Language Nutural Resources
require_once('system/res/errors.inc');
require_once('system/res/labels.inc');
require_once('system/res/messages.inc');
require_once('system/res/version.info.inc');

// Libraries
require_once('system/lib/base.inc');
require_once('system/lib/dbengine.inc');
require_once('system/lib/module.inc');
require_once('system/lib/fields.inc');
require_once('system/lib/record.inc');
require_once('system/lib/interface.inc');

// Tags
foreach (glob('system/tags/*.inc') as $tagclass) require_once($tagclass);

// Initialization

// Configuration Defautls
require_once('system/config.inc');

// Locales
$Dacomasy_Locale = $Dacomasy_Language . '/' . $Dacomasy_Region;
$Dacomasy_ResBase = 'system/res/' . $Dacomasy_Locale;

// Language resources
require_once($Dacomasy_ResBase . '/errors.inc');
require_once($Dacomasy_ResBase . '/labels.inc');
require_once($Dacomasy_ResBase . '/messages.inc');
require_once($Dacomasy_ResBase . '/version.info.inc');

if (isset($Dacomasy_AuthDB_Schema) === FALSE) {
	DacomasySetLastError(__DACOMASY_ERROR_FAILAUTHCONFIG);
	die (DacomasyGetLastErrorMsg());
}

require_once('system/userauth.inc');

/**#@-*/

?>