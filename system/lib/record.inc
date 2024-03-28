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
 * These routines collect records and the structure of records.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Record
 * @version $SixXGate: webapps/dacomasy/www/system/lib/record.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

/**
 * Creates a list of record and a basic panel structure.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @return array The basic panel field structure and a list of all records in the panel.
 */
function DacomasyListRecords(&$module, $panelIndex) {
	global $DacomasyField;
	
	if ($module == FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_PANELINVALID);
		return FALSE;
	}
	if ($panelIndex > count($module['Panels'])) {
		DacomasySetLastError(__DACOMASY_ERROR_PANELINVALID);
		return FALSE;
	}
	
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	
	unset($RecordSet);			// Holds the RPC Recordset
	
	// Query clauses
	$Select = '';				// SELECT portion of the SQL Query
	$From = $module['Panels'][$panelIndex]['Table'];	// FROM portion of the SQL Query
	$Where = '';				// WHERE portion of the SQL Query
	$Sort = '';					// ORDER BY portion of the SQL Query
	
	// Initially set these to false
	$RecordSet['Functions']['Password'] = FALSE;	// Show Change Password
	$RecordSet['Functions']['SuperSort'] = FALSE;	// Show Supersort
	
	$DB = new DacoDBConnection($module['Server']['Hostname'], $module['Server']['Username'], $module['Server']['Password']);
	if ($DB->Connect() === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
		return FALSE;
	}
	
	if ($DB->SelectCatalog ($module['Panels'][$panelIndex]['Database']) === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
		$DB->Disconnect();
		return FALSE;
	}
	
	// Generate the RecordSetFields
	for ($f = 0; $f < count($FieldSet); $f++) {
		$DacomasyField[$FieldSet[$f]['Type']]->GetRecordSetField($FieldSet[$f], $RecordSet);
		if ($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_PASSWORD) $RecordSet['Functions']['Password'] = TRUE;
		if ($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_SUPERSORT) $RecordSet['Functions']['SuperSort'] = TRUE;
	}
	
	// Generate the SQL Query
	for ($f = 0; $f < count($FieldSet); $f++) {
		$q = $DacomasyField[$FieldSet[$f]['Type']]->GetFetchQuery($FieldSet[$f], $module['Panels'][$panelIndex]['Table'], TRUE);
		if (@strlen($q['Select']) > 0) {
			if (strlen($Select) > 0) $Select .= ', ';
			$Select .= $q['Select'];
		}
		if (@strlen($q['From']) > 0) {
			if (strlen($From)) $From .= ' ';
			$From .= $q['From'];
		}
		if (@strlen($q['Where']) > 0) {
			if (strlen($Where)) $Where .= ' AND ';
			$Where .= $q['Where'];
		}
		if (@strlen($q['Sort']) > 0) {
			if (strlen($Sort)) $Sort .= ', ';
			$Sort .= $q['Sort'];
		}
	}
	
	$Query = 'SELECT ' . $Select . ' FROM ' . $From;
	if (strlen($Where)) $Query .= ' WHERE ' . $Where;
	if (strlen($Sort)) $Query .= ' ORDER BY ' . $Sort;
	
	$rQuery = $DB->Query($Query);
	if (($rQuery === FALSE) || (@$rQuery->Error() === TRUE)) {
		unset($rQuery);
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		$DB->Disconnect();
		return FALSE;
	}
	
	for ($r = 0; $r < $rQuery->RowCount(); $r++) {
		$Record = $rQuery->FetchNextRecord();
		if ($Record == FALSE) break;
		
		for ($f = 0; $f < count ($FieldSet); $f++) $DacomasyField[$FieldSet[$f]['Type']]->GetRecordSetRecordField($FieldSet[$f], $RecordSet, $Record, $r);
	}
	
	unset($rQuery);
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return $RecordSet;
}

/**
 * Gets the complete structure of records in a panel.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @return array An array of FieldDeclaration structures.
 * @see IDacomasyField::CreateFieldDeclaration(), DacomasyGetFieldData()
 */
function DacomasyGetStructure (&$module, $panelIndex) {
	if ($module === FALSE) return FALSE;
	if ($panelIndex > count($module['Panels'])) {
		DacomasySetLastError(__DACOMASY_ERROR_PANELINVALID);
		return FALSE;
	}
	
	unset($FieldSet); // The field set
	
	// The current Panel
	$Panel = $module['Panels'][$panelIndex];
	for ($f = 0; $f < count($Panel['TableDef']); $f++) {
		$field = DacomasyGetFieldData($Panel['TableDef'][$f], $module, $panelIndex);
		if ($field === FALSE) {
			return FALSE;
		}
		$FieldSet[$f] = $field;
	}
	
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return $FieldSet;
}

/**
 * Gets the structure of a field based on a XML DOM Element.  This is a wrapper for IDacomasyField::CreateFieldDeclaration() method.
 *
 * @param object DOMElement A XML DOM Element from PHP5 DOM extension.
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @return array A FieldDeclaration structures.
 * @see IDacomasyField::CreateFieldDeclaration()
 */
function DacomasyGetFieldData (&$DOMElement, &$module, $panelIndex) {
	global $DacomasyField;
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return $DacomasyField[$DOMElement->tagName]->CreateFieldDeclaration($DOMElement, $module, $panelIndex);
}

/**
 * Adds a record to a panel's database table.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @param array An array of values to be added to the record.
 * @return boolean Is true on success or false on error.
 */
function DacomasyAddRecord(&$module, $panelIndex, &$Values) {
	global $DacomasyField;
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	$SQLQuery = 'INSERT INTO ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ';
	$FieldList = '';
	$DB = new DacoDBConnection($module['Server']['Hostname'], $module['Server']['Username'], $module['Server']['Password']);
	if ($DB->Connect() === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
		return FALSE;
	}
	
	if ($DB->SelectCatalog($module['Panels'][$panelIndex]['Database']) === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
		return FALSE;
	}
	
	for ($f = 0; $f < count($FieldSet); $f++) {
		$q = $DacomasyField[ $FieldSet[$f]['Type'] ]->GetSetQuery($FieldSet[$f], $module['Panels'][$panelIndex]['Table'], $Values);
		if (@strlen($q['Select']) > 0) {
			if (strlen($FieldList) > 0) $FieldList .= ', ';
			$FieldList .= $q['Select'];
		}
	} // for f+

	$SQLQuery .= $FieldList;
	$result = $DB->Query($SQLQuery);
	if (($result === FALSE) || (@$result->Error() === TRUE)) {
		unset($result);
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	
	unset($result);
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return TRUE;
}

// Gets a record from a panel
/**
 * Gets a record from a panel's database table.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @param string The values of the index field of the record to get.
 * @return array Returns a value array of the records data.
 */
function DacomasyGetRecord(&$module, $panelIndex, $index) {
	global $DacomasyField;
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	$Select = 'SELECT * FROM ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' WHERE ' . DacoDBConnection::EscapeString($FieldSet[0]['Name']) . ' = "' . DacoDBConnection::EscapeString($index) . '"';
	$DB = new DacoDBConnection($module['Server']['Hostname'], $module['Server']['Username'], $module['Server']['Password']);
	if ($DB->Connect() === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
		return FALSE;
	}
	
	if ($DB->SelectCatalog($module['Panels'][$panelIndex]['Database']) === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
		return FALSE;
	}
	
	$rQuery = $DB->Query($Select);
	if (($rQuery === FALSE) || ($rQuery->Error() === TRUE)) {
		unset($rQuery);
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);		// TODO: replace with an error about the record not existing
		return FALSE;
	}
	
	if ($rQuery->RowCount() == 0) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	
	$aRecord = $rQuery->FetchNextRecord();
	
	for ($f = 0; $f < count($FieldSet); $f++) $DacomasyField[ $FieldSet[$f]['Type'] ]->GetRecordValues($FieldSet[$f], $aRecord, $Values);
	
	unset($rQuery);
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return $Values; // $Values;
}

/**
 * Updates a record in panel's database table.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @param array An array of values to be used to update a record.
 * @return boolean Is true on success or false on error.
 */
function DacomasyUpdateRecord(&$module, $panelIndex, &$Values) {
	global $DacomasyField;
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	$SQLQuery = 'UPDATE ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ';
	$FieldList = '';
	$RecordIndex = '';
	$DB = new DacoDBConnection($module['Server']['Hostname'], $module['Server']['Username'], $module['Server']['Password']);
	if ($DB->Connect() === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
		return FALSE;
	}
	
	if ($DB->SelectCatalog($module['Panels'][$panelIndex]['Database']) === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
		return FALSE;
	}
	
	for ($f = 0; $f < count($FieldSet); $f++) {
		$q = $DacomasyField[ $FieldSet[$f]['Type'] ]->GetSetQuery($FieldSet[$f], $module['Panels'][$panelIndex]['Table'], $Values, TRUE);
		if ($q === FALSE) return $q;
		if (@strlen($q['Select']) > 0) {
			if (strlen($FieldList) > 0) $FieldList .= ', ';
			$FieldList .= $q['Select'];
		}
		if (@strlen($q['Where']) > 0) {
			if (strlen($RecordIndex) > 0) $RecordIndex .= ' AND ';
			$RecordIndex .= '(' . $q['Where'] . ')';
		}
	} // for f+
	
	$SQLQuery .= $FieldList . ' WHERE ' . $RecordIndex . ';';

	$result = $DB->Query($SQLQuery);
	if (($result === FALSE) || (@$result->Error() === TRUE)) {
		unset($result);
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	
	unset($result);
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return TRUE;
}

/**
 * Deletes a record from a panel's database table.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @param string The values of the index field of the record to get.
 * @param number If the record has manual sorting then this must be set to the records place number, otherwise it should be NULL.
 * @return boolean Is true on success or false on error.
 */
function DacomasyDeleteRecord(&$module, $panelIndex, $RecordIndex, $PlaceIndex) {
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	
	$DB = new DacoDBConnection($module['Server']['Hostname'], $module['Server']['Username'], $module['Server']['Password']);
	if ($DB->Connect() === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
		return FALSE;
	}
	
	if ($DB->SelectCatalog($module['Panels'][$panelIndex]['Database']) === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
		return FALSE;
	}
	
	$DelQuery = 'DELETE FROM ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' WHERE ' . DacoDBConnection::EscapeString($FieldSet[0]['Name']) . '=' . DacoDBConnection::Escape($RecordIndex);
	$oQuery = $DB->Query($DelQuery);
	if ($oQuery->Error() === TRUE) {
		echo 'ERRROR! ' . $DB->GetLastError();
		return FALSE;
	}
	
	if ($PlaceIndex != NULL) {
		for ($f = 0; $f < count($FieldSet); $f++) {
			if ($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_SUPERSORT) {
				$PlaceField = $FieldSet[$f]['Name'];
				break;
			}
		}
		$UpdateQuery = 'UPDATE ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::EscapeString($PlaceField) . '-1 WHERE (' . DacoDBConnection::EscapeString($PlaceField) . '>' . DacoDBConnection::Escape($PlaceIndex) . ')';
		$oQuery = $DB->Query($UpdateQuery);
		if (($oQuery->Error() === TRUE) && ($oQuery->AffectedRows  () == 0)) {
			echo 'ERRROR! ' . $DB->GetLastError();
			return FALSE;
		}
	}
	
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return TRUE;
}

/**
 * Moves a record up (back) in the manual sorting order.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @param number The value that indicates that current place of the record.
 * @return boolean Is true on success or false on error.
 */
function DacomasyMoveRecordUp(&$module, $panelIndex, $PlaceIndex) {
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	for ($f = 0; $f < count($FieldSet); $f++) {
		if ($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_SUPERSORT) {
			$PlaceField = $FieldSet[$f]['Name'];
			break;
		}
	}
	if (isset($PlaceField) === FALSE) {
		return FALSE;
	}
	
	$DB = new DacoDBConnection($module['Server']['Hostname'], $module['Server']['Username'], $module['Server']['Password']);
	if ($DB->Connect() === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
		return FALSE;
	}
	
	if ($DB->SelectCatalog($module['Panels'][$panelIndex]['Database']) === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
		return FALSE;
	}
	// Get the number of records...
	$Query = 'SELECT COUNT(' . DacoDBConnection::EscapeString($PlaceField) . ') AS RecordCount FROM ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']);
	echo '<p>' . $Query . '</p>';
	$rCount = $DB->Query($Query);
	if ($rCount->Error() === TRUE) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	if ($rCount->RowCount() > 0) {
		$rCount = $rCount->FetchNextRecord();
		$rCount = $rCount['RecordCount'];
	} else $rCount = 0;
	// Move the current record to the end.
	$Query = 'UPDATE ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($rCount) . ' WHERE ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($PlaceIndex);
	echo '<p>' . $Query . '</p>';
	$oResult = $DB->Query($Query);
	if ($oResult->Error() === TRUE) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	// Move the previous record to the current record's position.
	$Query = 'UPDATE ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($PlaceIndex) . ' WHERE ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($PlaceIndex - 1);
	echo '<p>' . $Query . '</p>';
	$oResult = $DB->Query($Query);
	if ($oResult->Error() === TRUE) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	// Move the current record to the previous record's position.
	$Query = 'UPDATE ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($PlaceIndex - 1) . ' WHERE ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($rCount);
	echo '<p>' . $Query . '</p>';
	$oResult = $DB->Query($Query);
	if ($oResult->Error() === TRUE) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return TRUE;
}

/**
 * Moves a record down (forward) in the manual sorting order.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @param number The value that indicates that current place of the record.
 * @return boolean Is true on success or false on error.
 */
function DacomasyMoveRecordDown(&$module, $panelIndex, $PlaceIndex) {
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	for ($f = 0; $f < count($FieldSet); $f++) {
		if ($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_SUPERSORT) {
			$PlaceField = $FieldSet[$f]['Name'];
			break;
		}
	}
	if (isset($PlaceField) === FALSE) {
		return FALSE;
	}
	
	$DB = new DacoDBConnection($module['Server']['Hostname'], $module['Server']['Username'], $module['Server']['Password']);
	if ($DB->Connect() === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
		return FALSE;
	}
	
	if ($DB->SelectCatalog($module['Panels'][$panelIndex]['Database']) === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
		return FALSE;
	}
	// Get the number of records...
	$Query = 'SELECT COUNT(' . DacoDBConnection::EscapeString($PlaceField) . ') AS RecordCount FROM ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']);
	echo '<p>' . $Query . '</p>';
	$rCount = $DB->Query($Query);
	if ($rCount->Error() === TRUE) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	if ($rCount->RowCount() > 0) {
		$rCount = $rCount->FetchNextRecord();
		$rCount = $rCount['RecordCount'];
	} else $rCount = 0;
	// Move the current record to the end.
	$Query = 'UPDATE ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($rCount) . ' WHERE ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($PlaceIndex);
	echo '<p>' . $Query . '</p>';
	$oResult = $DB->Query($Query);
	if ($oResult->Error() === TRUE) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	// Move the next record to the current record's position.
	$Query = 'UPDATE ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($PlaceIndex) . ' WHERE ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($PlaceIndex + 1);
	echo '<p>' . $Query . '</p>';
	$oResult = $DB->Query($Query);
	if ($oResult->Error() === TRUE) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	// Move the current record to the next record's position.
	$Query = 'UPDATE ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($PlaceIndex + 1) . ' WHERE ' . DacoDBConnection::EscapeString($PlaceField) . '=' . DacoDBConnection::Escape($rCount);
	echo '<p>' . $Query . '</p>';
	$oResult = $DB->Query($Query);
	if ($oResult->Error() === TRUE) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return TRUE;
}

/**
 * Changes the password of a record.
 *
 * @param array A loaded Dacomasy module.
 * @param number The panel index.
 * @param number The index value of the record.
 * @param string The new password to set the record to.
 * @return boolean Is true on success or false on error.
 */
function DacomasyChangeRecordPassword(&$module, $panelIndex, $RecordIndex, $NewPassword) {
	// Find the password field
	$FieldSet = DacomasyGetStructure($module, $panelIndex);
	for ($f = 0; $f < count($FieldSet); $f++) {
		if ($FieldSet[$f]['Type'] == DACOMASY_FIELDTYPE_PASSWORD) {
			$PassField = $FieldSet[$f]['Name'];
			break;
		}
	}
	if (isset($PassField) === FALSE) {
		return FALSE;
	}
	
	$DB = new DacoDBConnection($module['Server']['Hostname'], $module['Server']['Username'], $module['Server']['Password']);
	if ($DB->Connect() === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_CONNECTINGTOSQLSERVER);
		return FALSE;
	}
	
	if ($DB->SelectCatalog($module['Panels'][$panelIndex]['Database']) === FALSE) {
		DacomasySetLastError(__DACOMASY_ERROR_NOSUCHDATABASE);
		return FALSE;
	}
	
	$szQuery = 'UPDATE ' . DacoDBConnection::EscapeString($module['Panels'][$panelIndex]['Table']) . ' SET ' . DacoDBConnection::EscapeString($PassField) . '="' . DacoDBConnection::Escape(md5($NewPassword)) . '" WHERE ' . DacoDBConnection::EscapeString($FieldSet[0]['Name']) . '=' . DacoDBConnection::Escape($RecordIndex);
	$oResult = $DB->Query($szQuery);
	if ($oResult->Error() === TRUE) {
		DacomasySetLastError(__DACOMASY_ERROR_INVALIDQUERY);
		return FALSE;
	}
	
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return TRUE;
}

?>