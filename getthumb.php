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
 * Fetches a temperary file for download or display.
 * 
 * @package Dacomasy
 * @subpackage WebClient
 * @version $SixXGate: webapps/dacomasy/www/getthumb.php,v 1.1.1.1 2005/07/21 22:57:31 matthew Exp $
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 */

/** @ignore */
require_once('system/dacomasy.inc');

header('Content-Type: image/jpeg', TRUE);
if (strlen($_GET['name']) > 0)
	header('Content-Disposition: attachment; filename="' . $_GET['name'] . '"', TRUE);

// Calculate the new image size limiting the height 150px
switch ($_GET['type']) {
case 'image/jpeg':
	$simg = imagecreatefromjpeg ($_GET['file']);
	break;
case 'image/gif':
	$simg = imagecreatefromgif ($_GET['file']);
	break;
case 'image/x-png':
	$simg = imagecreatefrompng ($_GET['file']);
	break;
}
if ($simg === FALSE) { /* See if it failed */
	$simg  = imagecreate(150, 30); /* Create a blank image */
	$bgc = imagecolorallocate($simg, 255, 255, 255);
	$tc  = imagecolorallocate($simg, 0, 0, 0);
	imagefilledrectangle($simg, 0, 0, 150, 30, $bgc);
	/* Output an errmsg */
	imagestring($hImage, 1, 5, 5, "Error loading $imgname", $tc);
} else {
	$width = imagesx ($simg);
	$height = imagesy ($simg);
	$rWidth = intval($width * (150 / $height));
	$img = imagecreatetruecolor ($rWidth, 150);
	imagecopyresampled ($img, $simg, 0, 0, 0, 0, $rWidth, 150, $width, $height);
	$simg = $img;
}
imagejpeg ($simg, '', 80);
imagedestroy ($simg);
// echo file_get_contents($_GET['file']);

?>