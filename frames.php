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
 * Presents the Dacomasy Interface/Frames
 * 
 * @package Dacomasy
 * @subpackage WebClient
 * @version $SixXGate: webapps/dacomasy/www/frames.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 */

/** @ignore */
require_once('system/dacomasy.inc');
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Frameset//EN" "http://www.w3.org/TR/html4/frameset.dtd">
<html dir="ltr" lang="en">
<head>
	<title><?php printf ($__dacomasy__LABEL_res[__DACOMASY_LABEL_APPVERSION] ,$ApplicationVersionRes['locale']['Name'], $ApplicationVersionRes['locale']['Version']); ?></title>
	<!-- frame buster - code by Gordon McComb -->
	<script type="text/javascript"><!-- 
		// Frame Buster
		if (self.parent) if (self.parent.frames.length != 0) self.parent.location = document.location + '&<?php echo DacomasySID(); ?>';
		// Make sure we have a DOM Level 1 compliant browser...
		if (document.getElementById) {} else {
			window.location = "minimumreq.html"
		}
	//--></script>
</head>
<!-- frames -->
<frameset cols="25%,*" framespacing="0" frameborder="0" style="background-color: ThreedFace;">
	<frame src="panels.php?<?php echo DacomasySID(); ?>" name="DacomasyModules" id="DacomasyModules" frameborder="0" scrolling="Auto" noresize marginwidth="0" marginheight="0">
	<frameset rows="25,*,35" framespacing="0" frameborder="0" style="background-color: ThreedFace;">
		<frame src="title.php?<?php echo DacomasySID(); ?>" name="DacomasyTitle" id="DacomasyTitle" frameborder="0" scrolling="No" noresize marginwidth="0" marginheight="0">
		<frame src="blank.html" name="DacomasyPanel" id="DacomasyPanel" frameborder="0" scrolling="Auto" noresize marginwidth="0" marginheight="0">
		<frame src="functions.php?<?php echo DacomasySID(); ?>" name="DacomasyFunctions" id="DacomasyFunctions" frameborder="0" scrolling="No" noresize marginwidth="0" marginheight="0">
	</frameset>
</frameset>
<noframes>
	<p>Dacomasy requires a browser that supports frames.</p>
</noframes>
</html>
