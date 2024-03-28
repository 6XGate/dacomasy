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
 * These routines provides interface and validation capability.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Interface
 * @version $SixXGate: webapps/dacomasy/www/system/lib/interface.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

/**
 * Validates form data and returns messages about any invalid data.
 *
 * @param array A loaded Dacomasy module.
 * @param number The index of the panel.
 * @param array Contains the values of all the form fields that Dacomasy recognized.
 * @param array An array which to add invalid messages.
 * @return boolean Is true is the form data is valid, false if it is not valid.
 */
function DacomasyValidateForm(&$module, $panelIndex, &$Values, &$InvalidFieldMessages, $IsEdit = FALSE) {
	global $__dacomasy__MSG_res, $DacomasyField;
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	$IsValid = TRUE;
	for ($f = 1; $f < count($FieldSet); $f++) {
		if ($DacomasyField[ $FieldSet[$f]['Type'] ]->ValidateValues($FieldSet[$f], $Values, $InvalidFieldMessages, $IsEdit) === FALSE) $IsValid = FALSE;
	} // for $f
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return $IsValid;
}

/**
 * Gets a values array from form POST data.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @return array An array of POST data that Dacomasy recognized.
 */
function DacomasyGenerateValuesArray(&$module, $panelIndex) {
	global $DacomasyField;
	unset($Values);
	
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	$Values = array();

	for ($f = 0; $f < count($FieldSet); $f++) $DacomasyField[$FieldSet[$f]['Type']]->GetPostValues($FieldSet[$f], $Values);
	
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return $Values;
}

/**
 * Generates an HTML form for collecting data to update or add a record.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @param string The filename of the module.
 * @param array An array of values to fill the form with when updating a record or fixing invalid entries.
 * @param array An array of messages about any invalid fields.  Is null if no fields are invalid.
 * @param boolean Indicates if the form is for adding a record or updating a record.
 * @return string HTML code for the entry form.
 */
function DacomasyGenerateForm(&$module, $panelIndex, $moduleFilename, &$Values = NULL, &$InvalidFieldMessages = NULL, $IsEdit = FALSE) {
	global $__dacomasy__LABEL_res, $ImageExt, $DacomasyField;
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	$FormHTML = '';
	
	// If no values are given then set them all to empty.
	if ($Values == NULL) {
		unset($Values);
		for ($f = 0; $f < count($FieldSet); $f++) {
			$Values[ $FieldSet[$f]['Name'] ] = '';
			switch ($FieldSet[$f]['Type']) {
				case DACOMASY_FIELDTYPE_LINK:
					$Values[ $FieldSet[$f]['HRef'] ] = '';
					break;
			}
		}
	}
	
	if($IsEdit) $action = 'action="edit.php?done=yes&amp;mod=' . urlencode($moduleFilename) . '&amp;pan=' . $panelIndex . '&amp;index=' . urlencode($Values[ $FieldSet[0]['Name'] ]) . '&amp;' . DacomasySID() . '"';
	else $action = 'action="add.php?done=yes&amp;mod=' . urlencode($moduleFilename) . '&amp;pan=' . $panelIndex . '&amp;' . DacomasySID() . '"';
	$FormHTML .= '<form ' . $action . ' id="DacomasyForm" name="DacomasyForm" method="post" enctype="multipart/form-data">';
	
	// Generate the form fields for each panel field.
	for ($f = 0; $f < count($FieldSet); $f++) {
		if (isset($InvalidFieldMessages[ $FieldSet[$f]['Name'] ])) $FormHTML .= '<p class="InvalidMessage">' . $InvalidFieldMessages[ $FieldSet[$f]['Name'] ] . '</p>';
		$FormHTML .= $DacomasyField[ $FieldSet[$f]['Type'] ]->GenerateField($FieldSet[$f], $Values, $IsEdit);
	} // for $f 
	
	// Add the buttons
	$FormHTML .= '<button id="DACO_okButton" name="DACO_action" value="okay" type="submit" class="realfunction"></button>';
	$FormHTML .= '<button id="DACO_cancelButton" name="DACO_action" value="cancel" type="submit" class="realfunction"></button>';
	$FormHTML .= '</form>';
	
	// And return the forms HTML code
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return $FormHTML;
}

?>