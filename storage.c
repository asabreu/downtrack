#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

/* application includes */
#include "storage.h"

#define KRESET			"\033[m"
#define KBROWN			"\x1B[33m"
#define KCYAN			"\x1B[36m"
#define KRED			"\x1B[31m"

int callback(void *, int, char **, char **);

sqlite3 *pDb;

void initialize_db() {
   int rc;
   char *zErrMsg = 0;
   char *sql;
   
   rc = sqlite3_open_v2(db_name, &pDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

   if (rc) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(pDb));
      sqlite3_close(pDb);
      exit(1);
   }

   sql = "CREATE TABLE IF NOT EXISTS log ( \
	id INTEGER PRIMARY KEY AUTOINCREMENT, \
	env TEXT NOT NULL, \
	start INTEGER NOT NULL, \
	end INTEGER, \
	reason TEXT)";

   rc = sqlite3_exec(pDb, sql, NULL, 0, &zErrMsg);

   if (rc != SQLITE_OK) {
      fprintf(stderr, "sqlite: SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
      sqlite3_close(pDb);
      exit(1);
   }
}

void close_db() {
   sqlite3_close(pDb);
}

bool insert_down(char *env, char *reason) {
	sqlite3_stmt *pStmt;
	const char *sql = "INSERT INTO log (env, start, reason) VALUES (:env, datetime('now','localtime'), :reason)";

	sqlite3_prepare_v2(pDb, sql, strlen(sql), &pStmt, NULL);

 	const int index1 = sqlite3_bind_parameter_index(pStmt, ":env");
        sqlite3_bind_text(pStmt, index1, (const char*)env, -1, SQLITE_STATIC);

	const int index2 = sqlite3_bind_parameter_index(pStmt, ":reason");
	sqlite3_bind_text(pStmt, index2, (const char*)reason, -1, SQLITE_STATIC); 

	bool success = true;

   	if (sqlite3_step(pStmt) != SQLITE_DONE) {
      		fprintf(stderr, "sqlite: SQL error!\n");
		success = false;
   	}

   	sqlite3_reset(pStmt);

	return success;
}

bool update_up(char *env) {
 	sqlite3_stmt *pStmt;
        const char *sql = "UPDATE log SET end = datetime('now','localtime') WHERE env = (:env)";

        sqlite3_prepare_v2(pDb, sql, strlen(sql), &pStmt, NULL);

        const int index = sqlite3_bind_parameter_index(pStmt, ":env");
        sqlite3_bind_text(pStmt, index, (const char*)env, -1, SQLITE_STATIC);

	bool success = true;

        if (sqlite3_step(pStmt) != SQLITE_DONE) {
                fprintf(stderr, "sqlite: SQL error!\n");
		success = false;
        }
	
        sqlite3_reset(pStmt);

	return success;
}

void get_status() {
	int rc;
   	char *zErrMsg = 0;
   	char *sql;	

	sql = "SELECT env, start, reason, Cast ((julianday('now','localtime') - julianday(start)) * 24 * 60 As Integer) FROM log WHERE end IS NULL";
        
    	rc = sqlite3_exec(pDb, sql, callback, 0, &zErrMsg);
    
    	if (rc != SQLITE_OK) {
        	fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "sqlite: SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
      	}
}

/* private methods */

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	NotUsed = 0;

	char *env =  argv[0] ? argv[0] : NULL; 
	char *start =  argv[1] ? argv[1] : NULL;
	char *reason =  argv[2] ? argv[2] : NULL;
	char *elapsed = argv[3] ? argv[3] : "";
	
	printf(KCYAN "%s" KRESET, env);
	printf("\t");
	printf(KBROWN "%s" KRESET, start);
	printf(" (%sm)", elapsed);

	if (reason != NULL) {
		printf("\t");
        	printf(KRED "%s" KRESET, reason);
	}

	printf("\n");

	return 0;
}
