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
 * List Field Implementation
 *
 * @package Dacomasy
 * @subpackage Tags
 * @version $SixXGate: webapps/dacomasy/www/system/tags/list.inc,v 1.1.1.1 2005/07/21 22:59:04 matthew Exp $
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @author 6XGate, Inc. <support@sixxgate.com>
 */

/**
 * List Field Class
 * @package Dacomasy
 * @ignore
 */
final class dacomasy_list implements IDacomasyField {
	static function GetFetchQuery (&$FieldDeclare, $TableName, $IsList = FALSE) {
		$q['Select'] = ''; $q['From'] = ''; $q['Where'] = ''; $q['Sort'] = '';
		$q['Select'] = DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['Name']);
		return $q;
	}
	
	static function GenerateField (&$FieldDeclare, &$Values, $IsEdit = FALSE) {
		switch ($FieldDeclare['As']) {
		case 'combo':
			$FormHTML = '<div><label for="' . $FieldDeclare['Name'] . '" class="fieldList">List - ' . $FieldDeclare['Label'] . '</label>' . "\n";
			$FormHTML .= '<select id="' . $FieldDeclare['Name'] . '" name="' . $FieldDeclare['Name'] . '" size="1" class="fieldList">' . "\n";
			for ($s = 0; $s < count($FieldDeclare['Selections']); $s++) {
				$FormHTML .= '<option value="' . $s . '"';
				if ($s == intval($Values[ $FieldDeclare['Name'] ])) $FormHTML .= ' selected="selected" ';
				$FormHTML .= '>' . $FieldDeclare['Selections'][$s] . '</option>';
			}
			$FormHTML .= '</select></div>' . "\n";
			break;
		case 'radio':
			$FormHTML = '<fieldset class="fieldList"><legend>' . $FieldDeclare['Label'] . '</legend>' . "\n";
			for ($s = 0; $s < count($FieldDeclare['Selections']); $s++) {
				$FormHTML .= '<div><input type="radio"  class="fieldList" name="' . $FieldDeclare['Name'] . '" id="' . $FieldDeclare['Name'] . $s . '" value="' . $s . '"';
				if ($s == intval($Values[ $FieldDeclare['Name'] ])) $FormHTML .= ' checked="checked" ';
				$FormHTML .= '><label class="fieldList" for="' . $FieldDeclare['Name'] . $s . '">' . $FieldDeclare['Selections'][$s] . '</label></div>' . "\n";
			}
			$FormHTML .= "</fieldset>\n";
			break;
		default:
			$FormHTML = '<div><label for="' . $FieldDeclare['Name'] . '" class="fieldList ">List - ' . $FieldDeclare['Label'] . '</label>' . "\n";
			$FormHTML .= '<select id="' . $FieldDeclare['Name'] . '" name="' . $FieldDeclare['Name'] . '" size="5" class="fieldList">' . "\n";
			for ($s = 0; $s < count($FieldDeclare['Selections']); $s++) {
				$FormHTML .= '<option value="' . $s . '"';
				if ($s == intval($Values[ $FieldDeclare['Name'] ])) $FormHTML .= ' selected="selected" ';
				$FormHTML .= '>' . $FieldDeclare['Selections'][$s] . '</option>';
			}
			$FormHTML .= '</select></div>';
		}
		return $FormHTML;
	}
	
	static function GetPostValues (&$FieldDeclare, &$Values) {
		@$Values[ $FieldDeclare['Name'] ] = $_POST[ $FieldDeclare['Name'] ];
		return TRUE;
	}
	
	static function GetFieldTypeInfo () {
		
	}
	
	static function CreateFieldDeclaration (&$DOMElement, $module, $panelIndex) {
		DacomasyGetCommonFieldData($DOMElement, $field);		
		$field['Type'] = DACOMASY_FIELDTYPE_LIST;
		$field['As'] = $DOMElement->getAttribute('as');
		$field['Selections'] = explode('|', $DOMElement->getAttribute('selections'));
		return $field;
	}
	
	static function GetSetQuery(&$FieldDeclare, $TableName, &$Values, $IsEdit = FALSE) {
		$q['Select'] = DacoDBConnection::EscapeString($FieldDeclare['Name']) . '=';
		if (strlen($Values[ $FieldDeclare['Name'] ]) > 0) {
			$q['Select'] .= '"' . DacoDBConnection::EscapeString($Values[ $FieldDeclare['Name'] ]) . '"';
		} else {
			$q['Select'] .= 'NULL';
		}
		return $q;
	}
	
	static function GetRecordValues(&$FieldDeclare, &$RecordArray, &$Values) {
		$Values[ $FieldDeclare['Name'] ] = $RecordArray[ $FieldDeclare['Name'] ];
		return TRUE;
	}

	static function ValidateValues(&$FieldDeclare, &$Values, &$InvalidMsg, $IsEdit = FALSE) {
		global $__dacomasy__MSG_res;
		if (intval($Values[ $FieldDeclare['Name'] ]) > count($FieldDeclare['Selections'])) {
			$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_NUMTOOBIG], $FieldDeclare['Label']);
			return FALSE;
		}
		if (intval($Values[ $FieldDeclare['Name'] ]) < 0) {
			$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_NUMTOOSMALL], $FieldDeclare['Label']);
			return FALSE;
		}
		if ($FieldDeclare['AllowNull'] === FALSE) {
			if (strlen($Values[ $FieldDeclare['Name'] ]) < 1) {
				$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_NONULL], $FieldDeclare['Label']);
				return FALSE;
			}
		}
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
			$RecordSet['Records'][$RecordIndex][$FieldCount]['Value'] =  $FieldDeclare['Selections'][ intval($Record[$FieldDeclare['Name']]) ];
		}
	}
	
	// Placeholders
	static function PrepareValues (&$FieldDeclare, &$Values) {}
	static function UnprepareValues (&$FieldDeclare, &$Values) {}
}

// Needed to add the class
$DacomasyField[DACOMASY_FIELDTYPE_LIST] = new dacomasy_list;
$DacomasyField['list'] = &$DacomasyField[DACOMASY_FIELDTYPE_LIST];

?>