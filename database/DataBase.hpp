#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <tinyxml.h> 
#include <iostream>
#include <string>
#include <vector>
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
		std::vector<Commentaire*> _currentComments ;
		std::string _tempConge = "OOOOOOOOOOOOOO";
		std::string _currentAdr;
	
	public:
		DataBase(char*);
		~DataBase();
		int addUser(User&);
		void addEtablissement(Etablissement&, std::string);
		void addRestaurant(Restaurant&);
		void addBar(Bar&);
		void addHotel(Hotel&);
		void addCommentaire(Commentaire&);
		void delUser(User&);
		void delEtablissement(Etablissement&);
		void delCommentaire(Commentaire&);
		User getUserByCond(std::string);
		std::vector<Commentaire*> getCommByCond(std::string);
		std::vector<Etablissement*> getEtabByCond(std::string);
		void updateData(std::string, std::string, std::string, std::string);
		void initUsersTable();
		void initCommentsTable();
		void initEtablishmentTable();
		void initLabelsPrototypeTable();
		void initLabelsContainerTable();
		void checkError(int, char*);
		template<typename xml, class etab>
		void restCase(xml ,etab);
		int xmlParser(std::string);
		int recursiveParser(TiXmlElement*);
		void addAndDeleteCommentsObj();
		void restInfos(TiXmlElement*);
		void barInfos(TiXmlElement*);
		void requeteR1();
		void requeteR2();
		// void debut_element(void *user_data, const xmlChar *, const xmlChar **);
		//int getHighestId(char*);
		static int getEtabCallback(void*, int, char**, char**);
		static int getUserCallback(void*, int, char**, char**);
		static int getRestoCallback(void*, int, char**, char**);
		static int getBarCallback(void*, int, char**, char**);
		static int getHotelCallback(void*, int, char**, char**);
		static int getNoteCallback(void*, int, char**, char**);
		static int getCommCallback(void*, int, char**, char**);
		static int printCallback(void*, int, char**, char**);


		
};
#endif /* DATABASE_HPP */