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


class DataBase {
	private:
		sqlite3* _dataBase;
		int _nextUserId;
		int _nextAdminId;
		int _nextEtabId;
		float _long;
		bool _isRestaurant = false;
		Bar* _currentBar = nullptr;
		Restaurant* _currentEtab = nullptr;
		std::string _tempConge = "OOOOOOOOOOOOOO";
		std::string _currentAdr;
	
	public:
		DataBase(char*);
		~DataBase();
		void addUser(User);
		void addEtablissement(Etablissement&);
		void addRestaurant(Restaurant&);
		void addBar(Bar&);
		void addHotel(Hotel&);
		void delUser(User);
		void delEtablissement(Etablissement&);
		User getUserByName(std::string);
		// Etablissement getEtablissement(int);
		void initUsersTable();
		void initEtablishmentTable();
		void checkError(int, char*);
		int getHighestId(char*);
		int xmlParser(std::string);
		int recursiveParser(TiXmlElement*);
		void restInfos(TiXmlElement*);
		void barInfos(TiXmlElement*);
		// void debut_element(void *user_data, const xmlChar *, const xmlChar **);
		//int getHighestId(char*);
		static int callbackFunction(void*, int, char**, char**);
		static int getUserCallback(void*, int, char**, char**);
		static int getEtablCallback(void*, int, char**, char**);
		template<typename xml,class etab>

		void restCase(xml temp,etab currentEtab){

			std::string tempText;
			if (temp->GetText()){tempText = temp->GetText();}
			std::string elem = temp->Value();
			std::cout<<elem<<std::endl;
			std::string::size_type sz;
			if (elem =="Name"){currentEtab->setNom(tempText);}
			else if (elem =="Street"){_currentAdr = tempText;}
			else if(elem =="Num"){_currentAdr += " " + tempText;}
			else if(elem =="Zip"){ 
			_currentAdr += " " + tempText;
			currentEtab->setLocalite(std::stoi(tempText));
			}
			else if(elem =="City"){_currentAdr += " " + tempText;
				currentEtab->setAdresse(_currentAdr);
			}
			else if(elem =="Longitude") {_long = std::stof(tempText,&sz);}
			else if(elem =="Latitude") {currentEtab->setCoords(std::stof(tempText,&sz),_long);}
			else if(elem =="Tel"){currentEtab->setNumTel(tempText);}
			else if(elem =="Site"){currentEtab->setSiteWeb(temp->Attribute("link"));}
		}
		
};
#endif /* DATABASE_HPP */