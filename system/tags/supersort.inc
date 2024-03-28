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
 * SuperSort Field Implementation
 *
 * @package Dacomasy
 * @subpackage Tags
 * @version $SixXGate: webapps/dacomasy/www/system/tags/supersort.inc,v 1.1.1.1 2005/07/21 22:59:04 matthew Exp $
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @author 6XGate, Inc. <support@sixxgate.com>
 */

/**
 * SuperSort Field Class
 * @package Dacomasy
 * @ignore
 */
final class dacomasy_supersort implements IDacomasyField {
	static private $DBHostname = NULL;
	static private $DBUsername = NULL;
	static private $DBPassword = NULL;
	static private $DBCatalog = NULL;

	static function GetFetchQuery (&$FieldDeclare, $TableName, $IsList = FALSE) {
		$q['Select'] = ''; $q['From'] = ''; $q['Where'] = ''; $q['Sort'] = '';
		$q['Select'] = DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['Name']);
		$q['Sort'] = DacoDBConnection::EscapeString($FieldDeclare['Name']);
		return $q;
	}
	
	static function GetFieldTypeInfo () {
		
	}
	
	static function CreateFieldDeclaration (&$DOMElement, $module, $panelIndex) {
		DacomasyGetCommonFieldData($DOMElement, $field);
		$field['Type'] = DACOMASY_FIELDTYPE_SUPERSORT;
		
		dacomasy_supersort::$DBHostname = $module['Server']['Hostname'];
		dacomasy_supersort::$DBUsername = $module['Server']['Username'];
		dacomasy_supersort::$DBPassword = $module['Server']['Password'];
		dacomasy_supersort::$DBCatalog = $module['Panels'][$panelIndex]['Database'];
		
		return $field;
	}
	
	static function GetSetQuery(&$FieldDeclare, $TableName, &$Values, $IsEdit = FALSE) {
		if ($IsEdit === FALSE) {
			$DB = new DacoDBConnection(dacomasy_supersort::$DBHostname, dacomasy_supersort::$DBUsername, dacomasy_supersort::$DBPassword);
			if ($DB->Connect() === FALSE) {
				DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
				return FALSE;
			}
			
			if ($DB->SelectCatalog(dacomasy_supersort::$DBCatalog) === FALSE) {
				DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
				return FALSE;
			}
			$rCount = $DB->Query('SELECT COUNT(' . DacoDBConnection::EscapeString($FieldDeclare['Name']) . ') AS RecordCount FROM ' . DacoDBConnection::EscapeString($TableName));
			if ($rCount->Error() === TRUE) {
				DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
				return FALSE;
			}
			
			if ($rCount->RowCount() > 0) {
				$rCount = $rCount->FetchNextRecord();
				$rCount = $rCount['RecordCount'];
			} else $rCount = 0;
			$q['Select'] = DacoDBConnection::EscapeString($FieldDeclare['Name']);
			$q['Select'] .= '=' . DacoDBConnection::Escape(intval($rCount));
			return $q;
		} return;
	}
	
	static function GetRecordValues(&$FieldDeclare, &$RecordArray, &$Values) {
		
	}

	static function ValidateValues(&$FieldDeclare, &$Values, &$InvalidMsg, $IsEdit = FALSE) {
		global $__dacomasy__MSG_res;
		return TRUE;
	}
	
	static function GetRecordSetField(&$FieldDeclare, &$RecordSet) {
		$FieldCount = count($RecordSet['Fields']);
		$RecordSet['Fields'][$FieldCount]['Label'] = $FieldDeclare['Label'];
		$RecordSet['Fields'][$FieldCount]['Name'] = $FieldDeclare['Name'];
		$RecordSet['Fields'][$FieldCount]['Type'] = $FieldDeclare['Type'];
	}
	
	static function GetRecordSetRecordField(&$FieldDeclare, &$RecordSet, &$Record, $RecordIndex) {
		$FieldCount = count($RecordSet['Records'][$RecordIndex]);
		$RecordSet['Records'][$RecordIndex][$FieldCount]['Value'] = $Record[$FieldDeclare['Name']];
	}

	// Placeholders
	static function PrepareValues (&$FieldDeclare, &$Values) {}
	static function UnprepareValues (&$FieldDeclare, &$Values) {}
	static function GenerateField (&$FieldDeclare, &$Values, $IsEdit = FALSE) {}
	static function GetPostValues (&$FieldDeclare, &$Values) {}
}

// Needed to add the class
$DacomasyField[DACOMASY_FIELDTYPE_SUPERSORT] = new dacomasy_supersort;
$DacomasyField['supersort'] = &$DacomasyField[DACOMASY_FIELDTYPE_SUPERSORT];

?>