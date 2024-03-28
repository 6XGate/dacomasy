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
 * Contains the systems configuration settings.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Base
 * @version $SixXGate: webapps/dacomasy/www/system/config.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

/////////////////////////////////////////////////////////////////////////////
// Locale
/////////////////////////////////////////////////////////////////////////////
// These are language and dialect settings

// Spoken Language
$Dacomasy_Language = 'en';
// Regional Dialect
$Dacomasy_Region = 'US';

/////////////////////////////////////////////////////////////////////////////
// General Settings
/////////////////////////////////////////////////////////////////////////////
// These are generalized settings

// Time format
/////////////////////////////////////////////////////////////////////////////
// This can be set to DACOMASY_TIMEMODE_12HOUR or DACOMASY_TIMEMODE_24HOUR
$Dacomasy_TimeMode = DACOMASY_TIMEMODE_12HOUR;

// Database Management System
/////////////////////////////////////////////////////////////////////////////
// This can be set to any of the following database management systems.
// DACOMASY_DBENGINE_MYSQL	- MySQL
// DACOMASY_DBENGINE_MSSQL	- mSQL					NOT READY AT ALL
// DACOMASY_DBENGINE_MSQL	- Microsoft SQL Server	Experimental
// DACOMASY_DBENGINE_PGSQL	- PostgreSQL			Experimental
// DACOMASY_DBENGINE_SQLITE	- SQLite				Experimental
$Dacomasy_DBEngine = DACOMASY_DBENGINE_MYSQL;

/////////////////////////////////////////////////////////////////////////////
// Authentication
/////////////////////////////////////////////////////////////////////////////
// Gives information about where to find the authentication shema.  Uses the
// same database management system as the rest of Dacomasy.

$Dacomasy_AuthDB_Hostname = 'localhost';
$Dacomasy_AuthDB_Username = 'mobicon';
$Dacomasy_AuthDB_Password = '8hoEc0eDroep';
$Dacomasy_AuthDB_Catalog = 'mobicon';
$Dacomasy_AuthDB_Schema = 'thepower';

?>
