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
 * Lists installed modules and panels
 * 
 * @package Dacomasy
 * @subpackage WebClient
 * @version $SixXGate: webapps/dacomasy/www/panels.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 */

/** @ignore */
require_once('system/dacomasy.inc');

if (isset($_SESSION['time'])) $LastTime = $_SESSION['time']; else $LastTime = '';
$_SESSION['time'] = time();

$ModList = DacomasyListModules();
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html dir="ltr" lang="en">
<head>
	<title><?php printf ($__dacomasy__LABEL_res[__DACOMASY_LABEL_APPVERSION] ,$ApplicationVersionRes['locale']['Name'], $ApplicationVersionRes['locale']['Version']); ?></title>
	<link href="style/style.css" rel="stylesheet" type="text/css">
	<link href="style/lists.css" rel="stylesheet" type="text/css">
</head>
<body>
<table>
	<thead><th><?php echo $__dacomasy__LABEL_res[__DACOMASY_LABEL_PANELS]; ?></th></thead>
	<tbody>
<?php
	for ($i = 0; $i < count($ModList); $i++) {
		echo '<tr><td><span title="' . $ModList[$i]['Tooltip'] . '"><img src="images/module.' . $ImageExt . '" alt="" class="modpan">' . $ModList[$i]['Name'] . '</span></td></tr>';
		for ($p = 0; $p < count($ModList[$i]['Panels']); $p++) {
			echo '<tr><td><img src="images/blank.gif"><a href="list.php?mod=' . $ModList[$i]['Filename'] . '&amp;pan=' . $p . '&amp;' . DacomasySID() . '" target="DacomasyPanel" title="' . $ModList[$i]['Panels'][$p]['Tooltip'] . '"><img src="images/panel.' . $ImageExt . '" alt="" class="modpan">' . $ModList[$i]['Panels'][$p]['Name'] . '</a></td></tr>';
		}
	}
?>
	</tbody>
</table>
<?php
	echo '<p class="verinfo">' . $ApplicationVersionRes['locale']['Version'] . '</p>';
?>
</body>
</html>
