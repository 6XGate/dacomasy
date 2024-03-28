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
 * Date/Time Field Implementation
 *
 * @package Dacomasy
 * @subpackage Tags
 * @version $SixXGate: webapps/dacomasy/www/system/tags/datetime.inc,v 1.1.1.1 2005/07/21 22:59:04 matthew Exp $
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @author 6XGate, Inc. <support@sixxgate.com>
 */

/**
 * Date/Time Field Class
 * @package Dacomasy
 * @ignore
 */
final class dacomasy_datetime implements IDacomasyField {
	static function GetFetchQuery (&$FieldDeclare, $TableName, $IsList = FALSE) {
		$q['Select'] = ''; $q['From'] = ''; $q['Where'] = ''; $q['Sort'] = '';
		$q['Select'] = DacoDBConnection::EscapeString($TableName) . '.' . DacoDBConnection::EscapeString($FieldDeclare['Name']);
		return $q;
	}
	
	static function GenerateField (&$FieldDeclare, &$Values, $IsEdit = FALSE) {
		$FormHTML = '<div>';
		switch ($FieldDeclare['Only']) {
		case 'date':
			$FormHTML .= '<label for="' . $FieldDeclare['Name'] . '" class="fieldDateTime">Date - ' . $FieldDeclare['Label'] . '</label>';
			$FormHTML .= '<input type="text" name="' . $FieldDeclare['Name'] . '" id="' . $FieldDeclare['Name'] . '" readonly class="fieldDateTime" value="' . $Values[ $FieldDeclare['Name'] ] . '">' . "\n";
			$FormHTML .= '<button name="' . $FieldDeclare['Name'] . '_trigger" id="' . $FieldDeclare['Name'] . '_trigger" type="reset" class="fieldDateTime">...</button>' . "\n";
			$FormHTML .= '<button name="' . $FieldDeclare['Name'] . '_clear" id="' . $FieldDeclare['Name'] . '_clear" type="reset" class="fieldDateTime">Clear</button>';
			$FormHTML .= '<script type="text/javascript"><!--
			Calendar.setup({
			inputField     :    "' . $FieldDeclare['Name'] . '",			// id of the input field
			ifFormat       :    "%Y-%m-%d",									// format of the input field
			button         :    "' . $FieldDeclare['Name'] . '_trigger",	// trigger for the calendar (button ID)
			align          :    "Bl",										// alignment (defaults to "Bl")
			singleClick    :    true
			});
			var oClear_' . $FieldDeclare['Name'] . ' = new Clearer("' . $FieldDeclare['Name'] . '", "' . $FieldDeclare['Name'] . '_clear");
			//--></script>';
			break;
		case 'time':
			$FormHTML .= '<label for="' . $FieldDeclare['Name'] . '" class="fieldDateTime">Time - ' . $FieldDeclare['Label'] . '</label>';
			$FormHTML .= '<input type="text" name="' . $FieldDeclare['Name'] . '" id="' . $FieldDeclare['Name'] . '" readonly class="fieldDateTime" value="' . $Values[ $FieldDeclare['Name'] ] . '"> ';
			$FormHTML .= '<button id="' . $FieldDeclare['Name'] . '_trigger" name="' . $FieldDeclare['Name'] . '_trigger" type="reset" class="fieldDateTime">...</button>' ."\n";
			$FormHTML .= '<button name="' . $FieldDeclare['Name'] . '_clear" id="' . $FieldDeclare['Name'] . '_clear" type="reset" class="fieldDateTime">Clear</button>';
			$FormHTML .= '
			<script type="text/javascript"><!--
				var oPicker_' . $FieldDeclare['Name'] . ' = new TimePicker();
				oPicker_' . $FieldDeclare['Name'] . '.Create("' . $FieldDeclare['Name'] . '", "' . $FieldDeclare['Name'] . '_trigger", _TIMEPICKER_MODE_12HOUR);
				var oClear_' . $FieldDeclare['Name'] . ' = new Clearer("' . $FieldDeclare['Name'] . '", "' . $FieldDeclare['Name'] . '_clear");
			//--></script>
			';
				break;
		default:
			$FormHTML .= '<label for="' . $FieldDeclare['Name'] . '" class="fieldDateTime">DT - ' . $FieldDeclare['Label'] . '</label>';
			$FormHTML .= '<input type="text" name="' . $FieldDeclare['Name'] . '" id="' . $FieldDeclare['Name'] . '" readonly class="fieldDateTime" value="' . $Values[ $FieldDeclare['Name'] ] . '">' . "\n";
			$FormHTML .= '<button name="' . $FieldDeclare['Name'] . '_trigger" id="' . $FieldDeclare['Name'] . '_trigger" type="reset" class="fieldDateTime">...</button>';
			$FormHTML .= '<button name="' . $FieldDeclare['Name'] . '_clear" id="' . $FieldDeclare['Name'] . '_clear" type="reset" class="fieldDateTime">Clear</button>';
			if ($Dacomasy_TimeMode & DACOMASY_TIMEMODE_12HOUR) $TimeString = '%I:%M %p';
			else $TimeString = '%H:%M';
			$FormHTML .= '<script type="text/javascript"><!--
			Calendar.setup({
			inputField     :    "' . $FieldDeclare['Name'] . '",			// id of the input field
			ifFormat       :    "%Y-%m-%d ' . $TimeString . '",				// format of the input field
			button         :    "' . $FieldDeclare['Name'] . '_trigger",	// trigger for the calendar (button ID)
			align          :    "Bl",										// alignment (defaults to "Bl")
			singleClick    :    true,
			showsTime      :    true
			});
			var oClear_' . $FieldDeclare['Name'] . ' = new Clearer("' . $FieldDeclare['Name'] . '", "' . $FieldDeclare['Name'] . '_clear");
			//--></script>';
		}
		$FormHTML .= "</div>\n";
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
		$field['Type'] = DACOMASY_FIELDTYPE_DATETIME;
		$field['Only'] = $DOMElement->getAttribute('only');
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
		// Build the regular expression to get the time currently in the input field
		// ([1-9][0-9]{3})-(1[0-2]|0[1-9])-(3[01]|[0-2][0-9])					// Date
		// (2[0-3]|[0-1]?[0-9]|):([0-5][0-9])									// 24-hour
		// (2[0-3]|[0-1]?[0-9]|):([0-5][0-9]):([0-5][0-9])						// 24-hour with seconds
		// (1[0-2]|0?[1-9]|):([0-5][0-9])\s?([Aa][Mm]|[Pp][Mm])					// 12-hour
		// (1[0-2]|0?[1-9]|):([0-5][0-9]):([0-5][0-9])\s?([Aa][Mm]|[Pp][Mm])	// 12-hour with seconds
		
		// Make sure the field has a value first... it may be allowed null
		if (strlen($Values[ $FieldDeclare['Name'] ]) > 0) {
			$RegExPat = '/^';
			switch ($FieldDeclare['Only']) {
			case 'date':
				$RegExPat .= '([1-9][0-9]{3})-(1[0-2]|0[1-9])-(3[01]|[0-2][0-9])';
				break;
			case 'time':
				if ($Dacomasy_TimeMode & DACOMASY_TIMEMODE_12HOUR) $RegExPat .= '(1[0-2]|0?[1-9]|)';
				else $RegExPat .= '(2[0-3]|[0-1]?[0-9]|)';
				$RegExPat .= ':([0-5][0-9])';
				if ($Dacomasy_TimeMode & DACOMASY_TIMEMODE_12HOUR) $RegExPat .= '\\s?([Aa][Mm]|[Pp][Mm])';
				break;
			default:
				$RegExPat .= '([1-9][0-9]{3})-(1[0-2]|0[1-9])-(3[01]|[0-2][0-9])\\s';
				if ($Dacomasy_TimeMode & DACOMASY_TIMEMODE_12HOUR) $RegExPat .= '(1[0-2]|0?[1-9]|)';
				else $RegExPat .= '(2[0-3]|[0-1]?[0-9]|)';
				$RegExPat .= ':([0-5][0-9])';
				if ($Dacomasy_TimeMode & DACOMASY_TIMEMODE_12HOUR) $RegExPat .= '\\s?([Aa][Mm]|[Pp][Mm])';
			}
			$RegExPat .= "$/";
			if (preg_match($RegExPat, $Values[ $FieldDeclare['Name'] ]) == 0) {
				if ($FieldDeclare['Only'] == 'date') $InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_INVALIDDATE], $FieldDeclare['Label']);
				elseif ($FieldDeclare['Only'] == 'time') $InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_INVALIDTIME], $FieldDeclare['Label']);
				else $InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_INVALIDDT], $FieldDeclare['Label']);
				return FALSE;
			}
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
$DacomasyField[DACOMASY_FIELDTYPE_DATETIME] = new dacomasy_datetime;
$DacomasyField['datetime'] = &$DacomasyField[DACOMASY_FIELDTYPE_DATETIME];

?>