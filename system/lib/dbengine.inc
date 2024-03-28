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
 * Contains constants, functions, and global variables database manipulation.
 * 
 * @package Dacomasy
 * @author 6XGate, Inc. <support@sixxgate.com>
 * @copyright 6XGate, Inc. 2005
 * @license http://www.opensource.org/licenses/gpl-license.php GNU GPL
 * @subpackage Database
 * @version $SixXGate: webapps/dacomasy/www/system/lib/dbengine.inc,v 1.1.1.1 2005/07/21 22:57:32 matthew Exp $
 */

/**#@+ Database Engine Type. */

/** MySQL */					define ('DACOMASY_DBENGINE_MYSQL',							0x0, TRUE);
/** Microsoft SQL Server */		define ('DACOMASY_DBENGINE_MSSQL',							0x1, TRUE);
/** mSQL */						define ('DACOMASY_DBENGINE_MSQL',							0x2, TRUE);
/** PostgreSQL */				define ('DACOMASY_DBENGINE_PGSQL',							0x3, TRUE);
/** SQLite */					define ('DACOMASY_DBENGINE_SQLITE',							0x4, TRUE);

/**#@-*/

/**
 * A database connection that Dacomasy uses to interface with a database system.
 *
 * @package Dacomasy
 */
final class DacoDBConnection {
	private $DBConn;
	private $Hostname;
	private $Username;
	private $Password;
	private $Port;
	private $Persist;
	
	/**
	 * Initializes a database connection class with the hostname, username, password, port, and persist option.
	 *
	 * @param string The hostname of the database server.  The default is localhost.
	 * @param string The username to use when connecting to the server.  Use null for the default.
	 * @param string The password to use when connecting to the server.  Use null for the default.
	 * @param number The port to connect to.
	 * @param boolean Indicates if to use a persistant connection or not.
	 */
	function __construct($szHostname = 'localhost', $szUsername = NULL, $szPassword = NULL, $nPort = NULL, $bPersist = TRUE) {
		$this->Hostname = $szHostname;
		$this->Username = $szUsername;
		$this->Password = $szPassword;
		$this->Port = $nPort;
		$this->Persist = $bPersist;
		$this->DBConn = FALSE;
	}
	
	/**
	 * Connects to the database server.
	 *
	 * @return boolean Is true on success or false on error.
	 */
	public function Connect() {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			if (!is_null($this->Port)) $this->Hostname .= ':' . $this->Port;
			
			if ($this->Persist) $this->DBConn = @mysql_pconnect($this->Hostname, $this->Username, $this->Password);
			else $this->DBConn = @mysql_connect($this->Hostname, $this->Username, $this->Password);
			
			if ($this->DBConn === FALSE) return FALSE;
			else return TRUE;
			break;
		case DACOMASY_DBENGINE_MSSQL:
			if ($this->Persist) $this->DBConn = @mssql_pconnect($szHostname, $szUsername, $szPassword);
			else $this->DBConn = @mssql_connect($szHostname, $szUsername, $szPassword);
			
			if ($this->DBConn === FALSE) return FALSE;
			else return TRUE;
			break;
		case DACOMASY_DBENGINE_MSQL:
			if (!is_null($this->Port)) $this->Hostname .= ',' . $this->Port;
			
			if ($this->Persist) $this->DBConn = @msql_pconnect($szHostname, $szUsername, $szPassword);
			else $this->DBConn = @msql_connect($szHostname, $szUsername, $szPassword);
			
			if ($this->DBConn === FALSE) return FALSE;
			else return TRUE;
			break;
		case DACOMASY_DBENGINE_PGSQL:
			// Just check to make sure the extension is installed, we don't have all we need to connect.
			if (extension_loaded('pgsql')) return TRUE;
			else return FALSE;
			break;
		case DACOMASY_DBENGINE_SQLITE:
			// Just check to make sure the extension is installed, we don't have all we need to connect.
			if (extension_loaded('SQLite')) return TRUE;
			else return FALSE;
			break;
		}
		// If we made here then an invalid database engine was specified.
		return FALSE;
	}
	
	/**
	 * Disconnects from the database server.
	 *
	 * @return boolean Is true on success or false on error.
	 */
	public function Disconnect() {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			return mysql_close($this->DBConn);
			break;
		case DACOMASY_DBENGINE_MSSQL:
			return mssql_close($this->DBConn);
			break;
		case DACOMASY_DBENGINE_MSQL:
			return msql_close($this->DBConn);
			break;
		case DACOMASY_DBENGINE_PGSQL:
			return pg_close($this->DBConn);
			break;
		case DACOMASY_DBENGINE_SQLITE:
			sqlite_close($this->DBConn);
			return TRUE;
			break;
	}
		// If we made here then an invalid database engine was specified.
		return FALSE;
	}
	
	/**
	 * Selects a catalog on the database server.  A catalog is sometime called a database.
	 *
	 * @param string The name of the catalog(database) to use.
	 * @return boolean Is true on success or false on error.
	 */
	public function SelectCatalog($szCatalogName) {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			return mysql_select_db($szCatalogName, $this->DBConn);
			break;
		case DACOMASY_DBENGINE_MSSQL:
			return mssql_select_db($szCatalogName, $this->DBConn);
			break;
		case DACOMASY_DBENGINE_MSQL:
			return msql_select_db($szCatalogName, $this->DBConn);
			break;
		case DACOMASY_DBENGINE_PGSQL:
			// If an existing connection exists, close it.
			if ($this->DBConn !== FALSE) pg_close($this->DBConn);
			
			// Create the connection string
			@$Connect = 'host=' . addslashes($this->Hostname);
			if (!is_null($this->Port)) $Connect .= ' port=' . addslashes($this->Port);
			if (!is_null($this->Username)) $Connect .= ' username=' . addslashes($this->Username);
			if (!is_null($this->Password)) $Connect .= ' password=' . addslashes($this->Password);
			$Connect .= ' dbname=' . addslashes($szCatalogName);
			
			// Connect
			if ($this->Persist) $this->DBConn = @pg_pconnect($Connect);
			else $this->DBConn = @pg_connect($Connect);
			
			// Check for errors
			if ($this->DBConn === FALSE) return FALSE;
			else return TRUE;
			
			break;
		case DACOMASY_DBENGINE_SQLITE:
			// If an existing connection exists, close it.
			if ($this->DBConn !== FALSE) sqlite_close($this->DBConn);
			
			// Open the datase
			if ($this->Persist) $this->DBConn = @sqlite_popen($szCatalogName);
			else $this->DBConn = @sqlite_open($szCatalogName);
			
			// Check for errors
			if ($this->DBConn === FALSE) return FALSE;
			else return TRUE;
			break;
		}
		// If we made here then an invalid database engine was specified.
		return FALSE;
	}
	
	/**
	 * Executes a SQL query and returns a DacoDBQuery class that can get the results of the query.
	 *
	 * @param string The SQL query to execute.
	 * @return object DacoDBQuery A DacoDBQuery object.
	 * @see DacoDBQuery
	 */
	public function Query($szQuery) {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			$newRes = mysql_query($szQuery, $this->DBConn);
			return new DacoDBQuery($this->DBConn, $newRes);
			break;
		case DACOMASY_DBENGINE_MSSQL:
			$newRes = mssql_query($szQuery, $this->DBConn);
			return new DacoDBQuery($this->DBConn, $newRes);
			break;
		case DACOMASY_DBENGINE_MSQL:
			$newRes = msql_query($szQuery, $this->DBConn);
			return new DacoDBQuery($this->DBConn, $newRes);
			break;
		case DACOMASY_DBENGINE_PGSQL:
			$newRes = pg_query($this->DBConn, $szQuery);
			return new DacoDBQuery($this->DBConn, $newRes);
			break;
		case DACOMASY_DBENGINE_SQLITE:
			$newRes = sqlite_query($this->DBConn, $szQuery);
			return new DacoDBQuery($this->DBConn, $newRes);
			break;
		}
		return FALSE;
	}
	
	/**
	 * Prepares a string to be used as a SQL field or table identifier, or SQL value.
	 *
	 * @param string The unescaped string to prepare.
	 * @return string The prepared string, ready to use in a SQL qeury.
	 */
	static public function EscapeString($szString) {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			return mysql_escape_string($szString);
			break;
		case DACOMASY_DBENGINE_MSSQL:
			return addslashes($szString);
			break;
		case DACOMASY_DBENGINE_MSQL:
			return addslashes($szString);
			break;
		case DACOMASY_DBENGINE_PGSQL:
			return pg_escape_string($szString);
			break;
		case DACOMASY_DBENGINE_SQLITE:
			return sqlite_escape_string($szString);
			break;
		}
		return FALSE;
	}
	
	/**
	 * Prepares a binary data stream as a SQL value.
	 *
	 * @param string The unescaped binary stream to prepare.
	 * @return string The prepared binary stream, ready to use in a SQL qeury.
	 */
	static public function EscapeBinary($szBinary) {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			return mysql_escape_string($szBinary);
			break;
		case DACOMASY_DBENGINE_MSSQL:
			return addslashes($szBinary);
			break;
		case DACOMASY_DBENGINE_MSQL:
			return addslashes($szBinary);
			break;
		case DACOMASY_DBENGINE_PGSQL:
			return pg_escape_bytea($szBinary);
			break;
		case DACOMASY_DBENGINE_SQLITE:
			return sqlite_escape_string($szBinary);
			break;
		}
	}
	
	/**
	 * Prepares other datatypes to be used as a SQL value.
	 *
	 * @param mixed The unprepared data.
	 * @return string The prepared data in a string, ready to use in a SQL qeury.
	 */
	static public function Escape($mValue) {
		if (is_float($mValue) || is_int($mValue)) {
			return strval($mValue);
		}
		if (is_bool($mValue)) {
			switch ($GLOBALS['Dacomasy_DBEngine']) {
			case DACOMASY_DBENGINE_MYSQL:
				return ($mValue === TRUE) ? '1' : '0';
				break;
			case DACOMASY_DBENGINE_MSSQL:
				return ($mValue === TRUE) ? '1' : '0';
				break;
			case DACOMASY_DBENGINE_MSQL:
				return ($mValue === TRUE) ? '1' : '0';
				break;
			case DACOMASY_DBENGINE_PGSQL:
				return ($mValue === TRUE) ? 'TRUE' : 'FALSE';
				break;
			case DACOMASY_DBENGINE_SQLITE:
				return ($mValue === TRUE) ? '1' : '0';
				break;
			}
		}
		if (is_string($mValue)) return DacoDBConnection::EscapeString($mValue);
		return 'NULL';
	}
	
	/**
	 * Gets the last error message that occurred from the last method call.
	 *
	 * @return string A message describing the error.
	 */
	public function GetLastError() {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			return mysql_error($this->DBConn);
			break;
		case DACOMASY_DBENGINE_MSSQL:
			return mssql_get_last_message();
			break;
		case DACOMASY_DBENGINE_MSQL:
			return msql_error();
			break;
		case DACOMASY_DBENGINE_PGSQL:
			return pg_last_error($this->DBConn);
			break;
		case DACOMASY_DBENGINE_SQLITE:
			return sqlite_error_string(sqlite_last_error($this->DBConn));
			break;
		}
		return FALSE;
	}
}

/**
 * A database query result returned from a DacoDBConnection::Query() method call.
 *
 * @see DacoDBConnection::Query()
 * @package Dacomasy
 */

final class DacoDBQuery {
	private $resResult;
	private $resDB;
	
	/**
	 * The DacoDBQuery constructor.
	 *
	 * @param resource A database connection resource.
	 * @param resource A query result resource.
	 */
	function __construct($resDB, $resResult) {
		$this->resResult = $resResult;
		$this->resDB = $resDB;
	}
	
	/**
	 * Frees the query result.
	 *
	 * This is called when you unset a query result variable.
	 */
	function __destruct() {
		if (is_resource($this->resResult) === TRUE) {
			switch ($GLOBALS['Dacomasy_DBEngine']) {
			case DACOMASY_DBENGINE_MYSQL:
				mysql_free_result($this->resResult);
				break;
			case DACOMASY_DBENGINE_MSSQL:
				mssql_free_result($this->resResult);
				break;
			case DACOMASY_DBENGINE_MSQL:
				msql_free_result($this->resResult);
				break;
			case DACOMASY_DBENGINE_PGSQL:
				pg_free_result($this->resResult);
				break;
			case DACOMASY_DBENGINE_SQLITE:
				// Just a placeholder
				break;
			}
		}
	}
	
	/**
	 * Indicates if an error occurred when the query was executed.
	 *
	 * @return boolean Is true if an error occurred, or false if one did not.
	 */
	public function Error() {
		if ($this->resResult === FALSE) return TRUE;
		return FALSE;
	}
	
	/**
	 * Gets the number of rows returned by a SELECT query.
	 *
	 * @return number The number of rows in the record set.
	 * @todo Optimize for use a cached value
	 */
	public function RowCount() {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			return mysql_num_rows($this->resResult);
			break;
		case DACOMASY_DBENGINE_MSSQL:
			return mssql_num_rows($this->resResult);
			break;
		case DACOMASY_DBENGINE_MSQL:
			return msql_num_rows($this->resResult);
			break;
		case DACOMASY_DBENGINE_PGSQL:
			return pg_num_rows($this->resResult);
			break;
		case DACOMASY_DBENGINE_SQLITE:
			return sqlite_num_rows($this->resResult);
			break;
		}
		return TRUE;
	}
	
	/**
	 * Fetches the next record in the query's record set.
	 *
	 * @return array An associative array that contains the field values of the record.
	 */
	public function FetchNextRecord() {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			return mysql_fetch_assoc($this->resResult);
			break;
		case DACOMASY_DBENGINE_MSSQL:
			return mssql_fetch_assoc($this->resResult);
			break;
		case DACOMASY_DBENGINE_MSQL:
			return msql_fetch_array($this->resResult);
			break;
		case DACOMASY_DBENGINE_PGSQL:
			return pg_fetch_assoc($this->resResult);
			break;
		case DACOMASY_DBENGINE_SQLITE:
			return sqlite_fetch_array($this->resResult);
			break;
		}
		return FALSE;
	}
	
	/**
	 * Returns the number of rows affected by a UPDATE, INSERT, or other non-SELECT query.
	 *
	 * @return number The number of affected rows.
	 */
	public function AffectedRows() {
		switch ($GLOBALS['Dacomasy_DBEngine']) {
		case DACOMASY_DBENGINE_MYSQL:
			return mysql_affected_rows($this->DBConn);
			break;
		case DACOMASY_DBENGINE_MSSQL:
			return mssql_rows_affected($this->DBConn);
			break;
		case DACOMASY_DBENGINE_MSQL:
			return msql_affected_rows($this->resResult);
			break;
		case DACOMASY_DBENGINE_PGSQL:
			return pg_affected_rows($this->resResult);
			break;
		case DACOMASY_DBENGINE_SQLITE:
			return sqlite_changes($this->DBConn);
			break;
		}
		return FALSE;
	}
}

?>