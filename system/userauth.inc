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
 * Authenicates the user and controls session secutiry.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Base
 * @version $SixXGate: webapps/dacomasy/www/system/userauth.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

// session_name('Dacomasy Session ID');
if (isset($_GET['sid'])) {
	session_id(strip_tags($_GET['sid']));
	session_start();
	
	foreach ($_SESSION as $szKey => $szValue) unset($$szKey);
	
	if (isset($_SESSION['ip']) === TRUE) $CIP = $_SESSION['ip']; else DacomasyReturnToLogin('This session doesn\'t have an address.');
	if ($CIP != $_SERVER['REMOTE_ADDR']) DacomasyReturnToLogin('The your computer\'s address does not match this session.');

	if (isset($_SESSION['usr']) === TRUE) $Usr = $_SESSION['usr']; else DacomasyReturnToLogin('This session doesn\'t have a username!');
	if (isset($_SESSION['pwd']) === TRUE) $Pwd = $_SESSION['pwd'];
} else {
	if (isset($_POST['usr']) === TRUE) $Usr = $_POST['usr']; else return;
	if (isset($_POST['pwd']) === TRUE) $Pwd = $_POST['pwd'];
	session_start();
}

// Security... Unset session variables that may have become global.
foreach ($_SESSION as $szKey => $szValue) unset($$szKey);

// Connect to the database server, or open the database.
$DB = new DacoDBConnection($Dacomasy_AuthDB_Hostname, $Dacomasy_AuthDB_Username, $Dacomasy_AuthDB_Password);
if ($DB->Connect() === FALSE) DacomasyReturnToLogin('Connection Error.');

// Select the catalog
if ($DB->SelectCatalog ($Dacomasy_AuthDB_Catalog) === FALSE) DacomasyReturnToLogin('Invalid Catalog');

// Get the user record
$szQuery = 'SELECT * FROM ' . DacoDBConnection::EscapeString($Dacomasy_AuthDB_Schema) . ' WHERE username="' . DacoDBConnection::EscapeString($Usr) . '"';
$oResult = $DB->Query($szQuery);
if ($oResult->Error() === TRUE) DacomasyReturnToLogin('Query Error.');
if ($oResult->RowCount() != 1) DacomasyReturnToLogin('Invalid Username or Password.');

$UserRecord = $oResult->FetchNextRecord();
$PasswordMD5 = md5($Pwd);

if (isset($UserRecord['password']) === FALSE) DacomasyReturnToLogin('No Password Field In Table...');
if ($PasswordMD5 != $UserRecord['password']) DacomasyReturnToLogin('Invalid Username or Password.');

$_SESSION['ip'] = $_SERVER['REMOTE_ADDR'];
$_SESSION['usr'] = $Usr;
$_SESSION['pwd'] = $Pwd;

?>