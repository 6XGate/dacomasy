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
 * Displays the title of the current function and panel
 * 
 * @package Dacomasy
 * @subpackage WebClient
 * @version $SixXGate: webapps/dacomasy/www/title.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
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
	<title><?php printf ($__dacomasy__LABEL_res[__DACOMASY_LABEL_APPVERSION] ,$ApplicationVersionRes['locale']['Name'], $ApplicationVersionRes['locale']['Version']); ?></title>
	<link href="style/title.css" rel="stylesheet" type="text/css">
	<script><!--
		function logout() {
			if (self.parent) if (self.parent.frames.length != 0) {
				self.parent.location = "logout.php?<?php echo DacomasySID(); ?>";
			} else {
				window.location = "logout.php?<?php echo DacomasySID(); ?>";
			}
		}
	//--></script>
</head>
<body>
<button type="reset" onclick="window.open('about.php?<?php echo DacomasySID(); ?>','about','minimizable=no,modal=no,dialog=yes,width=600,height=400,toolbar=no,scrollbars=no,menubar=no,status=no,resizable=no,location=no,directories=no,dependent=yes,channelmode=no');">About Dacomasy...</button>
<button type="reset" onclick="logout();">Logout</button>
<?php
	if (isset($_GET['title'])) {
		echo '<p>' . $_GET['title'] . '</p>';
	} else {
		echo '<p>' . sprintf ($__dacomasy__LABEL_res[__DACOMASY_LABEL_APPVERSION] ,$ApplicationVersionRes['locale']['Name'], $ApplicationVersionRes['locale']['Version']) . '</p>';
	}
?>
</body>
</html>
