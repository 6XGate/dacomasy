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
 * @version $SixXGate: webapps/dacomasy/www/changepwd.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 */

/** @ignore */
require_once('system/dacomasy.inc');

// We need a few basic variables.
$ModuleFilename = $_GET['mod'];
$PanelIndex = $_GET['pan'];
$RecordIndex = $_GET['index'];
if (isset($_GET['place'])) $PlaceValue = $_GET['place']; else $PlaceValue = NULL;

$module = DacomasyLoadModule($ModuleFilename);

$Action = @$_POST['action'];
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html dir="ltr" lang="en">
<head>
	<title><?php printf ($__dacomasy__LABEL_res[__DACOMASY_LABEL_APPVERSION] ,$ApplicationVersionRes['locale']['Name'], $ApplicationVersionRes['locale']['Version']); ?></title>
	<link href="style/style.css" rel="stylesheet" type="text/css">
	<link href="style/form.css" rel="stylesheet" type="text/css">
</head>
<body>
<?php
switch ($Action) {
// Confirmed Delete //////////////////////////////////////////////////////////////////////////////////////
case 'ok':
	$IsValid = TRUE;
	$FieldSet = DacomasyGetStructure($module, $PanelIndex);
	for ($f = 0; $f < count($FieldSet); $f++) {
		if ($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_PASSWORD) {
			$DacomasyField[DACOMASY_FIELDTYPE_PASSWORD]->GetPostValues($FieldSet[$f], $Values);
			if ($DacomasyField[DACOMASY_FIELDTYPE_PASSWORD]->ValidateValues($FieldSet[$f], $Values, $InvalidMessage) === FALSE) {
				$IsValid = FALSE;
			} else {
				$DacomasyField[DACOMASY_FIELDTYPE_PASSWORD]->PrepareValues($FieldSet[$f], $Values);
			}
			if ($IsValid === FALSE) { ?>
				<script><!--
					parent.frames.DacomasyTitle.location = 'title.php?title=<?php echo urlencode($module['Panels'][$PanelIndex]['Name'] . ' - ' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_DELRECORD]); ?>&<?php echo DacomasySID(); ?>'
					parent.frames.DacomasyFunctions.location = 'functions.php?mode=none&<?php echo DacomasySID(); ?>';
				//--></script>
				<form action="changepwd.php?mod=<?php echo urlencode($ModuleFilename); ?>&amp;pan=<?php echo $PanelIndex; ?>&amp;index=<?php echo urlencode($RecordIndex); ?>&amp;<?php echo DacomasySID(); ?>" method="post"><?php
					echo $DacomasyField[DACOMASY_FIELDTYPE_PASSWORD]->GenerateField ($FieldSet[$f], $Values = NULL);
				?><button name="action" value="ok"><img src="images/ok.<?php echo $ImageExt; ?>" alt=""><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_OK]; ?></button><button name="action" value="cancel"><img src="images/cancel.<?php echo $ImageExt; ?>" alt=""><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_CANCEL]; ?></button>
				</form>
<?php		} else {
				if (DacomasyChangeRecordPassword(&$module, $PanelIndex, $RecordIndex, $Values[ $FieldSet[$f]['Name'] ]) === FALSE) {
					echo '<p>' . /* $__dacomasy__MSG_res[__DACOMASY_MSG_DELFAILED] . */ 'Failed:' . DacomasyGetLastErrorMsg() . '</p>';
				} else {
					echo '<p>' . /* $__dacomasy__MSG_res[__DACOMASY_MSG_DELSUCCESS] . */ 'Success</p>';
				} ?><p><button type="reset" onclick="parent.frames.DacomasyPanel.location = 'list.php?mod=<?php echo $ModuleFilename; ?>&amp;pan=<?php echo $PanelIndex; ?>&amp;<?php echo DacomasySID(); ?>'"><img src="images/ok.<?php echo $ImageExt; ?>" alt=""><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_OK]; ?></button></p><?php
			}
		}
	}
	

break;
// Cancelled Delete //////////////////////////////////////////////////////////////////////////////////////
case 'cancel': ?>
<script type="text/javascript"><!--
	window.location = "list.php?mod=<?php echo $ModuleFilename; ?>&pan=<?php echo $PanelIndex; ?>&<?php echo DacomasySID(); ?>"
//--></script>
<?php	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
default: ?>
	<script><!--
		parent.frames.DacomasyTitle.location = 'title.php?title=<?php echo urlencode($module['Panels'][$PanelIndex]['Name'] . ' - ' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_DELRECORD]); ?>&<?php echo DacomasySID(); ?>'
		parent.frames.DacomasyFunctions.location = 'functions.php?mode=none&<?php echo DacomasySID(); ?>';
	//--></script>
	<form action="changepwd.php?mod=<?php echo urlencode($ModuleFilename); ?>&amp;pan=<?php echo $PanelIndex; ?>&amp;index=<?php echo urlencode($RecordIndex); ?>&amp;<?php echo DacomasySID(); ?>" method="post"><?php
	$FieldSet = DacomasyGetStructure($module, $PanelIndex);
	for ($f = 0; $f < count($FieldSet); $f++) {
		if ($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_PASSWORD) {
			echo $DacomasyField[DACOMASY_FIELDTYPE_PASSWORD]->GenerateField ($FieldSet[$f], $Values = NULL);
		}
	}
	?><button name="action" value="ok"><img src="images/ok.<?php echo $ImageExt; ?>" alt=""><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_OK]; ?></button><button name="action" value="cancel"><img src="images/cancel.<?php echo $ImageExt; ?>" alt=""><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_CANCEL]; ?></button>
	</form>
<?php } ?>
</body>
