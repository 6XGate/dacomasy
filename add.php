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
 * Gathers and inserts a record into a panel
 * 
 * @package Dacomasy
 * @subpackage WebClient
 * @version $SixXGate: webapps/dacomasy/www/add.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 */

/** @ignore */
require_once('system/dacomasy.inc');
	
	$ModuleFilename = $_GET['mod'];
	$PanelIndex = $_GET['pan'];
	$module = DacomasyLoadModule($ModuleFilename);
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html dir="ltr" lang="en">
<head>
	<title><?php printf ($__dacomasy__LABEL_res[__DACOMASY_LABEL_APPVERSION] ,$ApplicationVersionRes['locale']['Name'], $ApplicationVersionRes['locale']['Version']); ?></title>
	<link href="style/style.css" rel="stylesheet" type="text/css">
	<link href="style/form.css" rel="stylesheet" type="text/css">
	<!-- Addin Skins -->
	<link rel="stylesheet" type="text/css" media="all" href="addins/calendar/calendar-system.css">
	<link rel="stylesheet" type="text/css" media="all" href="addins/timepicker/skin/system.css">
	<!-- Main Calendar Program -->
	<script type="text/javascript" src="addins/calendar/calendar.js"></script>
	<script type="text/javascript" src="addins/calendar/calendar-setup.js"></script>
	<!-- Calendar Language-->
	<script type="text/javascript" src="addins/calendar/lang/calendar-<?php echo $Dacomasy_Language; ?>.js"></script>
	<!-- HTML Area initialization -->
	<script type="text/javascript"><!--
		_editor_url = "addins/editor/";
		_editor_lang = "<?php echo $Dacomasy_Language; ?>";
	//--></script>
	<script type="text/javascript" src="addins/editor/htmlarea.js"></script>
	<script type="text/javascript"><!--
		HTMLArea.loadPlugin("ContextMenu");
		HTMLArea.loadPlugin("TableOperations");
		HTMLArea.loadPlugin("SpellChecker");
	//--></script>
	<script type="text/javascript" src="addins/timepicker/timepicker.js"></script>
	<script type="text/javascript" src="script/clearer.js"></script>
</head>
<body class="form">
<?php
	if (isset($_POST['DACO_action'])) $Action = $_POST['DACO_action']; else $Action = '';
	switch ($Action) {
	case 'okay':
		$Values = DacomasyGenerateValuesArray($module, $PanelIndex);
		$FieldSet = DacomasyGetStructure($module, $PanelIndex);
		if (DacomasyValidateForm($module, $PanelIndex, $Values, $Messages) === FALSE) {
			echo '<p id="InvalidForm">' . $__dacomasy__MSG_res[__DACOMASY_MSG_FORMINVALID] . '</p>';?>
			<script><!--
				parent.frames.DacomasyTitle.location = 'title.php?title=<?php echo urlencode($module['Panels'][$PanelIndex]['Name'] . ' - ' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_ADDRECORD]); ?>&<?php echo DacomasySID(); ?>'
				parent.frames.DacomasyFunctions.location = 'functions.php?mode=form&<?php echo DacomasySID(); ?>';
			//--></script>
<?php		echo DacomasyGenerateForm($module, $PanelIndex, $ModuleFilename, $Values, $Messages);
		} else {
			DacomasyPrepareValuesArray($module, $PanelIndex, $Values);
			if (DacomasyAddRecord($module, $PanelIndex, $Values) === FALSE) {
				echo '<p>' . $__dacomasy__MSG_res[__DACOMASY_MSG_ADDFAILED] . '</p>';
				echo '<p>' . DacomasyGetLastErrorMsg() . '</p>';
			} else {
				echo '<p>' . $__dacomasy__MSG_res[__DACOMASY_MSG_ADDSUCCESS] . '</p>';
			}?>
			<script><!--
				parent.frames.DacomasyTitle.location = 'title.php?title=<?php echo urlencode($module['Panels'][$PanelIndex]['Name'] . ' - ' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_ADDRECORD]); ?>&<?php echo DacomasySID(); ?>'
				parent.frames.DacomasyFunctions.location = 'functions.php?mode=none&<?php echo DacomasySID(); ?>';
			//--></script>
			<p><button type="reset" onClick="parent.frames.DacomasyPanel.location = 'list.php?mod=<?php echo $ModuleFilename; ?>&amp;pan=<?php echo $PanelIndex; ?>&amp;<?php echo DacomasySID(); ?>'"><img src="images/ok.<?php echo $ImageExt; ?>" alt=""><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_OK]; ?></button>&nbsp;&nbsp;&nbsp;&nbsp;<button type="reset" onClick="window.location='add.php?mod=<?php echo $ModuleFilename; ?>&amp;pan=<?php echo $PanelIndex; ?>&amp;<?php echo DacomasySID(); ?>'"><img src="images/addnew.<?php echo $ImageExt; ?>" alt=""><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_ADDNEW]; ?></button></p>
<?php		// TODO: Create and use the add record code to add the record...
		}
		break;
	case 'cancel':
		$Values = DacomasyGenerateValuesArray($module, $PanelIndex);
		$FieldSet = DacomasyGetStructure($module, $PanelIndex);
		
		for ($f = 0; $f < count($FieldSet); $f++) {
			if (($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_FILE) || ($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_PICTURE)) {
				if (strlen($Values[ $FieldSet[$f]['Name'] ]['filename'])) unlink( $Values[ $FieldSet[$f]['Name'] ]['filename'] );
			}
		}
		foreach ($_FILES as $File) {
			if ($File['error'] == 0) unlink($File['tmp_name']);
		}
		echo '<script type="text/javascript"><!--
				window.location = "list.php?mod=' . $ModuleFilename . '&pan=' . $PanelIndex . '&' . DacomasySID() . '";
			//--></script>';
		break;
	default:?>
		<script><!--
			parent.frames.DacomasyTitle.location = 'title.php?title=<?php echo urlencode($module['Panels'][$PanelIndex]['Name'] . ' - ' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_ADDRECORD]); ?>&<?php echo DacomasySID(); ?>'
			parent.frames.DacomasyFunctions.location = 'functions.php?mode=form&<?php echo DacomasySID(); ?>';
		//--></script>
<?php	echo DacomasyGenerateForm($module, $PanelIndex, $ModuleFilename);
	} // DACO_action
?>
</body>
</html>
