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
 * FieldList Field Implementation
 *
 * @package Dacomasy
 * @subpackage Tags
 * @version $SixXGate: webapps/dacomasy/www/system/tags/fieldlist.inc,v 1.1.1.1 2005/07/21 22:59:04 matthew Exp $
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @author 6XGate, Inc. <support@sixxgate.com>
 */

/**
 * FieldList Field Class
 * @package Dacomasy
 * @ignore
 */
final class dacomasy_fieldlist implements IDacomasyField {
	static function GetFetchQuery (&$FieldDeclare, $TableName, $IsList = FALSE) {
		$q['Select'] = ''; $q['From'] = ''; $q['Where'] = ''; $q['Sort'] = '';
		if ($IsList === TRUE) {
			$q['Select'] = DacoDBConnection::EscapeString($FieldDeclare['Table']) . '.' . DacoDBConnection::EscapeString($FieldDeclare['ShowAs']) . ' AS ' . DacoDBConnection::EscapeString($FieldDeclare['Name']);
			$q['From'] = ' LEFT JOIN ' . DacoDBConnection::EscapeString($FieldDeclare['Table']) . ' ON (' . DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['Name']) . '=' . DacoDBConnection::EscapeString($FieldDeclare['Table']) . '.' . DacoDBConnection::EscapeString($FieldDeclare['FillWith']) . ')';
		} else {
			$q['Select'] = DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['Name']);
		}
		return $q;
	}
	
	static function GenerateField (&$FieldDeclare, &$Values, $IsEdit = FALSE) {
		switch ($FieldDeclare['As']) {
		case 'combo':
			$FormHTML = '<div><label for="' . $FieldDeclare['Name'] . '" class="fieldList">List - ' . $FieldDeclare['Label'] . '</label>' . "\n";
			$FormHTML .= '<select id="' . $FieldDeclare['Name'] . '" name="' . $FieldDeclare['Name'] . '" size="1" class="fieldList">' . "\n";
			for ($s = 0; $s < count($FieldDeclare['Selections']); $s++) {
				$FormHTML .= '<option value="' . htmlentities($FieldDeclare['Selections'][$s]['FillWith']) . '"';
				if ($FieldDeclare['Selections'][$s]['FillWith'] == $Values[ $FieldDeclare['Name'] ]) $FormHTML .= ' selected="selected" ';
				$FormHTML .= '>' . htmlentities($FieldDeclare['Selections'][$s]['ShowAs']) . '</option>';
			}
			$FormHTML .= '</select></div>' . "\n";
			break;
		case 'radio':
			$FormHTML = '<fieldset class="fieldList"><legend>' . $FieldDeclare['Label'] . '</legend>' . "\n";
			for ($s = 0; $s < count($FieldDeclare['Selections']); $s++) {
				$FormHTML .= '<div><input type="radio"  class="fieldList" name="' . $FieldDeclare['Name'] . '" id="' . $FieldDeclare['Name'] . $s . '" value="' . htmlentities($FieldDeclare['Selections'][$s]['FillWith']) . '"';
				if ($FieldDeclare['Selections'][$s]['FillWith'] == $Values[ $FieldDeclare['Name'] ]) $FormHTML .= ' checked="checked" ';
				$FormHTML .= '><label class="fieldList" for="' . $FieldDeclare['Name'] . $s . '">' . htmlentities($FieldDeclare['Selections'][$s]['ShowAs']) . '</label></div>' . "\n";
			}
			$FormHTML .= "</fieldset>\n";
			break;
		default:
			$FormHTML = '<div><label for="' . $FieldDeclare['Name'] . '" class="fieldList ">List - ' . $FieldDeclare['Label'] . '</label>' . "\n";
			$FormHTML .= '<select id="' . $FieldDeclare['Name'] . '" name="' . $FieldDeclare['Name'] . '" size="5" class="fieldList">' . "\n";
			for ($s = 0; $s < count($FieldDeclare['Selections']); $s++) {
				$FormHTML .= '<option value="' . htmlentities($FieldDeclare['Selections'][$s]['FillWith']) . '"';
				if ($FieldDeclare['Selections'][$s]['FillWith'] == $Values[ $FieldDeclare['Name'] ]) $FormHTML .= ' selected="selected" ';
				$FormHTML .= '>' . htmlentities($FieldDeclare['Selections'][$s]['ShowAs']) . '</option>';
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
		$field['Type'] = DACOMASY_FIELDTYPE_FIELDLIST;
		$field['As'] = $DOMElement->getAttribute('as');
		$field['FillWith'] = $DOMElement->getAttribute('fillwith');
		$field['ShowAs'] = $DOMElement->getAttribute('showas');
		$field['Table'] = $DOMElement->getAttribute('table');
		
		// Make sure we have a valid panel
		if ($panelIndex > count($module['Panels'])) {
			DacomasySetLastError(__DACOMASY_ERROR_PANELINVALID);
			return FALSE;
		}
		
		// Connect to the server
		$DB = new DacoDBConnection($module['Server']['Hostname'], $module['Server']['Username'], $module['Server']['Password']);
		if ($DB->Connect() === FALSE) {
			DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
			return FALSE;
		}
		
		// Select the database
		if ($DB->SelectCatalog($module['Panels'][$panelIndex]['Database']) === FALSE) {
			DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
			return FALSE;
		}
		
		// Get the records
		$Query = 'SELECT ' . DacoDBConnection::EscapeString($field['Table']) . '.' . DacoDBConnection::EscapeString($field['FillWith']) . ' AS fillwith, ' . DacoDBConnection::EscapeString($field['Table']) . '.' . DacoDBConnection::EscapeString($field['ShowAs']) . ' AS showas FROM ' . DacoDBConnection::EscapeString($field['Table']);
		$rQuery = $DB->Query($Query);
		if (($rQuery === FALSE) || ($rQuery->Error() === TRUE)) {
			DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
			return FALSE;
		}
		
		for ($r = 0; $r < $rQuery->RowCount($rQuery); $r++) {
			$Record = $rQuery->FetchNextRecord($rQuery);
			if ($Record === FALSE) break;
			
			$field['Selections'][$r]['FillWith'] = $Record['fillwith'];
			$field['Selections'][$r]['ShowAs'] = $Record['showas'];
		}
		unset($rQuery);
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
		$FieldValid = FALSE;
		for ($i = 0; $i < count($FieldDeclare['Selections']); $i++) {
			if ($Values[ $FieldDeclare['Name'] ] == $FieldDeclare['Selections'][$i]['FillWith']) $FieldValid = TRUE;
		}
		if ($FieldValid === FALSE) {
			$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf ($__dacomasy__MSG_res[__DACOMASY_MSG_INVALIDSELECTION], $FieldDeclare['Label']);
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
			$RecordSet['Records'][$RecordIndex][$FieldCount]['Value'] = $Record[$FieldDeclare['Name']];
		}
	}
	
	// Placeholders
	static function PrepareValues (&$FieldDeclare, &$Values) {}
	static function UnprepareValues (&$FieldDeclare, &$Values) {}
}

// Needed to add the class
$DacomasyField[DACOMASY_FIELDTYPE_FIELDLIST] = new dacomasy_fieldlist;
$DacomasyField['fieldlist'] = &$DacomasyField[DACOMASY_FIELDTYPE_FIELDLIST];

?>