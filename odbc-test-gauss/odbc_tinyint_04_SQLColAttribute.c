 /*
测试odbc支持tinyint类型
test: SQLColAttribute()函数，获取数据类型为tinyint的列的各项属性
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

int main( )
{
	SQLHENV         hEnv    = SQL_NULL_HENV;
	SQLHDBC         hDbc    = SQL_NULL_HDBC;
	SQLHSTMT        hStmt   = SQL_NULL_HSTMT;
	SQLRETURN       rc      = SQL_SUCCESS;
	SQLINTEGER      RETCODE = 0;
	
	SQLCHAR typename[200],typename2[200],catalogName[200],tableName[200],description[200];
	SQLCHAR disName[200],localTypeName[200],colName[200],prefix[200]={0},suffix[200]={0};
	
	SQLINTEGER autoIncrement = 0;
	SQLINTEGER caseSenstive = 0;
	SQLINTEGER caseSenstive2 = 0;
	SQLINTEGER descType = 0;
	SQLINTEGER length = 0;
	SQLINTEGER OCTET_LENGTH  = 0;
	SQLINTEGER descLength = 0;
	SQLINTEGER precision = 0;
	SQLINTEGER precision1 = 0;
	SQLINTEGER scale = 0;
	SQLINTEGER serchable = 0;
	SQLINTEGER serchable2 = 0;
	SQLINTEGER typelen = 0;
	SQLINTEGER unsigneds = 0;
	SQLINTEGER displaySize = 0;
	SQLINTEGER radix = 0;
	
	SQLINTEGER cbTypeName = 0;
	SQLINTEGER cbCatalog = 0;
	SQLINTEGER cbTable = 0;
	SQLINTEGER cbPrefix = 0;
	SQLINTEGER cbSuffix = 0;
	
	SQLINTEGER cbID = 0;
	SQLINTEGER cbDes = 0;
	SQLINTEGER cbLen = 0;
	
	(void) printf ("**** Entering CLIP06.\n\n");
	/*****************************************************************/
	/* Allocate environment handle                                   */
	/*****************************************************************/
	RETCODE = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	if (!SQL_SUCCEEDED(RETCODE))
		goto dberror;
	SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
	
	/*****************************************************************/
	/* Allocate connection handle to DSN                             */
	/*****************************************************************/
	RETCODE = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
	if( !SQL_SUCCEEDED(RETCODE) )      // Could not get a Connect Handle
		goto dberror;

	/*****************************************************************/
	/* CONNECT TO data source (STLEC1)                               */
	/*****************************************************************/
	RETCODE = SQLConnect(hDbc,        // Connect handle
		                  (SQLCHAR *)"gaussdb", // DSN
		                  SQL_NTS,     // DSN is nul-terminated
		                  NULL,        // Null UID
		                  0   ,
		                  NULL,        // Null Auth string
		                  0);
	
	if( !SQL_SUCCEEDED(RETCODE))      // Connect failed
		goto dberror;
 
	/*****************************************************************/
	/* Allocate statement handle                                     */
	/*****************************************************************/
	rc = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	if (!SQL_SUCCEEDED(rc))
		goto exit;
	
	
	/*****************************************************************/
	/*                                                               */
	/* Retrieve native SQL types from DSN ------------>              */
	/*                                                               */
	/*  The result set consists of 15 columns. We only bind          */
	/*  serveral we modified for tinyint. Note: Need   			  */
	/*  not bind all columns of result set -- only those required.   */
	/*                                                               */
	/*****************************************************************/
	
	rc = SQLExecDirect(hStmt,"drop table IF EXISTS  odbc_tinyint_04_SQLColAttribute",SQL_NTS);
	if (!SQL_SUCCEEDED(rc))
		goto exit;
	
	rc = SQLExecDirect(hStmt,"create table odbc_tinyint_04_SQLColAttribute(id tinyint,count int)",SQL_NTS);
	if (!SQL_SUCCEEDED(rc))
		goto exit;
	
	rc = SQLExecDirect(hStmt,"insert into odbc_tinyint_04_SQLColAttribute values(1,222)",SQL_NTS);
	if (!SQL_SUCCEEDED(rc))
		goto exit;
	
	rc = SQLExecDirect(hStmt,"select id,count from odbc_tinyint_04_SQLColAttribute",SQL_NTS);
	if (!SQL_SUCCEEDED(rc))
		goto exit;
	
	rc = SQLFetch(hStmt);  
	while(rc != SQL_NO_DATA)
	{   
		/*****************************************************************/
		/*	whether the column data type automatically increments. 		*/
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_COLUMN_AUTO_INCREMENT,NULL,0,NULL,(SQLLEN*)&autoIncrement);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_COLUMN_AUTO_INCREMENT----tinyint: %d\n",autoIncrement);
		
		RETCODE = SQLColAttribute(hStmt,2,SQL_COLUMN_AUTO_INCREMENT,NULL,0,NULL,(SQLLEN*)&autoIncrement);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_COLUMN_AUTO_INCREMENT----int: %d\n",autoIncrement);
		
		
		/*****************************************************************/
		/*	whether the column data type is case sensitive. 		    */
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_COLUMN_CASE_SENSITIVE,NULL,0,NULL,(SQLLEN*)&caseSenstive);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_COLUMN_CASE_SENSITIVE----tinyint: %d\n",caseSenstive);
		
		RETCODE = SQLColAttribute(hStmt,2,SQL_COLUMN_CASE_SENSITIVE,NULL,0,NULL,(SQLLEN*)&caseSenstive2);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_COLUMN_CASE_SENSITIVE----int: %d\n",caseSenstive2);
		
		/*****************************************************************/
		/*	Indicates if the column data type is searchable				*/
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_COLUMN_SEARCHABLE,NULL,0,NULL,(SQLLEN*)&serchable);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_COLUMN_SEARCHABLE----tinyint : %d \n",serchable);
		RETCODE = SQLColAttribute(hStmt,2,SQL_COLUMN_SEARCHABLE,NULL,0,NULL,(SQLLEN*)&serchable2);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_COLUMN_SEARCHABLE----int     : %d \n",serchable2);
		
		/*****************************************************************/
		/*	Indicates if the column data type is an unsigned type. 		*/
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_UNSIGNED ,NULL,0,NULL,(SQLLEN*)&unsigneds);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_UNSIGNED----tinyint(true): %d\n",unsigneds);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_UNSIGNED ,NULL,0,NULL,(SQLLEN*)&unsigneds);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_UNSIGNED----int(false): %d\n",unsigneds);
		
		
		/*****************************************************************/
		/*	The type of the column (specified in an SQL statement)		*/
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_TYPE_NAME ,typename,sizeof(typename),(SQLSMALLINT*)&cbTypeName,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_TYPE_NAME----int1: %s\n",typename);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_TYPE_NAME ,typename2,sizeof(typename2),(SQLSMALLINT*)&cbLen,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_TYPE_NAME----int4: %s\n",typename2);
		
		/*****************************************************************/
		/*	A VARCHAR(128) record field that contains any localized 	*/
		/* (native language) name for the data type that might be 		*/
		/*	different from  the regular name of the data type.			*/
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_LOCAL_TYPE_NAME,localTypeName,sizeof(localTypeName),(SQLSMALLINT*)&typelen,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_LOCAL_TYPE_NAME----int1: %s\n",localTypeName);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_LOCAL_TYPE_NAME,localTypeName,sizeof(localTypeName),(SQLSMALLINT*)&typelen,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_LOCAL_TYPE_NAME----int4: %s\n",localTypeName);
		
		/*****************************************************************/
		/*	The SQL data type of the column. 							*/
		/*	For the datetime data types, this field returns the verbose  */
		/*  data type, such as SQL_DATETIME.							*/
		/*****************************************************************/  
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_TYPE,NULL,0,NULL,(SQLLEN*)&descType);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_TYPE----SQL_TINYINT: %d SQL_TINYINT=%d\n",descType,SQL_TINYINT);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_TYPE,NULL,0,NULL,(SQLLEN*)&descType);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_TYPE----SQL_INTEGER: %d SQL_INTEGER=%d\n",descType,SQL_INTEGER);

		
		/*****************************************************************/
		/*	A numeric value that is either the maximum or actual length, */
		/*	in bytes, of a character string or binary data type.		*/
		/*****************************************************************/	
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_LENGTH ,NULL,0,NULL,(SQLLEN*)&descLength);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_LENGTH----tinyint: %d\n",descLength);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_LENGTH ,NULL,0,NULL,(SQLLEN*)&descLength);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_LENGTH----int: %d\n",descLength);
		
		/*****************************************************************/
		/*	The name of the column.										*/
		/*****************************************************************/	
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_NAME,colName,sizeof(colName),(SQLSMALLINT*)&typelen,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_NAME----ID: %s\n",colName);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_NAME,colName,sizeof(colName),(SQLSMALLINT*)&typelen,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_NAME----COUNT: %s\n",colName);
		
		
		/******************************************************************/
		/*	The number of bytes of data that is associated with the column*/
		/*	This is the length in bytes of data that is transferred on the*/ 
		/*	fetch or SQLGetData() for this column if SQL_C_DEFAULT is 	 */	
		/*	specified as the C data type. 								 */
		/******************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_OCTET_LENGTH,NULL,0,NULL,(SQLLEN*)&OCTET_LENGTH);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_OCTET_LENGTH----TINYINT: %d\n",OCTET_LENGTH);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_OCTET_LENGTH,NULL,0,NULL,(SQLLEN*)&OCTET_LENGTH);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_OCTET_LENGTH----INT: %d\n",OCTET_LENGTH);
		
		/*****************************************************************/
		/*	The maximum number of bytes that are needed to display the   */
		/* data in character form. 										*/
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_COLUMN_DISPLAY_SIZE,NULL,0,NULL,(SQLLEN*)&displaySize);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_COLUMN_DISPLAY_SIZE----TINYINT: %d\n",displaySize);
		RETCODE = SQLColAttribute(hStmt,1,SQL_COLUMN_DISPLAY_SIZE,NULL,0,NULL,(SQLLEN*)&displaySize);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_COLUMN_DISPLAY_SIZE----INT: %d\n",displaySize);
		
		/*****************************************************************/
		/*	PRECISION AND SCALE	RADIX								   */
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_PRECISION,NULL,0,NULL,(SQLLEN*)&precision);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_PRECISION----tinyint: %d\n",precision);
		
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_PRECISION,NULL,0,NULL,(SQLLEN*)&precision1);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_PRECISION----int: %d\n",precision1);
		
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_SCALE,NULL,0,NULL,(SQLLEN*)&scale);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_SCALE----TINYINT %d\n",scale);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_SCALE,NULL,0,NULL,(SQLLEN*)&scale);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_SCALE----INT: %d\n",scale);
		
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_NUM_PREC_RADIX ,NULL,0,NULL,(SQLLEN*)&radix);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_SCALE----TINYINT %d\n",radix);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_NUM_PREC_RADIX ,NULL,0,NULL,(SQLLEN*)&radix);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_SCALE----INT: %d\n",radix);
		
		/*****************************************************************/
		/*	LITERAL_PREFIX AND LITERAL_SUFFIX						    */
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_LITERAL_PREFIX ,prefix,sizeof(prefix),(SQLSMALLINT*)&cbPrefix,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;	
		printf("SQL_DESC_LITERAL_PREFIX----TINYINT: %s\n",prefix);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_LITERAL_PREFIX ,prefix,sizeof(prefix),(SQLSMALLINT*)&cbPrefix,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
		goto dberror;
		printf("SQL_DESC_LITERAL_PREFIX----INT: %s\n",prefix);
		
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_LITERAL_SUFFIX ,suffix,sizeof(suffix),(SQLSMALLINT*)&cbSuffix,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;
		printf("SQL_DESC_LITERAL_SUFFIX----TINYINT: %s\n",suffix);
		RETCODE = SQLColAttribute(hStmt,2,SQL_DESC_LITERAL_SUFFIX ,suffix,sizeof(suffix),(SQLSMALLINT*)&cbSuffix,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;
		printf("SQL_DESC_LITERAL_SUFFIX----INT: %s\n",suffix);
		
		/*****************************************************************/
		/*	CATALOG NAME AND TABLE NAME									*/
		/*****************************************************************/
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_CATALOG_NAME,catalogName,sizeof(catalogName),(SQLSMALLINT*)&cbCatalog,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;		
		printf("SQL_DESC_CATALOG_NAME----PG_CATALOG: %s\n",catalogName);
		
		RETCODE = SQLColAttribute(hStmt,1,SQL_DESC_TABLE_NAME,tableName,sizeof(tableName),(SQLSMALLINT*)&cbTable,NULL);
		if (!SQL_SUCCEEDED(RETCODE))
			goto dberror;
		printf("SQL_DESC_TABLE_NAME----TB: %s\n",tableName);

		rc = SQLFetch(hStmt);  
	};
	
	if (!SQL_SUCCEEDED(rc) && rc != SQL_NO_DATA)
		goto exit;
	
	/*****************************************************************/
	/* Free statement handle                                         */
	/*****************************************************************/
	rc = SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	if (!SQL_SUCCEEDED(RETCODE))       // An advertised API failed
		goto dberror;
	
	/*****************************************************************/
	/* DISCONNECT from data source                                   */
	/*****************************************************************/
	RETCODE = SQLDisconnect(hDbc);
	if (!SQL_SUCCEEDED(RETCODE))
		goto dberror;
	
	/*****************************************************************/
	/* Deallocate connection handle                                  */
	/*****************************************************************/
	RETCODE = SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	if (!SQL_SUCCEEDED(RETCODE))
		goto dberror;
	
	/*****************************************************************/
	/* Free environment handle                                       */
	/*****************************************************************/
	RETCODE = SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
	if (!SQL_SUCCEEDED(RETCODE))
		goto exit;
	return 0;
dberror:
	RETCODE=12;
exit:
	(void) printf ("**** Exiting  CLIP06.\n\n");
	return(RETCODE);
}
