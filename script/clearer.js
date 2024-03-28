//////////////////////////////////////////////////////////////////////////////
// clearer.js - Attaches an event to an element that will clear a single form
//              field
//////////////////////////////////////////////////////////////////////////////
// Copyright (C)2005 6XGate Incorporated
//
// This file is part of Dacomasy
//
// Dacomasy is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// Dacomasy is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with RegistryClass; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// $SixXGate: webapps/dacomasy/www/script/clearer.js,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
//
/////////////////////////////////////////////////////////////////////////////

function Clearer(szInputFieldID, szClearTriggerID) {
	// Private members
	var _InputField;
	var _ClearTrigger;

	var stopEvent = function(ev) {
		ev = (ev ? ev : window.event);
		if (ev.stopPropagation) {
			ev.preventDefault();
			ev.stopPropagation();
		} else {
			ev.cancelBubble = true;
			ev.returnValue = false;
		}
	};

	// Public Members
	this.ClearField = function(ev) {
		_InputField.value = '';
		stopEvent(ev);	
	};
	
	// Only works on DOM Level 1 Compliant Browsers (IE5+, NS5+, Opera?+, KHTML)
	if (document.getElementsByTagName) {
		if ((typeof szInputFieldID == 'string') && (typeof szClearTriggerID == 'string'))
		if ((szInputFieldID.length > 0) && (szClearTriggerID.length > 0)) {

			// Find the input field, and make sure it is a input field
			_InputField = document.getElementById(szInputFieldID);
			_ClearTrigger = document.getElementById(szClearTriggerID);
	
			// Make sure that we found BOTH elements
			if ((_InputField == null) || (_ClearTrigger == null)) return null;
	
			// Make sure the elements are the right type
			if (_InputField.tagName.toLowerCase() != 'input') return null;
	
			// Make sure the field is either text or hidden.
			if ((_InputField.getAttribute('type') != 'hidden') && (_InputField.getAttribute('type') != 'text')) return null;
			
			_ClearTrigger.onclick = this.ClearField;
		} else return null;
	}
	
	return;
}; // End of Clearer Object
