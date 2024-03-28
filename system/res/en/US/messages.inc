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
 * Contains interface strings and messages in English
 *
 * @package Dacomasy
 * @subpackage Resources
 * @version $SixXGate: webapps/dacomasy/www/system/res/en/US/messages.inc,v 1.1.1.1 2005/07/21 22:57:33 matthew Exp $
 * @ignore
 */

// Misc Messages
$__dacomasy__MSG_res[__DACOMASY_MSG_ADDFAILED] =						'Failed to add record.';
$__dacomasy__MSG_res[__DACOMASY_MSG_ADDSUCCESS] =						'Successfully added record.';
$__dacomasy__MSG_res[__DACOMASY_MSG_EDITFAILED] =						'Failed to update record.';
$__dacomasy__MSG_res[__DACOMASY_MSG_EDITSUCCESS] =					'Successfully updated record.';
$__dacomasy__MSG_res[__DACOMASY_MSG_DELFAILED] =						'Failed to delete record.';
$__dacomasy__MSG_res[__DACOMASY_MSG_DELSUCCESS] =						'Successfully deleted record.';
$__dacomasy__MSG_res[__DACOMASY_MSG_MOVEFAILED] =						'Failed to move record.';

// Field validation for all fields
$__dacomasy__MSG_res[__DACOMASY_MSG_FORMINVALID] = 						'You have invalid entries.';
$__dacomasy__MSG_res[__DACOMASY_MSG_NONULL] =							'%1$s cannot be empty.';

// Text field validation
$__dacomasy__MSG_res[__DACOMASY_MSG_TEXTTOOBIG] =						'%1$s is too long.';
$__dacomasy__MSG_res[__DACOMASY_MSG_PWDTOOBIG] =						'Password is too long.';
$__dacomasy__MSG_res[__DACOMASY_MSG_PWDTOOSMALL] =						'Password is too short.';
$__dacomasy__MSG_res[__DACOMASY_MSG_PWDNOTMATCH] =						'The passwords do not match.  To confirm your password you, must type it in both fields exactly.';
$__dacomasy__MSG_res[__DACOMASY_MSG_LINKNONULL] =						'Link for %s cannot be empty.';

// File field validation
$__dacomasy__MSG_res[__DACOMASY_MSG_FILETOOBIG] =						'%1$s is too big, it must smaller than %2$.1fKB.';
$__dacomasy__MSG_res[__DACOMASY_MSG_NOTAIMAGE] =						'%1$s must be and image file.';

// Numeric field validation
$__dacomasy__MSG_res[__DACOMASY_MSG_NUMTOOBIG] =						'%1$s is too big.';
$__dacomasy__MSG_res[__DACOMASY_MSG_NUMTOOSMALL] =						'%1$s is too small.';
$__dacomasy__MSG_res[__DACOMASY_MSG_NOTANUMBER] =						'%1$s must only be a number.';
$__dacomasy__MSG_res[__DACOMASY_MSG_TOOMANYDECIMAL] =					'%1$s has too many decimal places.';

// List field validation
$__dacomasy__MSG_res[__DACOMASY_MSG_INVALIDSELECTION] = 				'Invalid selection in %1$s.';

// Date/Time field validation
$__dacomasy__MSG_res[__DACOMASY_MSG_INVALIDDATE] = 						'Invalid date in %1$s.';
$__dacomasy__MSG_res[__DACOMASY_MSG_INVALIDTIME] = 						'Invalid time in %1$s.';
$__dacomasy__MSG_res[__DACOMASY_MSG_INVALIDDT] = 						'Invalid date and/or time in %1$s.';


?>