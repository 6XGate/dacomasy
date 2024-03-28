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
 * Password Field Implementation
 *
 * @package Dacomasy
 * @subpackage Tags
 * @version $SixXGate: webapps/dacomasy/www/system/tags/password.inc,v 1.1.1.1 2005/07/21 22:59:04 matthew Exp $
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @author 6XGate, Inc. <support@sixxgate.com>
 */

/**
 * Password Field Class
 * @package Dacomasy
 * @ignore
 */
final class dacomasy_password implements IDacomasyField {
	static function GenerateField (&$FieldDeclare, &$Values, $IsEdit = FALSE) {
		global $__dacomasy__LABEL_res;
		if ($IsEdit === FALSE) {
			$FormHTML = '<fieldset class="fieldLink"><legend>' . $FieldDeclare['Label'] . '</legend>';
			if ($FieldDeclare['Minimum'] > 0) $FormHTML .= '<p>' . sprintf($__dacomasy__LABEL_res[__DACOMASY_LABEL_MINOF], $FieldDeclare['Minimum']) . '</p>';
			if ($FieldDeclare['Maximum'] > 0) $FormHTML .= '<p>' . sprintf($__dacomasy__LABEL_res[__DACOMASY_LABEL_MAXOF], $FieldDeclare['Maximum']) . '</p>';
			
			$FormHTML .= '<div><label for="DACO_' . $FieldDeclare['Name'] . '_password" class="fieldLink">Password</label>';
			$FormHTML .= '<input type="password" class="fieldLink" id="DACO_' . $FieldDeclare['Name'] . '_password" name="DACO_' . $FieldDeclare['Name'] . '_password" ';
			if ($FieldDeclare['Maximum'] > 0) $FormHTML .= 'maxlength="' . $FieldDeclare['Maximum'] . '"';
			
			$FormHTML .= '<div><label for="DACO_' . $FieldDeclare['Name'] . '_confirm" class="fieldLink">Confirm Password</label>';
			$FormHTML .= '<input type="password" class="fieldLink" id="DACO_' . $FieldDeclare['Name'] . '_confirm" name="DACO_' . $FieldDeclare['Name'] . '_confirm" ';
			if ($FieldDeclare['Maximum'] > 0) $FormHTML .= 'maxlength="' . $FieldDeclare['Maximum'] . '"';
			$FormHTML .= "></div>\n";
	
			$FormHTML .= "</fieldset>\n";
			return $FormHTML;
		} else return '';
	}
	
	static function GetPostValues (&$FieldDeclare, &$Values) {
		@$Values[ 'DACO_' . $FieldDeclare['Name'] . '_password' ] = $_POST[ 'DACO_' . $FieldDeclare['Name'] . '_password' ];
		@$Values[ 'DACO_' . $FieldDeclare['Name'] . '_confirm' ] = $_POST[ 'DACO_' . $FieldDeclare['Name'] . '_confirm' ];
		return TRUE;
	}
	
	static function PrepareValues (&$FieldDeclare, &$Values) {
		$Values[ $FieldDeclare['Name'] ] = $Values[ 'DACO_' . $FieldDeclare['Name'] . '_password' ];
		unset($Values[ 'DACO_' . $FieldDeclare['Name'] . '_password' ]);
		unset($Values[ 'DACO_' . $FieldDeclare['Name'] . '_confirm' ]);
	}
	
	static function GetFieldTypeInfo () {
		
	}
	
	static function CreateFieldDeclaration (&$DOMElement, $module, $panelIndex) {
		DacomasyGetCommonFieldData($DOMElement, $field);		
		$field['Type'] = DACOMASY_FIELDTYPE_PASSWORD;
		$field['Maximum'] = $DOMElement->getAttribute('max');
		$field['Minimum'] = $DOMElement->getAttribute('min');
		return $field;
	}
	
	static function GetSetQuery(&$FieldDeclare, $TableName, &$Values, $IsEdit = FALSE) {
		if ($IsEdit === FALSE) {
			$q['Select'] = DacoDBConnection::EscapeString($FieldDeclare['Name']) . '=';
			if (strlen($Values[ $FieldDeclare['Name'] ]) > 0) {
				$q['Select'] .= '"' . DacoDBConnection::EscapeString( md5($Values[ $FieldDeclare['Name'] ]) ) . '"';
			} else {
				$q['Select'] .= 'NULL';
			}
			return $q;
		} else return;
	}
	
	static function ValidateValues(&$FieldDeclare, &$Values, &$InvalidMsg, $IsEdit = FALSE) {
		global $__dacomasy__MSG_res;
		if ($IsEdit === FALSE) {
			if (@$Values[ 'DACO_' . $FieldDeclare['Name'] . '_password' ] != @$Values[ 'DACO_' . $FieldDeclare['Name'] . '_confirm' ]) {
				$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_PWDNOTMATCH], $FieldDeclare['Label']);
				return FALSE;
			}
			if (($FieldDeclare['Maximum'] > 0) && (empty($FieldDeclare['Maximum']) === FALSE)){
				if (strlen($Values[ 'DACO_' . $FieldDeclare['Name'] . '_password' ]) > $FieldDeclare['Maximum']) {
					$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_PWDTOOBIG], $FieldDeclare['Label']);
					return FALSE;
				}
			}
			if (($FieldDeclare['Minimum'] > 0) && (empty($FieldDeclare['Minimum']) === FALSE )){
				if (strlen($Values[ 'DACO_' . $FieldDeclare['Name'] . '_password' ]) < $FieldDeclare['Minimum']) {
					$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_PWDTOOSMALL], $FieldDeclare['Label']);
					return FALSE;
				}
			}
			if ($FieldDeclare['AllowNull'] === FALSE) {
				if (strlen($Values[ 'DACO_' . $FieldDeclare['Name'] . '_password' ]) < 1) {
					$InvalidMsg[ $FieldDeclare['Name'] ] = sprintf($__dacomasy__MSG_res[__DACOMASY_MSG_NONULL], $FieldDeclare['Label']);
					return FALSE;
				}
			}
		}
		// TODO: Add password code for field validation.
		return TRUE;
	}
	
	// Placeholders
	static function GetRecordSetField(&$FieldDeclare, &$RecordSet) {}
	static function GetRecordSetRecordField(&$FieldDeclare, &$RecordSet, &$Record, $RecordIndex) {}
	static function UnprepareValues (&$FieldDeclare, &$Values) {}
	static function GetRecordValues(&$FieldDeclare, &$RecordArray, &$Values) {}
	static function GetFetchQuery (&$FieldDeclare, $TableName, $IsList = FALSE) {}
}

// Needed to add the class
$DacomasyField[DACOMASY_FIELDTYPE_PASSWORD] = new dacomasy_password;
$DacomasyField['password'] = &$DacomasyField[DACOMASY_FIELDTYPE_PASSWORD];

?>