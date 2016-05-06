#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include <string>
#include "User.hpp"
<<<<<<< HEAD
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
//#include "Etablissement.hpp"
#include "Bar.hpp"
=======
#include "Etablissement.hpp"
>>>>>>> 629ad5fc9d6267193afc4047dba1281f57d2693b
#include "Restaurant.hpp"
#include "Bar.hpp"
#include "Hotel.hpp"


class DataBase {
	private:
		sqlite3* _dataBase;
		int _nextUserId;
		int _nextAdminId;
		int _nextEtabId;
	
	public:
		DataBase(char*);
		~DataBase();
		void addUser(User);
		void addRestaurant(Restaurant);
		void addBar(Bar);
		void addHotel(Hotel);
		void delUser(User);
		User getUserByName(std::string);
		// Etablissement getEtablissement(int);
		void initUsersTable();
		void initEtablishmentTable();
		void checkError(int, char*);
		int getHighestId(char*);
		static int callbackFunction(void*, int, char**, char**);
		static int getUserCallback(void*, int, char**, char**);
		static int getEtablCallback(void*, int, char**, char**);
		
};
