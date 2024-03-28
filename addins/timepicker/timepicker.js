//////////////////////////////////////////////////////////////////////////////
// timepicker.js - TimePicker Script
//////////////////////////////////////////////////////////////////////////////
// Copyright (C)2005 6XGate Incorporated
//
// This file is part of TimePicker
//
// TimePicker is free software; you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// TimePicker is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with RegistryClass; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
/////////////////////////////////////////////////////////////////////////////
// $SixXGate: webapps/dacomasy/www/addins/timepicker/timepicker.js,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
// Define a few constants
var _TIMEPICKER_MODE_24HOUR = 0;
var _TIMEPICKER_MODE_12HOUR = 1;
var _TIMEPICKER_MODE_SECONDS = 2;

// Start the TimePicker object with some defaults.
function TimePicker () {
	// Initialize global variables
	var _Mode =					_TIMEPICKER_MODE_24HOUR			// Default in 24-hour mode

	// Status
	var _IsOpen =				false;							// Indicates if the picker is shown

	// The elements to picker will manipulate
	var _InputField =			null;							// The input field to store the time in
	var _PickerTrigger =		null;							// The element that will show the picker

	// The picker itself
	var _PickerHour = 			null;							// The hour picker element
	var _PickerMinute =			null;							// The minute picker element
	var _PickerSecond =			null;							// The second picker element
	var _PickerAMPM =			null;							// The AM/PM picker element
	var _PickerClose =			null;							// The picker close element
	var _PickerMain =			null;							// The root picker element

	// Event Handler Objects
	var _PickerHourHandle =		null;							// The hour picker handler object
	var _PickerMinuteHandle =	null;							// The minute picker handler object
	var _PickerSecondHandle =	null;							// The second picker handler object
	var _PickerAMPMHandle =		null;							// The AM/PM picker handler object

	this.Create = function(szFieldId, szTriggerId, fMode, szTimeFormat) {
		// Only works on DOM Level 1 Compliant Browsers (IE5+, NS5+, Opera?+, KHTML)
		if (document.getElementsByTagName) {
			if ((typeof szFieldId == 'string') && (typeof szTriggerId == 'string'))
			if ((szFieldId.length > 0) && (szTriggerId.length > 0)) {

				// Find the input field, and make sure it is a input field
				_InputField = document.getElementById(szFieldId);
				_PickerTrigger = document.getElementById(szTriggerId);

				// Make sure that we found BOTH elements
				if ((_InputField == null) || (_PickerTrigger == null)) return false;

				// Make sure the elements are the right type
				if (_InputField.tagName.toLowerCase() != 'input') return false;

				// Make sure the field is either text or hidden.
				if ((_InputField.getAttribute('type') != 'hidden') && (_InputField.getAttribute('type') != 'text')) return false;

				_Mode = fMode;
				var tnode;

				// Create the picker, piece by piece
				_PickerMain = document.createElement('p');
				_PickerMain.className = 'TimePickerBody';

				// Hour field
				_PickerHour = document.createElement('span');
				_PickerHour.className = 'TimePickerField';
				tnode = document.createTextNode('01');
				if (fMode & _TIMEPICKER_MODE_12HOUR) _PickerHourHandle = new HourPicker12(12, tnode, _PickerHour, this.EventHandleOnChnage);
				else _PickerHourHandle = new HourPicker24(0, tnode, _PickerHour, this.EventHandleOnChnage);
				_PickerHour.onmouseup = _PickerHourHandle.EventHandleMouseUp;
				_PickerHour.onmousedown = _PickerHourHandle.EventHandleMouseDown;
				_PickerHour.onmouseover = _PickerHourHandle.EventHandleMouseOver;
				_PickerHour.onmouseout = _PickerHourHandle.EventHandleMouseOut;
				_PickerHour.appendChild(tnode);
				_PickerHour.setAttribute('unselectable', true);

				// Minute field
				_PickerMinute = document.createElement('span');
				_PickerMinute.className = 'TimePickerField';
				tnode = document.createTextNode('00');
				_PickerMinuteHandle = new MinutePicker(0, tnode, _PickerMinute, this.EventHandleOnChnage);
				_PickerMinute.onmouseup = _PickerMinuteHandle.EventHandleMouseUp;
				_PickerMinute.onmousedown = _PickerMinuteHandle.EventHandleMouseDown;
				_PickerMinute.onmouseover = _PickerMinuteHandle.EventHandleMouseOver;
				_PickerMinute.onmouseout = _PickerMinuteHandle.EventHandleMouseOut;
				_PickerMinute.appendChild(tnode);
				_PickerMinute.setAttribute('unselectable', true);

				// Add these to the body
				_PickerMain.appendChild(_PickerHour);
				tnode = document.createTextNode(' : ');
				_PickerMain.appendChild(tnode);
				_PickerMain.appendChild(_PickerMinute);

				// Secord field
				if (fMode & _TIMEPICKER_MODE_SECONDS) {
					_PickerSecond = document.createElement('span');
					_PickerSecond.className = 'TimePickerField';
					tnode = document.createTextNode('00');
					_PickerSecondHandle = new MinutePicker(0, tnode, _PickerSecond, this.EventHandleOnChnage);
					_PickerSecond.onmouseup = _PickerSecondHandle.EventHandleMouseUp;
					_PickerSecond.onmousedown = _PickerSecondHandle.EventHandleMouseDown;
					_PickerSecond.onmouseover = _PickerSecondHandle.EventHandleMouseOver;
					_PickerSecond.onmouseout = _PickerSecondHandle.EventHandleMouseOut;
					_PickerSecond.appendChild(tnode);
					_PickerSecond.setAttribute('unselectable', true);

					tnode = document.createTextNode(' : ');
					_PickerMain.appendChild(tnode);
					_PickerMain.appendChild(_PickerSecond);
				}

				// AMFM field
				if (fMode & _TIMEPICKER_MODE_12HOUR) {
					_PickerAMPM = document.createElement('span');
					_PickerAMPM.className = 'TimePickerField';
					tnode = document.createTextNode('AM');
					_PickerAMPMHandle = new AMPMPicker('AM', tnode, _PickerAMPM, this.EventHandleOnChnage);
					_PickerAMPM.onmouseup = _PickerAMPMHandle.EventHandleMouseUp;
					_PickerAMPM.onmousedown = _PickerAMPMHandle.EventHandleMouseDown;
					_PickerAMPM.onmouseover = _PickerAMPMHandle.EventHandleMouseOver;
					_PickerAMPM.onmouseout = _PickerAMPMHandle.EventHandleMouseOut;
					_PickerAMPM.appendChild(tnode);
					_PickerAMPM.setAttribute('unselectable', true);

					tnode = document.createTextNode(' ');
					_PickerMain.appendChild(tnode);
					_PickerMain.appendChild(_PickerAMPM);
				}

				_PickerMain.style.position='absolute';
				var pos = getElementPos(_InputField);
				_PickerMain.style.left = pos.Left + 'px';
				_PickerMain.style.top = (pos.Top + pos.Height) + 'px';
				_PickerMain.style.width = pos.Width + 'px';
				_PickerMain.style.MozUserSelect = 'none';
				_PickerMain.setAttribute('unselectable', true);

				_PickerTrigger.onclick = this.EventHandleOnTrigger;
				TimePicker.addEvent(document.documentElement, 'click', this.CloseWhenDone);

				_PickerMain.style.visibility = 'hidden';

				_InputField.parentNode.appendChild(_PickerMain);

			} else return false; // End of ((typeof.../((szFieldId...
		} else return true;	// End of (document.getElementsByTagName)
		return true;
	}; // End of Create()

	this.EventHandleOnChnage = function () {
		_InputField.value = _PickerHourHandle.GetValue() + ':' + _PickerMinuteHandle.GetValue() + ((_Mode & _TIMEPICKER_MODE_SECONDS) ? (':' + _PickerSecondHandle.GetValue()) : '')  + ((_Mode & _TIMEPICKER_MODE_12HOUR) ? (' ' + _PickerAMPMHandle.GetValue()) : '');
	}; // End of EventHandleOnChnage function

	this.EventHandleOnTrigger = function (ev) {
		if (_InputField.value.length > 0) {
			
			// Build the regular expression to get the time currently in the input field
			// ^(2[0-3]|[0-1]?[0-9]|):([0-5][0-9])$										// 24-hour
			// ^(2[0-3]|[0-1]?[0-9]|):([0-5][0-9]):([0-5][0-9])$						// 24-hour with seconds
			// ^(1[0-2]|0?[1-9]|):([0-5][0-9])\s?([Aa][Mm]|[Pp][Mm])$					// 12-hour
			// ^(1[0-2]|0?[1-9]|):([0-5][0-9]):([0-5][0-9])\s?([Aa][Mm]|[Pp][Mm])$		// 12-hour with seconds
	
			// Beginning
			var TimeBreaker = '^';
			// 12- or 24-hour
			if (_Mode & _TIMEPICKER_MODE_12HOUR) TimeBreaker += '(1[0-2]|0?[1-9]|)';
			else TimeBreaker += '(2[0-3]|[0-1]?[0-9]|)';
			// Minutes
			TimeBreaker += ':([0-5][0-9])';
			// Seconds or not
			if (_Mode & _TIMEPICKER_MODE_SECONDS) TimeBreaker += ':([0-5][0-9])';
			// 12-hour AM/PM
			if (_Mode & _TIMEPICKER_MODE_12HOUR) TimeBreaker += '\\s?([Aa][Mm]|[Pp][Mm])';
			// Ending
			TimeBreaker += '$';
			// It is now build...
			
			TimeBreaker = _InputField.value.match(TimeBreaker);
			if (TimeBreaker == null) {
				alert('Invalid Time');
				return false;
			}
			
			var nHour, nMinutes, nSeconds, szAMPM, nIndex = 3;
			nHour = parseInt(TimeBreaker[1], 10);
			nMinutes = parseInt(TimeBreaker[2], 10);
			if (_Mode & _TIMEPICKER_MODE_SECONDS) {
				nSeconds = parseInt(TimeBreaker[nIndex], 10);
				nIndex++;
			}
			if (_Mode & _TIMEPICKER_MODE_12HOUR) {
				TimeBreaker[nIndex].toUpperCase();
				szAMPM = TimeBreaker[nIndex].toUpperCase();
			}
	
			_PickerHourHandle.SetIntValue(nHour);
			_PickerMinuteHandle.SetIntValue(nMinutes);
			if (_Mode & _TIMEPICKER_MODE_SECONDS) _PickerSecondHandle.SetIntValue(nSeconds);
			if (_Mode & _TIMEPICKER_MODE_12HOUR) _PickerAMPMHandle.SetValue(szAMPM);

		} else { // _InputField.value.length > 0
			if (_Mode & _TIMEPICKER_MODE_12HOUR) _PickerHourHandle.SetIntValue(12);
			else _PickerHourHandle.SetIntValue(0);
			_PickerMinuteHandle.SetIntValue(0);
			if (_Mode & _TIMEPICKER_MODE_SECONDS) _PickerSecondHandle.SetIntValue(0);
			if (_Mode & _TIMEPICKER_MODE_12HOUR) _PickerAMPMHandle.SetValue('AM');
		}  // _InputField.value.length > 0
		
		_PickerMain.style.visibility = 'visible';
		TimePicker.stopEvent(ev);
	}; // End of EventHandleOnTrigger

	this.CloseWhenDone = function (ev) {
		ev = (ev ? ev : window.event);
		var target
		if (ev.target) target = ev.target; else target = ev.srcElement;
		// Lets make sure we are not in the TimePicker
		while (target.parentNode) {
			if (target != _PickerMain) target = target.parentNode;
			if (target == _PickerMain) return;
		}

		_PickerMain.style.visibility = 'hidden';
	} // End of CloseWhenDone;

}; // End of TimePicker Object

// Gets the left and top position of an element
function getElementPos(elementObject) {
	var retObj = {
		Left: 0,
		Top: 0,
		Width: elementObject.offsetWidth,
		Height: elementObject.offsetHeight
	}

	var curObj = elementObject;

	if (curObj.offsetParent) {
		while (curObj.offsetParent) {
			retObj.Left += curObj.offsetLeft;
			retObj.Top += curObj.offsetTop;
			curObj = curObj.offsetParent;
		}
	} else return false;
	return retObj;
}

function HourPicker24 (nCurrentHour, objTextNode, objFieldNode, fnChangeEvent) {
	var _CurrentHour = nCurrentHour;
	var _TextNode = objTextNode;
	var _FieldNode = objFieldNode;
	var _ChangeEvent = fnChangeEvent;

	if (_CurrentHour < 10) _TextNode.data = '0' + _CurrentHour.toString();
	else _TextNode.data = _CurrentHour.toString();

	this.EventHandleMouseOver = function() { _FieldNode.id = 'TimePickerSelected'; };
	this.EventHandleMouseOut = function() { _FieldNode.id = null; };
	this.EventHandleMouseDown = function() { _FieldNode.id = 'TimePickerActive'; };
	this.EventHandleMouseUp = function (ev) {
		_FieldNode.id = 'TimePickerSelected'
		_CurrentHour++;
		if (_CurrentHour > 23) _CurrentHour = 0;
		if (_CurrentHour < 10) _TextNode.data = '0' + _CurrentHour.toString();
		else _TextNode.data = _CurrentHour.toString();
		_ChangeEvent();
		TimePicker.stopEvent(ev);
	};

	this.GetValue = function() {
		if (_CurrentHour < 10) 	return '0' + _CurrentHour.toString();
		else return _CurrentHour.toString();
	};

	this.SetIntValue = function(nValue) {
		if ((nValue > 23) || (nValue < 0)) return false;
		_CurrentHour = nValue;
		if (_CurrentHour < 10) _TextNode.data = '0' + _CurrentHour.toString();
		else _TextNode.data = _CurrentHour.toString();
	};
	
	this.GetIntValue = function() {
		return _CurrentHour;
	};
}

function HourPicker12 (nCurrentHour, objTextNode, objFieldNode, fnChangeEvent) {
	var _CurrentHour = nCurrentHour;
	var _TextNode = objTextNode;
	var _FieldNode = objFieldNode;
	var _ChangeEvent = fnChangeEvent;

	if (_CurrentHour < 10) _TextNode.data = '0' + _CurrentHour.toString();
	else _TextNode.data = _CurrentHour.toString();

	this.EventHandleMouseOver = function() { _FieldNode.id = 'TimePickerSelected'; };
	this.EventHandleMouseOut = function() { _FieldNode.id = null; };
	this.EventHandleMouseDown = function() { _FieldNode.id = 'TimePickerActive'; };
	this.EventHandleMouseUp = function (ev) {
		_FieldNode.id = 'TimePickerSelected'
		_CurrentHour++;
		if (_CurrentHour > 12) _CurrentHour = 1;
		if (_CurrentHour < 10) _TextNode.data = '0' + _CurrentHour.toString();
		else _TextNode.data = _CurrentHour.toString();
		_ChangeEvent();
		TimePicker.stopEvent(ev);
	};

	this.GetValue = function () {
		if (_CurrentHour < 10) 	return '0' + _CurrentHour.toString();
		else return _CurrentHour.toString();
	};

	this.SetIntValue = function(nValue) {
		if ((nValue > 12) || (nValue < 1)) return false;
		_CurrentHour = nValue;
		if (_CurrentHour < 10) _TextNode.data = '0' + _CurrentHour.toString();
		else _TextNode.data = _CurrentHour.toString();
	};
	
	this.GetIntValue = function() {
		return _CurrentHour;
	};
}

function MinutePicker (nCurrentMinute, objTextNode, objFieldNode, fnChangeEvent) {
	var _CurrentMinute = nCurrentMinute;
	var _TextNode = objTextNode;
	var _FieldNode = objFieldNode;
	var _ChangeEvent = fnChangeEvent;

	if (_CurrentMinute < 10) _TextNode.data = '0' + _CurrentMinute.toString();
	else _TextNode.data = _CurrentMinute.toString();

	this.EventHandleMouseOver = function() { _FieldNode.id = 'TimePickerSelected'; };
	this.EventHandleMouseOut = function() { _FieldNode.id = null; };
	this.EventHandleMouseDown = function() { _FieldNode.id = 'TimePickerActive'; };
	this.EventHandleMouseUp = function (ev) {
		_FieldNode.id = 'TimePickerSelected'
		_CurrentMinute++;
		if (_CurrentMinute > 59) _CurrentMinute = 0;
		if (_CurrentMinute < 10) _TextNode.data = '0' + _CurrentMinute.toString();
		else _TextNode.data = _CurrentMinute.toString();
		_ChangeEvent();
		TimePicker.stopEvent(ev);
	};

	this.GetValue = function () {
		if (_CurrentMinute < 10) return '0' + _CurrentMinute.toString();
		else return _CurrentMinute.toString();
	};

	this.SetIntValue = function(nValue) {
		if ((nValue > 59) || (nValue < 0)) return false;
		_CurrentMinute = nValue;
		if (_CurrentMinute < 10) _TextNode.data = '0' + _CurrentMinute.toString();
		else _TextNode.data = _CurrentMinute.toString();
	};
	
	this.GetIntValue = function() {
		return _CurrentMinute;
	};
}

function SecondPicker (nCurrentSecond, objTextNode, objFieldNode, fnChangeEvent) {
	var _CurrentSecond = nCurrentSecond;
	var _TextNode = objTextNode;
	var _FieldNode = objFieldNode;
	var _ChangeEvent = fnChangeEvent;

	if (_CurrentSecond < 10) _TextNode.data = '0' + _CurrentSecond.toString();
	else _TextNode.data = _CurrentSecond.toString();

	this.EventHandleMouseOver = function() { _FieldNode.id = 'TimePickerSelected'; };
	this.EventHandleMouseOut = function() { _FieldNode.id = null; };
	this.EventHandleMouseDown = function() { _FieldNode.id = 'TimePickerActive'; };
	this.EventHandleMouseUp = function (ev) {
		_FieldNode.id = 'TimePickerSelected'
		_CurrentSecond++;
		if (_CurrentSecond > 59) _CurrentSecond = 0;
		if (_CurrentSecond < 10) _TextNode.data = '0' + _CurrentSecond.toString();
		else _TextNode.data = _CurrentSecond.toString();
		_ChangeEvent();
		TimePicker.stopEvent(ev);
	};

	this.GetValue = function () {
		if (_CurrentSecond < 10) 	return '0' + _CurrentSecond.toString();
		else return _CurrentSecond.toString();
	};

	this.SetIntValue = function(nValue) {
		if ((nValue > 59) || (nValue < 0)) return false;
		_CurrentSecond = nValue;
		if (_CurrentSecond < 10) _TextNode.data = '0' + _CurrentSecond.toString();
		else _TextNode.data = _CurrentSecond.toString();
	};
	
	this.GetIntValue = function() {
		return _CurrentSecond;
	};
}

function AMPMPicker (szCurrentHour, objTextNode, objFieldNode, fnChangeEvent) {
	var _CurrentHour = szCurrentHour;
	var _TextNode = objTextNode;
	var _FieldNode = objFieldNode;
	var _ChangeEvent = fnChangeEvent;

	if ((_CurrentHour == 'AM') ||  (_CurrentHour == 'PM')) _TextNode.data = _CurrentHour;
	else _TextNode.data = 'AM';

	this.EventHandleMouseOver = function() { _FieldNode.id = 'TimePickerSelected'; };
	this.EventHandleMouseOut = function() { _FieldNode.id = null; };
	this.EventHandleMouseDown = function() { _FieldNode.id = 'TimePickerActive'; };
	this.EventHandleMouseUp = function (ev) {
		_FieldNode.id = 'TimePickerSelected'
		if (_CurrentHour == 'PM') {
			_CurrentHour = 'AM';
		} else {
			_CurrentHour = 'PM';
		}
		_TextNode.data = _CurrentHour;
		_ChangeEvent();
		TimePicker.stopEvent(ev);
	};

	this.GetValue = function () { return _CurrentHour; };
	this.SetValue = function (szValue) {
		if ((szValue != 'AM') && (szValue != 'PM')) return false;
		_CurrentHour = szValue;
		_TextNode.data = _CurrentHour;
	}
}

TimePicker.addEvent = function(objElement, szEvent, fnEventHandle) {
	if (objElement.attachEvent) objElement.attachEvent('on' + szEvent, fnEventHandle);
	else if (objElement.addEventListener) objElement.addEventListener(szEvent, fnEventHandle, true);
	else objElement['on' + szEvent] = fnEventHandle;
}

TimePicker.removeEvent = function(objElement, szEvent, fnEventHandle) {
	if (objElement.detachEvent) objElement.detachEvent('on' + szEvent, fnEventHandle);
	else if (objElement.removeEventListener) objElement.removeEventListener(szEvent, fnEventHandle, true);
	else objElement['on' + szEvent] = null;
}

TimePicker.stopEvent = function(ev) {
	ev = (ev ? ev : window.event);
	if (ev.stopPropagation) {
		ev.preventDefault();
		ev.stopPropagation();
	} else {
		ev.cancelBubble = true;
		ev.returnValue = false;
	}
}
