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
 * Preinitializes Dacomasy and Prevents certain security problems...
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Base
 * @version $SixXGate: webapps/dacomasy/www/system/preinit.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

/////////////////////////////////////////////////////////////////////////////
// Configuration
/////////////////////////////////////////////////////////////////////////////

// A few ideal settings for PHP, If they fail, the rest of this file is
// a backup process to simulate some of these changes.
@ini_set('register_globals', '0');
@ini_set('magic_quotes_gpc', '0');
@ini_set('magic_quotes_runtime', '0');

// Session control (has no backup)
@ini_set('session.use_cookies', '0');
@ini_set('session.use_only_cookies', '0');


/////////////////////////////////////////////////////////////////////////////
// Security
/////////////////////////////////////////////////////////////////////////////

// Unset all variables that may be registered due to register_globals
foreach ($_ENV as $szKey => $szValue) unset($$szKey);
foreach ($_GET as $szKey => $szValue) unset($$szKey);
foreach ($_POST as $szKey => $szValue) unset($$szKey);
foreach ($_COOKIE as $szKey => $szValue) unset($$szKey);
foreach ($_SERVER as $szKey => $szValue) unset($$szKey);
foreach ($_REQUEST as $szKey => $szValue) unset($$szKey); // FIXME: Is this needed?

/////////////////////////////////////////////////////////////////////////////
// Behavior
/////////////////////////////////////////////////////////////////////////////

// Disable Magic Quote Runtime...  If any idiot has this enabled on thier
// server...  Well... You know what to do.
set_magic_quotes_runtime (0);

// Unquote all request variables if magic quotes is enables
if (get_magic_quotes_gpc() == 1){
	foreach ($_GET as $szKey => $szValue) $_GET[$szKey] = stripslashes($szValue);
	foreach ($_POST as $szKey => $szValue) $_POST[$szKey] = stripslashes($szValue);
	foreach ($_COOKIE as $szKey => $szValue) $_COOKIE[$szKey] = stripslashes($szValue);
}

// Alter image type to use based on user-agent.
if (preg_match('/^Mozilla\/([0-9]).[0-9]/i', $_SERVER['HTTP_USER_AGENT'], $MozVer)) {
	if ($MozVer[1] > 4) $ImageExt = 'png';
	else $ImageExt = 'gif';
} else {
	if (preg_match('/Opera/i', $_SERVER['HTTP_USER_AGENT'])) $ImageExt = 'png';
	else $ImageExt = 'gif';
}


?>
