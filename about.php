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
 * Displays version information.
 * 
 * @package Dacomasy
 * @subpackage WebClient
 * @version $SixXGate: webapps/dacomasy/www/about.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 */

/** @ignore */
require_once('system/dacomasy.inc');
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html dir="ltr" lang="en">
<head>
	<title><?php echo sprintf($__dacomasy__LABEL_res[__DACOMASY_LABEL_ABOUT], $ApplicationVersionRes['locale']['Name']); ?></title>
	<link href="style/about.css" rel="stylesheet" type="text/css">
</head>
<body>
<?php
	echo '<p><strong>' . $ApplicationVersionRes['locale']['Name'] . '</strong></p>';
	echo '<p>' . $ApplicationVersionRes['locale']['Version'] . '</p>';
	echo '<p>' . $ApplicationVersionRes['locale']['Description'] . '</p>';
	echo '<p>' . $ApplicationVersionRes['locale']['Copyright'] . '</p>';
?>	<div><?php
		echo '<p><strong>' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_SYSINFO] . '</strong></p>';
		echo '<p><em>' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_SERVERSW] . '</em>' . $_SERVER['SERVER_SOFTWARE'] . '</p>';
		echo '<p><em>' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_SERVEROS] . '</em>' . PHP_OS . '</p>';
		echo '<p><em>' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_USERAGENT] . '</em>' . $_SERVER['HTTP_USER_AGENT'] . '</p>';
		echo '<p>' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_PHPVER] . PHP_VERSION . '</p>';
?>	</div>
	<p><button onclick="window.open('license.html','license','minimizable=yes,modal=no,dialog=no,width=600,height=400,toolbar=no,scrollbars=yes,menubar=no,status=no,resizable=yes,location=no,directories=no,dependent=yes,channelmode=no');"><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_LICENSE]; ?></button></p>
	<p><button onclick="window.close();"><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_CLOSE]; ?></button></p>
</body>
</html>
