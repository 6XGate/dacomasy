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
 * XML-RPC Server Script
 * 
 * @package Dacomasy
 * @subpackage XML-RPM-Server
 * @version $SixXGate: webapps/dacomasy/www/dacomasy.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 */

/** @ignore */
require_once('system/dacomasy.inc');

$ModList = DacomasyListModules();

	header("Content-Type: text/xml", true);
	header("Connection: close", true);

	function rpcTest($method_name, $params, $app_data) {
		$name = $param[0];
	
		return $GLOBALS['ModList'];
	}
	
	
	$szXML = $HTTP_RAW_POST_DATA;
	// $szXML = xmlrpc_encode_request('dacomasy.listmodules', null);
	
	$rRPCS = xmlrpc_server_create();
	xmlrpc_server_register_method($rRPCS, "dacomasy.listmodules", "rpcTest");

	echo xmlrpc_server_call_method($rRPCS, $szXML, $app_data);

	xmlrpc_server_destroy($rRPCS);
?>
