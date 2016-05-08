#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <tinyxml.h> 
#include <iostream>
#include <string>
#include "User.hpp"	
#include "Etablissement.hpp"
#include "Restaurant.hpp"
#include "Bar.hpp"
#include "Hotel.hpp"
#include "Commentaire.hpp"


class DataBase {
	private:
		sqlite3* _dataBase;
		float _long;
		bool _isRestaurant = false;
		Bar* _currentBar = nullptr;
		Restaurant* _currentEtab = nullptr;
		std::string _tempConge = "OOOOOOOOOOOOOO";
		std::string _currentAdr;
	
	public:
		DataBase(char*);
		~DataBase();
		void addUser(User&);
		void addEtablissement(Etablissement&);
		void addRestaurant(Restaurant&);
		void addBar(Bar&);
		void addHotel(Hotel&);
		void addCommentaire(Commentaire&);
		void delUser(User&);
		void delEtablissement(Etablissement&);
		void delCommentaire(Commentaire&);
		User getUserByName(std::string);
		Restaurant getRestoByName(std::string);
		// Etablissement getEtablissement(int);
		void initUsersTable();
		void initCommentsTable();
		void initEtablishmentTable();
		void checkError(int, char*);
		template<typename xml, class etab>
		void restCase(xml ,etab);
		int xmlParser(std::string);
		int recursiveParser(TiXmlElement*);
		void restInfos(TiXmlElement*);
		void barInfos(TiXmlElement*);
		// void debut_element(void *user_data, const xmlChar *, const xmlChar **);
		//int getHighestId(char*);
		static int callbackFunction(void*, int, char**, char**);
		static int getUserCallback(void*, int, char**, char**);
		static int getEtablCallback(void*, int, char**, char**);


		
};
#endif /* DATABASE_HPP */