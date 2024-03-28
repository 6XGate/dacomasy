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
 * @version $SixXGate: webapps/dacomasy/www/list.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 */

/** @ignore */
require_once('system/dacomasy.inc');

	// We need the module filename and panel index
	$ModuleFilename = $_GET['mod'];
	$PanelNum = $_GET['pan'];
	$module = DacomasyLoadModule($ModuleFilename);
	$RecordSet = DacomasyListRecords($module, $PanelNum);
	
	$PlaceField = 0;
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html dir="ltr" lang="en">
<head>
	<title><?php printf ($__dacomasy__LABEL_res[__DACOMASY_LABEL_APPVERSION] ,$ApplicationVersionRes['locale']['Name'], $ApplicationVersionRes['locale']['Version']); ?></title>
	<link href="style/style.css" rel="stylesheet" type="text/css">
	<link href="style/lists.css" rel="stylesheet" type="text/css">
	<script><!--
		// Sets up other frames for this page
		parent.frames.DacomasyTitle.location = 'title.php?title=<?php echo urlencode($module['Panels'][$PanelNum]['Name']); ?>&<?php echo DacomasySID(); ?>';
		parent.frames.DacomasyFunctions.location = 'functions.php?mode=list&<?php echo DacomasySID(); ?>';
	//--></script>
</head>
<body>
<?php
	if ($module === FALSE) {
		echo '<p>Dacomasy Error: ' . DacomasyGetLastErrorMsg() . '</p>';
		echo '<p>Extended Error Information:</p>';
		echo '<blockquote>' . DacomasyGetExtendedErrorMsg() . '</blockquote>';
		echo '</body></html>';
		exit();
	}
?>

	<p><?php
		if ($RecordSet == FALSE) echo htmlentities(DacomasyGetLastErrorMsg());
	?></p>
	<table>
		<thead><tr><?php
			for ($i = 1; $i < count($RecordSet['Fields']); $i++) {
				if ($RecordSet['Fields'][$i]['Type'] != DACOMASY_FIELDTYPE_SUPERSORT)
					echo '<th id="_FIELD_' . $RecordSet['Fields'][$i]['Name'] . '">' . htmlentities($RecordSet['Fields'][$i]['Label']) . '</th>';
			}
		?><th class="functionCol">Functions</th></tr></thead>
		<tbody><?php
			for ($r = 0; $r < @count($RecordSet['Records']); $r++) { ?>
				<tr>
<?php			for ($i = 1; $i < count($RecordSet['Fields']); $i++) {
					switch($RecordSet['Fields'][$i]['Type']) {
					case DACOMASY_FIELDTYPE_SUPERSORT:
						$PlaceField = $i;
						break;
					case DACOMASY_FIELDTYPE_LINK:
						echo '<td><a href="' . $RecordSet['Records'][$r][$i]['HRef'] . '" target="_blank">' . htmlentities($RecordSet['Records'][$r][$i]['Value']) . '</a></td>';
						break;
					default:
						echo '<td>' . htmlentities($RecordSet['Records'][$r][$i]['Value']) . '</td>';
					}
				} ?>
				<td>
					<a href="edit.php?mod=<?php echo urlencode($ModuleFilename); ?>&amp;pan=<?php echo $PanelNum; ?>&amp;index=<?php echo urlencode($RecordSet['Records'][$r][0]['Value']); ?>&amp;<?php echo DacomasySID(); ?>" class="function" title="<?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_EDIT]; ?>"><img src="images/edit.<?php echo $ImageExt; ?>" alt="<?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_EDIT]; ?>"></a>
					<a href="delete.php?mod=<?php echo urlencode($ModuleFilename); ?>&amp;pan=<?php echo $PanelNum; ?>&amp;index=<?php echo urlencode($RecordSet['Records'][$r][0]['Value']); ?><?php if ($PlaceField > 0) echo '&amp;place=' . urlencode($RecordSet['Records'][$r][$PlaceField]['Value']); ?>&amp;<?php echo DacomasySID(); ?>" class="function" title="<?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_DEL]; ?>"><img src="images/delete.<?php echo $ImageExt; ?>" alt="<?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_DEL]; ?>"></a>
<?php				if ($RecordSet['Functions']['Password']) 
						echo'<a href="changepwd.php?mod=' . urlencode($ModuleFilename) . '&amp;pan=' . $PanelNum . '&amp;index=' . urlencode($RecordSet['Records'][$r][0]['Value']) . '&amp;' . DacomasySID() . '" class="function" title="' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_CHANGEPWD] . '"><img src="images/changepwd.' . $ImageExt . '" alt="' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_CHANGEPWD] . '"></a>';
					if ($RecordSet['Functions']['SuperSort']) {
						if ($r > 0) echo'<a href="move.php?mod=' . urlencode($ModuleFilename) . '&amp;pan=' . $PanelNum . '&amp;place=' . urlencode($RecordSet['Records'][$r][$PlaceField]['Value']) . '&amp;action=up&amp;' . DacomasySID() . '" class="function" title="' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_MOVEUP] . '"><img src="images/moveup.' . $ImageExt . '" alt="' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_MOVEUP] . '"></a>';
						else echo '<img src="images/blank.gif" alt="">';
						if ($r < count($RecordSet['Records']) - 1) echo'<a href="move.php?mod=' . urlencode($ModuleFilename) . '&amp;pan=' . $PanelNum . '&amp;place=' . urlencode($RecordSet['Records'][$r][$PlaceField]['Value']) . '&amp;action=down&amp;' . DacomasySID() . '" class="function" title="' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_MOVEDN] . '"><img src="images/movedn.' . $ImageExt . '" alt="' . $__dacomasy__LABEL_res[__DACOMASY_LABEL_MOVEDN] . '"></a>';
						else echo '<img src="images/blank.gif" alt="">';
					} ?>
				</td></tr>
<?php		}
		?></tbody>
	</table>
	<p><button class="realfunction" id="DACO_addButton" type="reset" onclick="window.location='add.php?mod=<?php echo urlencode($ModuleFilename); ?>&amp;pan=<?php echo $PanelNum; ?>&amp;<?php echo DacomasySID(); ?>'"></button></p>
</body>
</html>

