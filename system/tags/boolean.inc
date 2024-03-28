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
 * Boolean Field Implementation
 *
 * @package Dacomasy
 * @subpackage Tags
 * @version $SixXGate: webapps/dacomasy/www/system/tags/boolean.inc,v 1.1.1.1 2005/07/21 22:59:04 matthew Exp $
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @author 6XGate, Inc. <support@sixxgate.com>
 */

/**
 * Boolean Field Class
 * @package Dacomasy
 * @ignore
 */
final class dacomasy_boolean implements IDacomasyField {
	static function GetFetchQuery (&$FieldDeclare, $TableName, $IsList = FALSE) {
		$q['Select'] = ''; $q['From'] = ''; $q['Where'] = ''; $q['Sort'] = '';
		$q['Select'] = DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['Name']);
		return $q;
	}
	
	static function GenerateField (&$FieldDeclare, &$Values, $IsEdit = FALSE) {
		$FormHTML = '<div><input type="checkbox" name="' . $FieldDeclare['Name'] . '" id="' . $FieldDeclare['Name'] . '" value="1" class="fieldBoolean"';
		if ($Values[ $FieldDeclare['Name'] ] == 1) $FormHTML .= ' checked';
		$FormHTML .= '><label for="' . $FieldDeclare['Name'] . '" class="fieldBoolean">' . $FieldDeclare['Label'] . '</label></div>' . "\n";
		return $FormHTML;
	}
	
	static function GetPostValues (&$FieldDeclare, &$Values) {
		if (intval($_POST[ $FieldDeclare['Name'] ]) == 0) {
			@$Values[ $FieldDeclare['Name'] ] = '0';
		} else {
			@$Values[ $FieldDeclare['Name'] ] = '1';
		}
		return TRUE;
	}
	
	static function GetFieldTypeInfo () {
		
	}
	
	static function CreateFieldDeclaration (&$DOMElement, $module, $panelIndex) {
		DacomasyGetCommonFieldData($DOMElement, $field);		
		$field['Type'] = DACOMASY_FIELDTYPE_BOOLEAN;
		return $field;
	}
	
	static function GetSetQuery(&$FieldDeclare, $TableName, &$Values, $IsEdit = FALSE) {
		$q['Select'] = DacoDBConnection::EscapeString($FieldDeclare['Name']) . '=';
		if (strlen($Values[ $FieldDeclare['Name'] ]) > 0) {
			if (intval($Values[ $FieldDeclare['Name'] ]) == 0) {
				$BoolVal = FALSE;
			} else {
				$BoolVal = TRUE;
			}
			$q['Select'] .= DacoDBConnection::Escape($BoolVal);
		} else {
			$q['Select'] .= 'NULL';
		}
		return $q;
	}
	
	static function GetRecordValues(&$FieldDeclare, &$RecordArray, &$Values) {
		$Values[ $FieldDeclare['Name'] ] = (intval($RecordArray[ $FieldDeclare['Name'] ]) == 0) ? '0' : '1';
		return TRUE;
	}
	
	static function ValidateValues(&$FieldDeclare, &$Values, &$InvalidMsg, $IsEdit = FALSE) {
		global $__dacomasy__MSG_res;
		return TRUE;
	}
	
	static function GetRecordSetField(&$FieldDeclare, &$RecordSet) {
		if ($FieldDeclare['InTable'] === TRUE) {
			$FieldCount = count($RecordSet['Fields']);
			$RecordSet['Fields'][$FieldCount]['Label'] = $FieldDeclare['Label'];
			$RecordSet['Fields'][$FieldCount]['Name'] = $FieldDeclare['Name'];
			$RecordSet['Fields'][$FieldCount]['Type'] = $FieldDeclare['Type'];
		}
	}
	
	static function GetRecordSetRecordField(&$FieldDeclare, &$RecordSet, &$Record, $RecordIndex) {
		if ($FieldDeclare['InTable'] === TRUE) {
			$FieldCount = count($RecordSet['Records'][$RecordIndex]);
			$RecordSet['Records'][$RecordIndex][$FieldCount]['Value'] = $Record[$FieldDeclare['Name']];
		}
	}
	
	// Placeholders
	static function PrepareValues (&$FieldDeclare, &$Values) {}
	static function UnprepareValues (&$FieldDeclare, &$Values) {}
}

// Needed to add the class
$DacomasyField[DACOMASY_FIELDTYPE_BOOLEAN] = new dacomasy_boolean;
$DacomasyField['boolean'] = &$DacomasyField[DACOMASY_FIELDTYPE_BOOLEAN];

?>