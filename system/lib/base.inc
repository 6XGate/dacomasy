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
 * Contains basic routines and constants.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Base
 * @version $SixXGate: webapps/dacomasy/www/system/lib/base.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

/**#@+ Time Format */

/** 24-hour Time Format */	define ('DACOMASY_TIMEMODE_24HOUR',							0x0, TRUE);
/** 12-hour Time Format */	define ('DACOMASY_TIMEMODE_12HOUR',							0x1, TRUE);
/** Use Seconds */			define ('DACOMASY_TIMEMODE_SECONDS',						0x2, TRUE);

/**#@-*/

/**
 * Converts a string into a boolean based on Dacomasy boolean attribute selections.
 *
 * DacomasyGetBoolean returns TRUE or FALSE depending on the value of the string
 * $BoolString.  "T", "TRUE", "Y", "YES", and "1" will return TRUE while "F", "FALSE",
 * "N", "NO", and "0" will return FALSE.  This function is not case-sensitive.
 *
 * @param string A string that represents a boolean value.
 * @param boolean The default return value if one can't be determind.
 * @return boolean The true or false value of the boolean string.
 */
function DacomasyGetBoolean ($BoolString, $Default = FALSE) {
	if (preg_match('/^(t(rue)?|y(es)?|1)$/', $BoolString)) return TRUE;
	if (preg_match('/^(f(alse)?|n(o)?|0)$/', $BoolString)) return FALSE;
	return $Default;
}

// Last Dacomasy Error
$__dacomasy__ERROR = __DACOMASY_ERROR_SUCCESSFUL;
$__dacomasy__EXTERROR = '';
$__dacomasy__ERRARRAY = array();

/**
 * Returns that last Dacomasy error number that occurred.
 * 
 * @return number The number for the last Dacomasy error.
 */
function DacomasyGetLastError() { return $GLOBALS['__dacomasy__ERROR']; }

/**
 * Returns a message that represents that last Dacomasy error that occurred.
 *
 * @return string A message describing that last Dacomasy error.
 */
function DacomasyGetLastErrorMsg() { return $GLOBALS['__dacomasy__ERROR_res'][$GLOBALS['__dacomasy__ERROR']]; }

/**
 * Sets the last Dacomasy error that occurred when a function failed.
 *
 * Sets the error number for an error that has occurred in Dacomasy.  Functions
 * should call this upon exiting to indicate an error that occurred if the
 * function indicates an error.  DacomasySetLastError also resets the extended
 * error message to an empty string it to must be set at the end with
 * DacomasySetExtendedErrorMsg.
 *
 * @param number A Dacomasy error number.
 * @return number The number for the last Dacomasy error.
 * @see DacomasySetExtendedErrorMsg()
 */
function DacomasySetLastError( $newError) {
	$lastError = $GLOBALS['__dacomasy__ERROR'];
	$GLOBALS['__dacomasy__ERROR'] = $newError;
	return $lastError;
}

/**
 * Sets a string that contains additional error information when an error occurrs.
 *
 * DacomasySetExtendedErrorMsg is used to include additional information about
 * an error that occurred.  This function must be called after the
 * DacomasySetLastError since it will reset the Extended Error Message.
 *
 * @param string The additional information or message about the error.
 * @return void
 * @see DacomasySetLastError()
 */
function DacomasySetExtendedErrorMsg($szExtErrorMsg) {
	$GLOBALS['__dacomasy__EXTERROR'] = $szExtErrorMsg;
}

/**
 * Gets extended the extended error message for an error that has occurred.
 *
 * @return string The message containing additional informatoin about the error.
 */
function DacomasyGetExtendedErrorMsg() {
	return $GLOBALS['__dacomasy__EXTERROR'];
}

/**
 * Dacomasy's Custom Error Handler to help trap error messages to use as an extended error message.
 *
 * @param number The numeric type of the error that occurred.
 * @param string The message about the error that occurred.
 * @param string The file the error occurred in.
 * @param number The line on which the error occurred.
 * @return void
 * @see DacomasySetExtendedErrorMsg()
 */
function DacomasyErrorHandler($errno, $errstr, $errfile, $errline) {
	global $__dacomasy__ERRARRAY;
	switch ($errno) {
	case E_WARNING:
	case E_NOTICE:
		DacomasyArrayPush($__dacomasy__ERRARRAY, $errstr);
		break;
	}
	return;
}

/**
 * Returns the currently caught PHP errors and clears the CaughtErrors array.
 *
 * @return array An array of all errors caught by Dacomasy.
 */
function DacomasyGetCaughtErrors() {
	global $__dacomasy__ERRARRAY;
	$ret = $__dacomasy__ERRARRAY;
	$__dacomasy__ERRARRAY = array();
	return $ret;
}

/**
 * Returns a session ID part for URLs.
 *
 * @return string The session ID formatted for URLs, e.g. sid\=39d9fsd9f0s90df980dds.
 */
function DacomasySID() {
	return 'sid=' . urlencode(session_id());
}

/**
 * Returns the user to the login screen when a user authentication error occurs.
 *
 * @param string An error message to display on the login screen.
 * @return void
 */
function DacomasyReturnToLogin($szErrorMsg = NULL) {
echo '
	<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd"><html dir="ltr" lang="en">
	<head><title>Returning To Login</title><script type="text/javascript"><!-- 
		// Frame Buster
		if (self.parent) if (self.parent.frames.length != 0) {
			self.parent.location = "index.php' . (($szErrorMsg != NULL) ? ('?ErrorMsg=' . urlencode($szErrorMsg)) : ('')) . '";
		} else {
			window.location = "index.php' . (($szErrorMsg != NULL) ? ('?ErrorMsg=' . urlencode($szErrorMsg)) : ('')) . '";
		}
		// Make sure we have a DOM Level 1 compliant browser...
		if (document.getElementById) {} else {
			window.location = "minimumreq.html"
		}
	//--></script></head><body></body></html>
	';
exit();
}

/**
 * Pushes an entry onto an array, or makes the first entry if the variable isn't an array.
 *
 * @param mixed A variable that is an array or will become an array.
 * @return boolean Is true on success or false on error.
 */
function DacomasyArrayPush(&$Array, &$Value) {
//	if (is_array($Array) === TRUE) {
		array_push($Array, $Value);
//	} else {
//		$Array = array($Value);
//	}
}

?>
