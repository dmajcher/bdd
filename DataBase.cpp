#include "DataBase.hpp"


DataBase::DataBase(char* dataBaseName) {
	char* errorMsg;
	sqlite3_open(dataBaseName, &_dataBase);
	sqlite3_exec(_dataBase, "PRAGMA foreign_keys = ON", 0, 0, 0);
	initUsersTable();
	initEtablishmentTable();
	initCommentsTable();
	User newUser("Flo", "legrand", "flo@gmail.com", 160502, 1);
	User newUser2("David", "password123", "david@gmail.com", 160501, -1);
    addUser(newUser);
	addUser(newUser2);
	//delUser(newUser2);
	xmlParser();
    // Bar bar(true, true);
    // Hotel hotel(3,40,100);
    Restaurant resto(12, true, true, "FOOOOOO", 50);
    // resto.setEid(1);
    // bar.setEtabInfos("le dorum", "rue du poulet", 1080, "0474225229", "www.lepoulet.be", 1, 160505, 160, 95);
    // resto.setEtabInfos("le reste haut", "rue du chevreuil", 1050, "0478275299", "www.lechevreuil.be", 1, 160505, 120, 90);
    // hotel.setEtabInfos("l'autel", "rue du marsouin", 1050, "0478789635", "www.lautel.be", 1, 160505, 140, 110);
    // addRestaurant(resto);
    // addBar(bar);
    // addHotel(hotel);
    // delEtablissement(resto);
    Commentaire comm("David", "à chier", 0, 1);
    // addCommentaire(comm);
    comm.setCid(1);
    delCommentaire(comm);
}



void DataBase::initUsersTable() {
	int errorStatus;
	char* errorMsg;
	const char* tableCreation = "CREATE TABLE IF NOT EXISTS Utilisateurs("\
	"NameId TEXT PRIMARY KEY,"\
	"Email TEXT NOT NULL UNIQUE,"\
	"Password TEXT NOT NULL,"\
	"DateInscription INTEGER NOT NULL,"\
	"Admin INTEGER)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::initCommentsTable() {
	int errorStatus;
	char* errorMsg;
	const char* tableCreation = "CREATE TABLE IF NOT EXISTS Commentaires("\
	"CID INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"Auteur TEXT NOT NULL,"\
	"Texte TEXT NOT NULL,"\
	"Score INTEGER NOT NULL,"\
	"EidConcerne INTEGER NOT NULL,"\
	"FOREIGN KEY (EidConcerne) REFERENCES Etablissements ON DELETE CASCADE,"\
	"FOREIGN KEY (Auteur) REFERENCES Utilisateurs ON DELETE CASCADE)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, NULL, 0, &errorMsg);
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
	"AdminCreateur TEXT NOT NULL,"\
	"DateCreation TEXT NOT NULL,"\
	"Latitude REAL NOT NULL,"\
	"Longitude REAL NOT NULL)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Restaurants("\
	"RID INTEGER PRIMARY KEY,"\
	"PrixPlats INTEGER NOT NULL,"\
	"TakeAway INTEGER NOT NULL,"\
    "Livraison INTEGER NOT NULL,"\
	"HoraireFermeture TEXT NOT NULL,"\
	"NbPlacesBanquet INTEGER NOT NULL,"\
	"FOREIGN KEY (RID) REFERENCES Etablissements ON DELETE CASCADE)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Bars("\
	"BID INTEGER PRIMARY KEY,"\
	"Fumeur INTEGER NOT NULL,"\
	"PetiteRestauration INTEGER NOT NULL,"\
	"FOREIGN KEY (BID) REFERENCES Etablissements ON DELETE CASCADE)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Hotels("\
	"HID INTEGER PRIMARY KEY,"\
	"NbEtoiles INTEGER NOT NULL,"\
    "NbChambres INTEGER NOT NULL,"\
	"IndicePrix INTEGER NOT NULL,"\
	"FOREIGN KEY (HID) REFERENCES Etablissements ON DELETE CASCADE)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, NULL, 0, &errorMsg);
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
		if (_currentRest){
		addRestaurant(*_currentRest);
		}
		// _currentRest = new Etablissement();
		_currentRest = new Restaurant(-1,false,false,"",-1);
		_currentRest->setDate(temp->Attribute("creationDate"));
		_currentRest->setAdmin(temp->Attribute("nickname"));
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
	if (elem =="Name"){_currentRest->setNom(tempText);}
	else if (elem =="Street"){_currentAdr = tempText;}
	else if(elem =="Num"){_currentAdr += " " + tempText;}
	else if(elem =="Zip"){ 
		_currentAdr += " " + tempText;
		_currentRest->setLocalite(std::stoi(tempText));
	}
	else if(elem =="City"){_currentAdr += " " + tempText;
		_currentRest->setAdresse(_currentAdr);
	}
	else if(elem =="Longitude") {_long = std::stof(tempText,&sz);}
	else if(elem =="Latitude") {_currentRest->setCoords(std::stof(tempText,&sz),_long);}
	else if(elem =="Tel"){_currentRest->setNumTel(tempText);}
	else if(elem =="Site"){_currentRest->setSiteWeb(temp->Attribute("link"));}
	else if(elem =="On"){}	
	else if(elem =="TakeAway"){_currentRest->setTakeAway(true);}
	else if(elem =="Delivery"){_currentRest->setLivraison(true);}
	else if(elem =="PriceRange"){_currentRest->setPrix(std::stof((tempText),&sz));}
	else if(elem =="Banquet"){_currentRest->setNbPlaces(std::stoi(temp->Attribute("capacity")));}
}
	

void DataBase::addUser(User &newUser) {
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Utilisateurs(NameId, Email, Password, dateInscription, Admin) VALUES("+\
	gu+newUser.getName()+gu+vir +gu+newUser.getEmail()+gu+vir +gu+newUser.getPassword()+gu+vir +std::to_string(newUser.getCreationDate())+vir+\
	std::to_string(newUser.isAdmin())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::addEtablissement(Etablissement &newEtab) {
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Etablissements(Nom, Adresse, Localite, NumTel, SiteWeb, AdminCreateur, DateCreation, Latitude, Longitude) VALUES("+\
    gu+newEtab.getNom()+gu+vir +gu+newEtab.getAdresse()+gu+vir +std::to_string(newEtab.getLocalite())+vir +gu+newEtab.getNumTel()+gu+vir +gu+newEtab.getSiteWeb()+gu+vir+\
	gu+newEtab.getAdmin()+gu+vir +gu+newEtab.getDateCreation()+gu+vir +std::to_string(newEtab.getLatitude())+vir +std::to_string(newEtab.getLongitude())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::addRestaurant(Restaurant &newResto) {
	addEtablissement(newResto);
	std::cout<<"resto"<<std::endl;
    char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string maxEid = "(SELECT MAX(EID) FROM Etablissements)";
	std::string query = "INSERT INTO Restaurants(RID, PrixPlats, TakeAway, Livraison, HoraireFermeture, NbPlacesBanquet) VALUES("+\
	maxEid+vir +std::to_string(newResto.getPrix())+vir +std::to_string(newResto.hasTakeAway())+vir +std::to_string(newResto.hasLivraison())+\
    vir +gu+newResto.getHoraire()+gu+vir +std::to_string(newResto.getNbPlaces())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::addBar(Bar &newBar) {
	addEtablissement(newBar);
    char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string maxEid = "(SELECT MAX(EID) FROM Etablissements)";
	std::string query = "INSERT INTO Bars(BID, Fumeur, PetiteRestauration) VALUES("+\
	maxEid+vir +std::to_string(newBar.isFumeur())+vir +std::to_string(newBar.hasPetiteResto())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::addHotel(Hotel &newHotel) {
	addEtablissement(newHotel);
    char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string maxEid = "(SELECT MAX(EID) FROM Etablissements)";
	std::string query = "INSERT INTO Hotels(HID, NbEtoiles, NbChambres, IndicePrix) VALUES("+\
	maxEid+vir +std::to_string(newHotel.getEtoiles())+vir +std::to_string(newHotel.getChambres())+vir +std::to_string(newHotel.getIndicePrix())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::addCommentaire(Commentaire &newComm) {
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Commentaires(Auteur, Texte, Score, EidConcerne) VALUES("+\
	gu+newComm.getAuteur()+gu+vir +gu+newComm.getTexte()+gu+vir +std::to_string(newComm.getScore())+vir +std::to_string(newComm.getEidConcerne())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::delUser(User &userToDel) {
	char* errorMsg;
	std::string gu = "\"";
	std::string query = "DELETE FROM Utilisateurs WHERE (NameId = "+gu+userToDel.getName()+gu+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);	
}



void DataBase::delEtablissement(Etablissement &etabToDel) {
    std::cout<<etabToDel.getEid()<<std::endl;
	char* errorMsg;
	std::string gu = "\"";
	std::string query = "DELETE FROM Etablissements WHERE (EID = "+std::to_string(etabToDel.getEid())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);	
}



void DataBase::delCommentaire(Commentaire &commToDel) {
	char* errorMsg;
	std::string gu = "\"";
	std::string query = "DELETE FROM Commentaires WHERE (CID = "+std::to_string(commToDel.getCid())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);	
}
 


User DataBase::getUserByName(std::string nameId) {
	char* errorMsg;
	std::string gu="\"";
	std::string query = "SELECT NameId, Email, Password, dateInscription FROM Utilisateurs WHERE(NameId = "+gu+nameId+gu+")";
	User userRequested("", "", "", -1, -1);
    User* userRequestedPtr = &userRequested;
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), getUserCallback, userRequestedPtr, &errorMsg);
	checkError(errorStatus, errorMsg);
	return userRequested;
}



Restaurant DataBase::getRestoByName(std::string restoName) {
	char* errorMsg;
	std::string gu="\"";
	std::string query = "SELECT Nom, Adresse, Localite, NumTel, SiteWeb, Latitude, Longitude FROM Etablissements WHERE(EID = "+gu+restoName+gu+")";
	Restaurant restoRequested(-1, false, false, "", -1);
	Restaurant* restoRequestedPtr = &restoRequested;
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, restoRequestedPtr, &errorMsg);
	checkError(errorStatus, errorMsg);
	return restoRequested;
}



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
    // if (argv[4] != "NULL")
    //     temp->setAdminId(atoi(argv[4]));
    // else
    //     temp->setAdminId(-1);
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