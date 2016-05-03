#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include "User.hpp"


class DataBase {
	private:
		sqlite3* _dataBase;
		int _nextUserId;
		int _nextAdminId;
	
	public:
		DataBase(char*);
		~DataBase();
		void addUser(User);
		void initUsersTable();
		void initEtablishmentTable();
		void checkError(int, char*);
		static int callbackFunction(void*, int, char**, char**);
		static int getHighestId(void*, int, char**, char**);
};
