#include "DataBase.hpp"


DataBase::DataBase(char* dataBaseName) {
	char* errorMsg;
	_nextUserId = 1;
	_nextAdminId = 1;
	_nextEtabId = 1;
	sqlite3_open(dataBaseName, &_dataBase);
	sqlite3_exec(_dataBase, "PRAGMA foreign_keys = ON", 0, 0, 0);
	initUsersTable();
	initEtablishmentTable();
	User newUser("Flo", "legrand", "flo@gmail.com", 160502);
	User newUser2("David", "password123", "david@gmail.com", 160501);
	//addUser(newUser);
	//addUser(newUser2);
	//delUser(newUser2);
	User yoUser = getUserByName("Flo");
	xmlParser();
	std::cout<<yoUser.getEmail()<<yoUser.getPassword()<<yoUser.getCreationDate()<<std::endl;
}


void DataBase::initUsersTable() {
	int errorStatus;
	char* errorMsg;
	const char* tableCreation = "CREATE TABLE IF NOT EXISTS Utilisateurs("\
	"UID INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"NameId TEXT NOT NULL UNIQUE,"\
	"Email TEXT NOT NULL UNIQUE,"\
	"Password TEXT NOT NULL,"\
	"DateInscription INTEGER NOT NULL,"\
	"AdminId INTEGER UNIQUE)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}

void DataBase::initEtablishmentTable() {
	int errorStatus;
	char* errorMsg;
	
	const char* tableCreation = "CREATE TABLE IF NOT EXISTS Etablissements("\
	"EID INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"Nom TEXT NOT NULL,"\
	"Adresse TEXT NOT NULL,"\
	"Localite INTEGER NOT NULL,"\
	"NumTel TEXT NOT NULL,"\
	"SiteWeb TEXT,"\
	"AdminCreateur INTEGER NOT NULL,"\
	"DateCreation TEXT NOT NULL,"\
	"Latitude REAL NOT NULL,"\
	"Longitude REAL NOT NULL,"\
	"FOREIGN KEY(AdminCreateur) REFERENCES Admin)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Restaurants("\
	"RID INTEGER PRIMARY KEY,"\
	"PrixPlats REAL NOT NULL,"\
	"TakeAway INTEGER NOT NULL,"\
    "Livraison INTEGER NOT NULL,"\
	"HoraireFermeture TEXT NOT NULL,"\
	"DemiJoursFermeture INTEGER NOT NULL,"\
	"NbPlacesBanquet INTEGER NOT NULL,"\
	"FOREIGN KEY (RID) REFERENCES Etablissements ON DELETE CASCADE)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Bars("\
	"BID INTEGER PRIMARY KEY,"\
	"Fumeur INTEGER NOT NULL,"\
	"PetiteRestauration INTEGER NOT NULL,"\
	"FOREIGN KEY (BID) REFERENCES Etablissements ON DELETE CASCADE)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Hotels("\
	"HID INTEGER PRIMARY KEY,"\
	"NbEtoiles INTEGER NOT NULL,"\
    "NbChambres INTEGER NOT NULL,"\
	"IndicePrix INTEGER NOT NULL,"\
	"FOREIGN KEY (HID) REFERENCES Etablissements ON DELETE CASCADE)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}

int DataBase::xmlParser(){
	TiXmlDocument doc("Restaurants.xml");
	if(!doc.LoadFile()){
    	std::cerr << "erreur lors du chargement" << std::endl;
    	std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
    return 1;
	}

	TiXmlHandle hdlparent(&doc);
	TiXmlElement* restaurant = hdlparent.FirstChildElement().FirstChildElement().Element();
	recursiveParser(restaurant);
	//TiXmlElement* temp = doc
}
int DataBase::recursiveParser(TiXmlElement *temp){
	//std::cout<<temp->Value()<<std::endl;
	std::cout<<temp->Value()<<std::endl;
	std::string info = temp->Value();
	if (temp == nullptr){return 1;}
	else if (info == "Restaurant"){
		if (_currentEtab){
		addEtablissement(*_currentEtab);
		addRestaurant(*_currentRest);
		}
		_currentEtab = new Etablissement();
		_currentRest = new Restaurant();
		_currentEtab->setDate(temp->Attribute("creationDate"));
		_currentEtab->setAdmin(temp->Attribute("nickname"));
	}
	restCase(temp);
	if (temp->FirstChildElement()){recursiveParser(temp->FirstChildElement());}
	if(temp->NextSiblingElement()){recursiveParser(temp->NextSiblingElement());} 
}

void DataBase::restCase(TiXmlElement* temp){
	std::string tempText;
	if (temp->GetText()){tempText = temp->GetText();}
	std::string elem = temp->Value();
	std::string::size_type sz;
	if (elem =="Name"){_currentEtab->setNom(tempText);}
	else if (elem =="Street"){_currentAdr = tempText;}
	else if(elem =="Num"){_currentAdr += " " + tempText;}
	else if(elem =="Zip"){ 
		_currentAdr += " " + tempText;
		_currentEtab->setLocalite(std::stoi(tempText));
	}
	else if(elem =="City"){_currentAdr += " " + tempText;}	
	else if(elem =="Longitude") {_long = std::stof(tempText,&sz);}
	else if(elem =="Latitude") {_currentEtab->setCoords(std::stof(tempText,&sz),_long);}
	else if(elem =="Tel"){_currentEtab->setNumTel(tempText);}
	else if(elem =="Site"){_currentEtab->setSiteWeb(temp->Attribute("link"));}
	else if(elem =="On"){}	
	else if(elem =="TakeAway"){_currentRest->setTakeAway(true);}
	else if(elem =="Delivery"){_currentRest->setLivraison(true);}
	else if(elem =="PriceRange"){_currentRest->setPrix(std::stof((tempText),&sz));}
	else if(elem =="Banquet"){_currentRest->setNbPlaces(std::stoi(temp->Attribute("capacity")));}
}


void DataBase::addUser(User newUser) {
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "'";
	std::string query = "INSERT INTO Utilisateurs(NameId, Email, Password, dateInscription) VALUES("+\
	gu+newUser.getName()+gu+vir +gu+newUser.getEmail()+gu+vir +gu+newUser.getPassword()+gu+vir +std::to_string(newUser.getCreationDate());
	query += ")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	_nextUserId+=1;
	_nextAdminId+=1;
}



void DataBase::addEtablissement(Etablissement newEtab) {
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "'";
	std::string query = "INSERT INTO Etablissements(Nom, Adresse, Localite, NumTel, SiteWeb, AdminCreateur, DateCreation, Latitude, Longitude) VALUES("+\
    gu+newEtab.getNom()+gu+vir +gu+newEtab.getAdresse()+gu+vir +std::to_string(newEtab.getLocalite())+vir +gu+newEtab.getNumTel()+gu+vir +\
	gu+newEtab.getAdmin()+gu+vir +(newEtab.getDateCreation())+vir +std::to_string(newEtab.getLatitude())+vir +std::to_string(newEtab.getLongitude());
	query += ")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::addRestaurant(Restaurant newResto) {
	addEtablissement(newResto);
    char* errorMsg;
	std::string vir = ",";
	std::string gu = "'";
	std::string query = "INSERT INTO Restaurants(RID, PrixPlats, TakeAway, Livraison, HoraireFermeture, DemiJoursFermeture, NbPlacesBanquet) VALUES("+\
	std::to_string(_nextEtabId)+vir +std::to_string(newResto.getPrix())+vir +std::to_string(newResto.hasTakeAway())+vir +std::to_string(newResto.hasLivraison())+vir +gu+newResto.getHoraire()+gu+vir +\
	std::to_string(newResto.getDemiJours())+vir +std::to_string(newResto.getNbPlaces());
	query+=")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	_nextEtabId += 1;
}



void DataBase::addBar(Bar newBar) {
	addEtablissement(newBar);
    char* errorMsg;
	std::string vir = ",";
	std::string gu = "'";
	std::string query = "INSERT INTO Bars(BID, Fumeur, PetiteRestauration) VALUES("+\
	std::to_string(_nextEtabId)+vir +std::to_string(newBar.isFumeur())+vir +std::to_string(newBar.hasPetiteResto());
	query+=")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	_nextEtabId += 1;
}



void DataBase::addHotel(Hotel newHotel) {
	addEtablissement(newHotel);
    char* errorMsg;
	std::string vir = ",";
	std::string gu = "'";
	std::string query = "INSERT INTO Hotels(HID, NbEtoiles, IndicePrix) VALUES("+\
	std::to_string(_nextEtabId)+vir +std::to_string(newHotel.getEtoiles())+vir +std::to_string(newHotel.getChambres())+vir +std::to_string(newHotel.getIndicePrix());
	query+=")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	_nextEtabId += 1;
}



void DataBase::delUser(User userToDel) {
	char* errorMsg;
	std::string gu = "'";
	std::string query = "DELETE FROM Utilisateurs WHERE (NameId = "+gu+userToDel.getName()+gu;
	query += ")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);	
}



void DataBase::delEtablissement(Etablissement etabToDel) {
	char* errorMsg;
	std::string gu = "'";
	std::string query = "DELETE FROM Etablissements WHERE (EID = "+etabToDel.getEid();
	query += ")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);	
}
 


User DataBase::getUserByName(std::string nameId) {
	char* errorMsg;
	std::string gu="'";
	std::string query = "SELECT NameId, Email, Password, dateInscription FROM Utilisateurs WHERE(NameId = "+gu+nameId+gu;
	query += ")";
	User* userRequested = new User("", "", "", -1);
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), getUserCallback, userRequested, &errorMsg);
	checkError(errorStatus, errorMsg);
	std::cout<<"adr1 "<<userRequested<<std::endl;
	//std::cout<<userRequested->getEmail()<<std::endl;
	return *userRequested;
}



// Etablissement DataBase::getEtablissement(int eID) {
// 	char* errorMsg;
// 	std::string gu="'";
// 	std::string query = "SELECT Nom, Adresse, Localite, NumTel, SiteWeb, Latitude, Longitude FROM Etablissements WHERE(EID = "+eID;
// 	query += ")";
// 	Etablissement* etablRequested = new Etablissement("", "", -1, "", "", -1, -1);
// 	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), getEtablCallback, etablRequested, &errorMsg);
// 	checkError(errorStatus, errorMsg);
// 	return *etablRequested;
// }



int DataBase::callbackFunction(void* NotUsed, int argc, char** argv, char** azColName) {
   int i;
   std::cout<<argc<<std::endl;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;	
}



int DataBase::getUserCallback(void* user, int argc, char** argv, char** azColName) {
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n"); 
    User* temp = (User*) user; 	
    temp->setName(argv[0]);
    temp->setEmail(argv[1]);
    temp->setPassword(argv[2]);
    temp->setCreationDate(atoi(argv[3]));
    std::cout<<"adr2 "<<user<<std::endl;
    return 0;	
}



int DataBase::getEtablCallback(void* etabl, int argc, char** argv, char** azColName) {
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n"); 
    Etablissement* temp = (Etablissement*) etabl; 	
    temp->setNom(argv[0]);
    temp->setAdresse(argv[1]);
    temp->setLocalite(atoi(argv[2]));
    temp->setNumTel(argv[3]);
    temp->setSiteWeb(argv[4]);
    temp->setCoords(atof(argv[5]), atof(argv[6]));
    return 0;	
}



int DataBase::getHighestId(char* res) {
	const char* highestIdchar = res ? res : "0";
	int highestId = atoi(highestIdchar);
	return highestId;
}



void DataBase::checkError(int errorStatus, char* errorMsg) {
    if (errorStatus) {
        fprintf(stderr, "Error on database: %s\n", errorMsg);
        exit(0);
	}
    else {
        fprintf(stdout, "Operation succeed\n");
    }
}

// Bar DataBase::fetchBarInfos(){}



DataBase::~DataBase() {
	sqlite3_close(_dataBase);
}