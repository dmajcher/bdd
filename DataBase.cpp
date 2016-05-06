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
	User newUser("Flo", "legrand", "flo@gmail.com", 160502, 1);
	User newUser2("David", "password123", "david@gmail.com", 160501, -1);
    addUser(newUser);
	addUser(newUser2);
	//delUser(newUser2);
    Bar bar(true, true);
    Hotel hotel(3,40,100);
    Restaurant resto(12, true, true, "FOOOOOO", 50);
    bar.setEtabInfos("le dorum", "rue du poulet", 1080, "0474225229", "www.lepoulet.be", 1, 160505, 160, 95);
    resto.setEtabInfos("le reste haut", "rue du chevreuil", 1050, "0478275299", "www.lechevreuil.be", 1, 160505, 120, 90);
    hotel.setEtabInfos("l'autel", "rue du marsouin", 1050, "0478789635", "www.lautel.be", 1, 160505, 140, 110);
    addRestaurant(resto);
    addBar(bar);
    addHotel(hotel);
    delEtablissement(resto);
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
	"DateCreation INTEGER NOT NULL,"\
	"Latitude REAL NOT NULL,"\
	"Longitude REAL NOT NULL)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Restaurants("\
	"RID INTEGER PRIMARY KEY,"\
	"PrixPlats INTEGER NOT NULL,"\
	"TakeAway INTEGER NOT NULL,"\
    "Livraison INTEGER NOT NULL,"\
	"HoraireFermeture TEXT NOT NULL,"\
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



// void DataBase::debut_element(void *user_data, const xmlChar *name, const xmlChar **attrs) {
//     printf("Début de l'élément : %s\n", name);
// }



// int DataBase::xmlParser(){
// 	// Initialisation à zéro de tous les membres (NULL pour un pointeur par conversion)
//     xmlSAXHandler sh = { 0 };

//     // Affectation des fonctions de rappel
//     sh.startElement = debut_element;

//     xmlParserCtxtPtr ctxt;
//     // Création du contexte
//     if ((ctxt = xmlCreateFileParserCtxt("Restaurants.xml")) == NULL) {
//         fprintf(stderr, "Erreur lors de la création du contexte\n");
//         return EXIT_FAILURE;
//     }
//     // Fonctions de rappel à utiliser
//     ctxt->sax = &sh;
//     // Analyse
//     xmlParseDocument(ctxt);
//     // Le document est-il bien formé ?
//     if (ctxt->wellFormed) {
//         printf("Document XML bien formé\n");
//     } else {
//         fprintf(stderr, "Document XML mal formé\n");
//         xmlFreeParserCtxt(ctxt);
//         return EXIT_FAILURE;
//     }
//     // Libération de la mémoire
//     xmlFreeParserCtxt(ctxt);

//     return EXIT_SUCCESS;
// }



void DataBase::addUser(User newUser) {
	char* errorMsg;
    int adminId = newUser.getAdminId();
    std::string adminIdTxt;
    if (adminId != -1) 
        adminIdTxt = std::to_string(adminId);
    else
        adminIdTxt = "NULL";
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Utilisateurs(NameId, Email, Password, dateInscription, AdminId) VALUES("+\
	gu+newUser.getName()+gu+vir +gu+newUser.getEmail()+gu+vir +gu+newUser.getPassword()+gu+vir +std::to_string(newUser.getCreationDate())+vir +adminIdTxt+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	_nextUserId+=1;
	_nextAdminId+=1;
}



void DataBase::addEtablissement(Etablissement &newEtab) {
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Etablissements(Nom, Adresse, Localite, NumTel, SiteWeb, AdminCreateur, DateCreation, Latitude, Longitude) VALUES("+\
    gu+newEtab.getNom()+gu+vir +gu+newEtab.getAdresse()+gu+vir +std::to_string(newEtab.getLocalite())+vir +gu+newEtab.getNumTel()+gu+vir +gu+newEtab.getSiteWeb()+gu+vir+\
	std::to_string(newEtab.getAdmin())+vir +std::to_string(newEtab.getDateCreation())+vir +std::to_string(newEtab.getLatitude())+vir +std::to_string(newEtab.getLongitude())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::addRestaurant(Restaurant &newResto) {
	addEtablissement(newResto);
    char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Restaurants(RID, PrixPlats, TakeAway, Livraison, HoraireFermeture, NbPlacesBanquet) VALUES("+\
	std::to_string(_nextEtabId)+vir +std::to_string(newResto.getPrix())+vir +std::to_string(newResto.hasTakeAway())+vir +std::to_string(newResto.hasLivraison())+\
    vir +gu+newResto.getHoraire()+gu+vir +std::to_string(newResto.getNbPlaces())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
    newResto.setEid(_nextEtabId);
	_nextEtabId += 1;
}



void DataBase::addBar(Bar &newBar) {
	addEtablissement(newBar);
    char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Bars(BID, Fumeur, PetiteRestauration) VALUES("+\
	std::to_string(_nextEtabId)+vir +std::to_string(newBar.isFumeur())+vir +std::to_string(newBar.hasPetiteResto())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
    newBar.setEid(_nextEtabId);
	_nextEtabId += 1;
}



void DataBase::addHotel(Hotel &newHotel) {
	addEtablissement(newHotel);
    char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Hotels(HID, NbEtoiles, NbChambres, IndicePrix) VALUES("+\
	std::to_string(_nextEtabId)+vir +std::to_string(newHotel.getEtoiles())+vir +std::to_string(newHotel.getChambres())+vir +std::to_string(newHotel.getIndicePrix())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
    newHotel.setEid(_nextEtabId);
	_nextEtabId += 1;
}



void DataBase::delUser(User userToDel) {
	char* errorMsg;
	std::string gu = "\"";
	std::string query = "DELETE FROM Utilisateurs WHERE (NameId = "+gu+userToDel.getName()+gu+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);	
}



void DataBase::delEtablissement(Etablissement &etabToDel) {
    std::cout<<etabToDel.getEid()<<std::endl;
	char* errorMsg;
	std::string gu = "\"";
	std::string query = "DELETE FROM Etablissements WHERE (EID = "+std::to_string(etabToDel.getEid())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
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