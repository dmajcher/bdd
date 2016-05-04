#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include <string>
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
		void delUser(User);
		User getUserByName(std::string);
		void initUsersTable();
		void initEtablishmentTable();
		void checkError(int, char*);
		int getHighestId(char*);
		static int callbackFunction(void*, int, char**, char**);
		static int selectCallbackFunction(void*, int, char**, char**);
		
};
