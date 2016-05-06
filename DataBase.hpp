#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h> 
#include <iostream>
#include <string>
#include "User.hpp"	
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include "Etablissement.hpp"
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
		void debut_element(void *user_data, const xmlChar *, const xmlChar **);
		int getHighestId(char*);
		int xmlParser();
		static int callbackFunction(void*, int, char**, char**);
		static int getUserCallback(void*, int, char**, char**);
		static int getEtablCallback(void*, int, char**, char**);
		
};
#endif /* DATABASE_HPP */