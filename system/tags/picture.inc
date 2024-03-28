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
 * Picture Field Implementation
 *
 * @package Dacomasy
 * @subpackage Tags
 * @version $SixXGate: webapps/dacomasy/www/system/tags/picture.inc,v 1.1.1.1 2005/07/21 22:59:04 matthew Exp $
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @author 6XGate, Inc. <support@sixxgate.com>
 */

/**
 * Password Field Class
 * @package Dacomasy
 * @ignore
 */
final class dacomasy_picture implements IDacomasyField {
	static function GetFetchQuery (&$FieldDeclare, $TableName, $IsList = FALSE) {
		$q['Select'] = ''; $q['From'] = ''; $q['Where'] = ''; $q['Sort'] = '';
		if ($IsList === FALSE) {
			$q['Select'] = DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['Name']);
			$q['Select'] .= ',' . DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['CType']);
			$q['Select'] .= ',' . DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['CSize']);
			if (strlen($FieldDeclare['Filename']) > 0) {
				$q['Select'] .= ',' . DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['Filename']);
			}
		}
		return $q;
	}
	
	static function GenerateField (&$FieldDeclare, &$Values, $IsEdit = FALSE) {
		$FormHTML = '<div><label for="' . $FieldDeclare['Name'] . '" class="fieldUpload">' . $FieldDeclare['Label'] . '</label>';
		$FormHTML .= '<input type="file" name="' . $FieldDeclare['Name'] . '" id="' . $FieldDeclare['Name'] . '" accept="image/jpeg,image/gif,image/x-png" class="fieldUpload">';
		if (isset($Values[ $FieldDeclare['Name'] ]['filename'])) {
			$FormHTML .= '<input type="hidden" name="DACO_' . $FieldDeclare['Name'] . '_filename" value="' . $Values[ $FieldDeclare['Name'] ]['filename'] . '">';
			@$FormHTML .= '<input type="hidden" name="DACO_' . $FieldDeclare['Name'] . '_name" value="' . $Values[ $FieldDeclare['Name'] ]['name'] . '">';
			$FormHTML .= '<input type="hidden" name="DACO_' . $FieldDeclare['Name'] . '_size" value="' . $Values[ $FieldDeclare['Name'] ]['size'] . '">';
			$FormHTML .= '<input type="hidden" name="DACO_' . $FieldDeclare['Name'] . '_type" value="' . $Values[ $FieldDeclare['Name'] ]['type'] . '"><br>';
			@$FormHTML .= '<p><a href="getfile.php?name=' . urlencode($Values[ $FieldDeclare['Name'] ]['name']) . '&amp;type=' . urlencode($Values[ $FieldDeclare['Name'] ]['type']) . '&amp;file=' . urlencode($Values[ $FieldDeclare['Name'] ]['filename']) . '&amp;' . DacomasySID() . '" target="_blank"><img src="getthumb.php?name=' . urlencode($Values[ $FieldDeclare['Name'] ]['name']) . '&amp;type=' . urlencode($Values[ $FieldDeclare['Name'] ]['type']) . '&amp;file=' . urlencode($Values[ $FieldDeclare['Name'] ]['filename']) . '&amp;' . DacomasySID() . '" alt=""></a></p>';
		}
		$FormHTML .= '</div>';
		return $FormHTML;
	}
	
	static function GetPostValues (&$FieldDeclare, &$Values) {
		if ($_FILES[ $FieldDeclare['Name'] ]['error'] == 0) {
			// If a file was posted lets get its information
			@$ValArray['filename'] = tempnam('/tmp', 'DCMS_');
			@copy($_FILES[ $FieldDeclare['Name'] ]['tmp_name'], $ValArray['filename']);
			@$ValArray['type'] = $_FILES[ $FieldDeclare['Name'] ]['type'];
			@$ValArray['size'] = $_FILES[ $FieldDeclare['Name'] ]['size'];
			@$ValArray['name'] = $_FILES[ $FieldDeclare['Name'] ]['name'];
			$Values[ $FieldDeclare['Name'] ] = $ValArray;
			if (isset($_POST[ 'DACO_' . $FieldDeclare['Name'] . '_filename'])) {
				// If a file already exists, delete it in place of the new one.
				unlink($_POST[ 'DACO_' . $FieldDeclare['Name'] . '_filename']);
			}
		} else {
			if (isset($_POST[ 'DACO_' . $FieldDeclare['Name'] . '_filename'])) {
				// If no file was posted, get an existing file
				@$ValArray['filename'] = $_POST[ 'DACO_' . $FieldDeclare['Name'] . '_filename'];
				@$ValArray['type'] = $_POST[ 'DACO_' . $FieldDeclare['Name'] . '_type'];
				@$ValArray['size'] = $_POST[ 'DACO_' . $FieldDeclare['Name'] . '_size'];
				@$ValArray['name'] = $_POST[ 'DACO_' . $FieldDeclare['Name'] . '_name'];
				$Values[ $FieldDeclare['Name'] ] = $ValArray;
			}
		}
		return TRUE;
	}
	
	static function PrepareValues (&$FieldDeclare, &$Values) {
		if (isset($Values[ $FieldDeclare['Name'] ])) {
			$ValArray = $Values[ $FieldDeclare['Name'] ];
			
			$Values[ $FieldDeclare['Name'] ] = file_get_contents($ValArray['filename']);
			$Values[ $FieldDeclare['CSize'] ] = $ValArray['size'];
			$Values[ $FieldDeclare['CType'] ] = $ValArray['type'];
			$Values[ $FieldDeclare['Filename'] ] = $ValArray['name'];
		} else {
			$Values[ $FieldDeclare['CSize'] ] = '0';
		}
	}
	
	static function UnprepareValues (&$FieldDeclare, &$Values) {
		if (@intval($Values[ $FieldDeclare['CSize'] ]) > 0) {
			@$ValArray['type'] = $Values[ $FieldDeclare['CType'] ];
			unset($Values[ $FieldDeclare['CType'] ]);
			@$ValArray['size'] = $Values[ $FieldDeclare['CSize'] ];
			unset($Values[ $FieldDeclare['CSize'] ]);
			if (isset($Values[ $FieldDeclare['Filename'] ])) {
				@$ValArray['name'] = $Values[ $FieldDeclare['Filename'] ];
				unset($Values[ $FieldDeclare['Filename'] ]);
			}
			if ($ValArray['size'] > 0) {
				@$ValArray['filename'] = tempnam('/tmp', 'DCMS_');
				$fHandle = fopen($ValArray['filename'], 'wb');
				if ($fHandle === FALSE) {
					DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL); // TODO replace with an error for not being able to create the file.
					return FALSE;
				}
				fwrite($fHandle, $Values[ $FieldDeclare['Name'] ], $ValArray['size']);
				fclose($fHandle);
			}
			$Values[ $FieldDeclare['Name'] ] = $ValArray;
		}
	}
	
	static function GetFieldTypeInfo () {
		
	}
	
	static function CreateFieldDeclaration (&$DOMElement, $module, $panelIndex) {
		DacomasyGetCommonFieldData($DOMElement, $field);		
		$field['Type'] = DACOMASY_FIELDTYPE_PICTURE;
		$field['Maximum'] = $DOMElement->getAttribute('max');
		$field['Filename'] = $DOMElement->getAttribute('filename');
		$field['CType'] = $DOMElement->getAttribute('ctype');
		$field['CSize'] = $DOMElement->getAttribute('csize');
		return $field;
	}
	
	static function GetSetQuery(&$FieldDeclare, $TableName, &$Values, $IsEdit = FALSE) {
		if (intval($Values[ $FieldDeclare['CSize'] ]) > 0) {
			$q['Select'] = DacoDBConnection::EscapeString($FieldDeclare['Name']) . '="' . DacoDBConnection::EscapeBinary($Values[ $FieldDeclare['Name'] ]) . '",' . DacoDBConnection::EscapeString($FieldDeclare['CType']) . '="' . DacoDBConnection::EscapeString($Values[ $FieldDeclare['CType'] ]) . '",' . DacoDBConnection::EscapeString($FieldDeclare['CSize']) . '="' . DacoDBConnection::EscapeString($Values[ $FieldDeclare['CSize'] ]) . '"';
			if (strlen($FieldDeclare['Filename']) > 0) {
				$q['Select'] .= ',' . DacoDBConnection::EscapeString($FieldDeclare['Filename']) . '="' . DacoDBConnection::EscapeString($Values[ $FieldDeclare['Filename'] ]) . '"';
			}
		} else {
			$q['Select'] = DacoDBConnection::EscapeString($FieldDeclare['Name']) . '=NULL,' . DacoDBConnection::EscapeString($FieldDeclare['CType']) . '=NULL,' . DacoDBConnection::EscapeString($FieldDeclare['CSize']) . '=0';
			if (strlen($FieldDeclare['Filename']) > 0) {
				$q['Select'] .= ',' . DacoDBConnection::EscapeString($FieldDeclare['Filename']) . '=NULL';
			}
		}
		return $q;
	}
	
	static function GetRecordValues(&$FieldDeclare, &$RecordArray, &$Values) {
		$Values[ $FieldDeclare['Name'] ] = $RecordArray[ $FieldDeclare['Name'] ];
		$Values[ $FieldDeclare['CType'] ] = $RecordArray[ $FieldDeclare['CType'] ];
		$Values[ $FieldDeclare['CSize'] ] = $RecordArray[ $FieldDeclare['CSize'] ];
		if (isset($FieldDeclare['Filename']))
			if (strlen($FieldDeclare['Filename']) > 0) $Values[ $FieldDeclare['Filename'] ] = $RecordArray[ $FieldDeclare['Filename'] ];
	}

	static function ValidateValues(&$FieldDeclare, &$Values, &$InvalidMsg, $IsEdit = FALSE) {
		global $__dacomasy__MSG_res;
		if (($FieldDeclare['Maximum'] > 0) && (!empty($FieldDeclare['Maximum']))){
			if ($Values[ $FieldDeclare['Name'] ]['size'] > $FieldDeclare['Maximum']) {
				$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_FILETOOBIG], $FieldDeclare['Label'], $FieldDeclare['Maximum'] / 0x400);
				return FALSE;
			}
		}
		if ($FieldDeclare['AllowNull'] === FALSE) {
			if ($Values[ $FieldDeclare['Name'] ]['size'] < 1) {
				$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_NONULL], $FieldDeclare['Label']);
				return FALSE;
			}
		}
		// Make sure the field has a value, it may be nullallowed...
		if (@intval($Values[ $FieldDeclare['Name'] ]['size']) > 0) {
			switch ($Values[ $FieldDeclare['Name'] ]['type']) {
			case 'image/jpeg':
			case 'image/gif':
			case 'image/x-png':
				break;
			default:
				$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_NOTAIMAGE], $FieldDeclare['Label']);
				return FALSE;
			}
		}
		return TRUE;
	}
	
	// Placeholders
	static function GetRecordSetField(&$FieldDeclare, &$RecordSet) {}
	static function GetRecordSetRecordField(&$FieldDeclare, &$RecordSet, &$Record, $RecordIndex) {}
}

// Needed to add the class
$DacomasyField[DACOMASY_FIELDTYPE_PICTURE] = new dacomasy_picture;
$DacomasyField['picture'] = &$DacomasyField[DACOMASY_FIELDTYPE_PICTURE];

?>