#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h> 



static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   std::cout<<argc<<std::endl;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}



int main() {
	sqlite3* dataBase;
	char* dbRequest;
	int rc;
	char *zErrMsg;
	
	rc = sqlite3_open("test.db", &dataBase);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(dataBase));
        exit(0);
	}
    else{
        fprintf(stdout, "Opened database successfully\n");
    }
    
    dbRequest = "CREATE TABLE IF NOT EXISTS restaurants(id INT PRIMARY KEY, name TEXT, places INT)";
	rc = sqlite3_exec(dataBase, dbRequest, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		fprintf(stdout, "Table created successfully\n");
	}
	
	//dbRequest = "INSERT INTO restaurants VALUES(1, 'blue', 60)";
	//dbRequest = "INSERT INTO restaurants (id, name, places) VALUES (2, tribeca, 100)"
	rc = sqlite3_exec(dataBase, "UPDATE restaurants SET places = NULL WHERE(name = 'blue')", callback, 0, &zErrMsg);
	dbRequest = "UPDATE restaurants SET places = 90 WHERE(name = 'blue')";
	dbRequest = "SELECT COUNT(places) FROM restaurants";
	
	rc = sqlite3_exec(dataBase, dbRequest, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else{
		fprintf(stdout, "Value added successfully\n");
	}
	sqlite3_close(dataBase);
	return 0;
}
