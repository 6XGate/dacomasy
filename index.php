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
 * Presents the form to logon to Dacomasy.
 * 
 * @package Dacomasy
 * @subpackage WebClient
 * @version $SixXGate: webapps/dacomasy/www/index.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
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
	<link href="style/style.css" rel="stylesheet" type="text/css">
	<!-- frame buster - code by Gordon McComb -->
	<script type="text/javascript"><!-- 
		// Frame Buster
		if (self.parent) if (self.parent.frames.length != 0) self.parent.location = document.location;
		// Make sure we have a DOM Level 1 compliant browser...
		if (document.getElementById) {} else {
			window.location = "minimumreq.html"
		}
	//--></script>
</head>
<body>
<p id="dialogHeader"><?php printf ($__dacomasy__LABEL_res[__DACOMASY_LABEL_APPVERSION] ,$ApplicationVersionRes['locale']['Name'], $ApplicationVersionRes['locale']['Version']); ?> - Login</p>
<?php if (isset($_GET['ErrorMsg'])) echo '<p>Error: ' . $_GET['ErrorMsg'] . '</p>'; ?>
<form action="frames.php" method="post">
	<p><label for="usr">Username:</label></p>
	<p><input type="text" name="usr" id="usr"></p>
	<p><label for="pwd">Password:</label></p>
	<p><input type="password" name="pwd" id="pwd"></p>
	<button type="submit"><img src="images/changepwd.<?php echo $ImageExt ;?>" alt="">Login</button>
</form>
</body>
</html>
