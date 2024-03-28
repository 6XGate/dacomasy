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
 * Lists the contents of a panel
 * 
 * @package Dacomasy
 * @subpackage WebClient
 * @version $SixXGate: webapps/dacomasy/www/move.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 */

/** @ignore */
require_once('system/dacomasy.inc');

// We need a few basic variables.
$ModuleFilename = $_GET['mod'];
$PanelIndex = $_GET['pan'];
$PlaceIndex = $_GET['place'];
$Action = $_GET['action'];
if (isset($_GET['place'])) $PlaceValue = $_GET['place']; else $PlaceValue = NULL;

$module = DacomasyLoadModule($ModuleFilename);

?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html dir="ltr" lang="en">
<head>
	<title><?php printf ($__dacomasy__LABEL_res[__DACOMASY_LABEL_APPVERSION] ,$ApplicationVersionRes['locale']['Name'], $ApplicationVersionRes['locale']['Version']); ?></title>
	<link href="style/style.css" rel="stylesheet" type="text/css">
</head>
<body>
<?php
switch ($Action) {
// Move Up ///////////////////////////////////////////////////////////////////////////////////////////////
case 'up': 
	if (DacomasyMoveRecordUp($module, $PanelIndex, $PlaceIndex) === FALSE) { ?>
	<p><?php echo $__dacomasy__MSG_res[__DACOMASY_MSG_MOVEFAILED]; ?></p>
	<script><!--
		parent.frames.DacomasyTitle.location = 'title.php?title=<?php echo urlencode($module['Panels'][$PanelIndex]['Name'] . ' - ' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_MOVEECORD]); ?>&<?php echo DacomasySID(); ?>'
		parent.frames.DacomasyFunctions.location = 'functions.php?mode=none&<?php echo DacomasySID(); ?>';
	//--></script>
	<p><button type="reset" onclick="parent.frames.DacomasyPanel.location = 'list.php?mod=<?php echo $ModuleFilename; ?>&amp;pan=<?php echo $PanelIndex; ?>&amp;<?php echo DacomasySID(); ?>'"><img src="images/ok.<?php echo $ImageExt; ?>" alt=""><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_OK]; ?></button></p>
<?php } else { ?>
		<script type="text/javascript"><!--
			window.location = "list.php?mod=<?php echo $ModuleFilename; ?>&pan=<?php echo $PanelIndex; ?>&<?php echo DacomasySID(); ?>"
		//--></script>
<?php }
break;
// Move Down /////////////////////////////////////////////////////////////////////////////////////////////
case 'down':
	if (DacomasyMoveRecordDown($module, $PanelIndex, $PlaceIndex) === FALSE) {?>
	<p><?php echo $__dacomasy__MSG_res[__DACOMASY_MSG_MOVEFAILED]; ?></p>
	<script><!--
		parent.frames.DacomasyTitle.location = 'title.php?title=<?php echo urlencode($module['Panels'][$PanelIndex]['Name'] . ' - ' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_MOVEECORD]); ?>&<?php echo DacomasySID(); ?>'
		parent.frames.DacomasyFunctions.location = 'functions.php?mode=none&<?php echo DacomasySID(); ?>';
	//--></script>
	<p><button type="reset" onclick="parent.frames.DacomasyPanel.location = 'list.php?mod=<?php echo $ModuleFilename; ?>&amp;pan=<?php echo $PanelIndex; ?>&amp;<?php echo DacomasySID(); ?>'"><img src="images/ok.<?php echo $ImageExt; ?>" alt=""><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_OK]; ?></button></p>
<?php } else { ?>
		<script type="text/javascript"><!--
			window.location = "list.php?mod=<?php echo $ModuleFilename; ?>&pan=<?php echo $PanelIndex; ?>&<?php echo DacomasySID(); ?>"
		//--></script>
<?php }
break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
} ?>
</body>