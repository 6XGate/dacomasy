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
 * These routines provide module information collection capability.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Module
 * @version $SixXGate: webapps/dacomasy/www/system/lib/module.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

class _Server
{
	var $Username;
	var $Password;
	var $Hostname;
}

class CModule
{
	var $Name;				// The name of module
	var $Description;		// The long description of the module's use
	var $Tooltip;			// The short description of the module's use
	var $Filename;			// The filename of the module
	var $Server;			// The server information
	var $Panels				// An array of panel classes
	function CModule()
	{
		$this->Server = new _Server;
	}
}
 
/**
 * Generates an array of currently installed modules and the panels in them.
 *
 * @return array The module and panel list.
 */
function DacomasyListModules () {
	// Initialize a few variables
	unset($ModList);
	$ModNum = 0;
	$filename = '';
	
	// Get a list of XML files in the modules directory
	$Modules = glob('system/modules/*.xml');
	
	// Now lets step through that list and confirm that each file is a module and add it to the
	// module list.
	foreach ($Modules as $filename) {
		// Load and parse the module into the module list.
		$module = DacomasyLoadModule(basename($filename));
		if ($module != FALSE) {
			$ModList[$ModNum]['Name'] = $module['Name'];
			$ModList[$ModNum]['Filename'] = basename($filename);
			$ModList[$ModNum]['Tooltip'] = $module['Tooltip'];
			$ModList[$ModNum]['Description'] = $module['Description'];
			for ($i = 0; $i < count ($module['Panels']); $i++) {
				$ModList[$ModNum]['Panels'][$i]['Name'] = $module['Panels'][$i]['Name'];
				$ModList[$ModNum]['Panels'][$i]['Tooltip'] = $module['Panels'][$i]['Tooltip'];
				$ModList[$ModNum]['Panels'][$i]['Description'] = $module['Panels'][$i]['Description'];
			}
			
			$ModNum++;
		} // $module == FALSE
	}
	
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return $ModList;
}

// Loads a module for use by other Dacomasy functions.
/**
 * Loads a Dacomasy module file.
 *
 * @param string The filename of the Dacomasy module.  No path is needed since all module must be in the "modules" directory.
 * @return array A DacomasyModule structure.
 */
function DacomasyLoadModule ($moduleFilename) {
	// Setup error handling
	$ErrMode = error_reporting(E_WARNING | E_NOTICE);
	set_error_handler('DacomasyErrorHandler', E_WARNING | E_NOTICE);
	
	// Create a new DOMDocument, load the document
	$moduleDoc = new DOMDocument();	
	if ($moduleDoc->load('system/modules/' . $moduleFilename) == false) {
		$Errs = DacomasyGetCaughtErrors();
		$ExtErr = '';
		foreach ($Errs as $ErrLine) $ExtErr .= strip_tags($ErrLine) . '<br>';
		restore_error_handler();
		error_reporting($ErrMode);
		DacomasySetExtendedErrorMsg($ExtErr);
		DacomasySetLastError(__DACOMASY_ERROR_MODULENOTFOUND);
		return FALSE;
	}
	
	// Validate the document's structure
	if ($moduleDoc->schemaValidate('module.xsd') == false) {
		$Errs = DacomasyGetCaughtErrors();
		$ExtErr = '';
		foreach ($Errs as $ErrLine) $ExtErr .= strip_tags($ErrLine) . '<br>';
		restore_error_handler();
		error_reporting($ErrMode);
		DacomasySetExtendedErrorMsg($ExtErr);
		DacomasySetLastError(__DACOMASY_ERROR_MODULENOTVALID);
		return FALSE;
	}
	// Load the Head and Panels tags
	for ($i = 0; $i < $moduleDoc->documentElement->childNodes->length; $i++) {
		if (get_class($moduleDoc->documentElement->childNodes->item($i)) == 'DOMElement') {
			switch ($moduleDoc->documentElement->childNodes->item($i)->tagName) {
				case 'head':
					$moduleHead = $moduleDoc->documentElement->childNodes->item($i);
					break;
				case 'panels':
					$modulePanels= $moduleDoc->documentElement->childNodes->item($i);
					break;
			} // switch tagName
		} // == DOMElement
	} // for i
	
	// Now breakdown the head of the document
	for ($i = 0; $i < $moduleHead->childNodes->length; $i++) {
		if (get_class($moduleHead->childNodes->item($i)) == 'DOMElement') {
			switch ($moduleHead->childNodes->item($i)->tagName) {
				case 'name':
					$module['Name'] = $moduleHead->childNodes->item($i)->nodeValue;
					break;
				case 'describe':
					$module['Description'] = $moduleHead->childNodes->item($i)->nodeValue;
					break;
				case 'tooltip':
					$module['Tooltip'] = $moduleHead->childNodes->item($i)->nodeValue;
					break;
				case 'server':
					$module['Server']['Username'] = $moduleHead->childNodes->item($i)->getAttribute('username');
					$module['Server']['Password'] = $moduleHead->childNodes->item($i)->getAttribute('password');
					$module['Server']['Hostname'] = $moduleHead->childNodes->item($i)->getAttribute('hostname');
					break;
			} // switch tagName
		} // == DOMElement
	} // for i

	// We need to get information about each panel and enumerate the fields
	$cp = 0;
	for ($p = 0; $p < $modulePanels->childNodes->length; $p++) {
		$cPanel = $modulePanels->childNodes->item($p);
		if (get_class($cPanel) == 'DOMElement') {
			if ($cPanel->tagName == 'panel') {
				$module['Panels'][$cp]['Name'] = $cPanel->getAttribute('name');
				$module['Panels'][$cp]['Database'] = $cPanel->getAttribute('db');
				$module['Panels'][$cp]['Table'] = $cPanel->getAttribute('table');
				for ($i = 0; $i < $cPanel->childNodes->length; $i++) {
					if (get_class($cPanel->childNodes->item($i)) == 'DOMElement') {
						switch ($cPanel->childNodes->item($i)->tagName) {
							case 'tooltip':
								$module['Panels'][$cp]['Tooltip'] = $cPanel->childNodes->item($i)->nodeValue;
								break;
							case 'describe':
								$module['Panels'][$cp]['Description'] = $cPanel->childNodes->item($i)->nodeValue;
								break;
							case 'tabledef':
								$curTable = $cPanel->childNodes->item($i);
								$e = 0;
								// Enumerate the fields
								for ($f = 0; $f < $curTable->childNodes->length; $f++) {
									if (get_class($curTable->childNodes->item($f)) == 'DOMElement') {
										$module['Panels'][$cp]['TableDef'][$e] = $curTable->childNodes->item($f);
										$e++;
									} // DOMElement
								} // for f
								break;
						} // switch tagName
					}  // == DOMElement
				} // for i
				$cp++;
			} // tagName = panel
		} // == DOMElement
	} // for p

	restore_error_handler();
	error_reporting($ErrMode);
	DacomasySetExtendedErrorMsg('');
	DacomasySetLastError(__DACOMASY_ERROR_SUCCESSFUL);
	return $module;
}

?>
