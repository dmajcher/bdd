#include "DataBase.hpp"


DataBase::DataBase(char* dataBaseName) {
	char* errorMsg;
	_nextUserId = 1;
	_nextAdminId = 1;
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
	"Localite INT NOT NULL,"\
	"NumTel TEXT NOT NULL,"\
	"SiteWeb TEXT,"\
	"AdminCreateur INTEGER NOT NULL,"\
	"DateCreation INTEGER NOT NULL,"\
	"Latitude REAL NOT NULL,"\
	"Longitude REAL NOT NULL,"\
	"FOREIGN KEY(AdminCreateur) REFERENCES Admin)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Restaurants("\
	"RID INTEGER PRIMARY KEY,"\
	"PrixPlats REAL NOT NULL,"\
	"TakeAway INTEGER NOT NULL,"\
	"HoraireFermeture TEXT NOT NULL,"\
	"DemiJoursFermeture INTEGER NOT NULL,"\
	"NbPlacesBanquet INTEGER NOT NULL,"\
	"FOREIGN KEY (RID) REFERENCES Etablissements)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Bars("\
	"BID INTEGER PRIMARY KEY,"\
	"Fumeur INTEGER NOT NULL,"\
	"PetiteRestauration INTEGER NOT NULL,"\
	"FOREIGN KEY (BID) REFERENCES Etablissements)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	
	tableCreation = "CREATE TABLE IF NOT EXISTS Hotels("\
	"HID INTEGER PRIMARY KEY,"\
	"NbEtoiles INTEGER NOT NULL,"\
	"IndicePrix INTEGER NOT NULL,"\
	"FOREIGN KEY (HID) REFERENCES Etablissements)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}	

void debut_element(void *user_data, const xmlChar *name, const xmlChar **attrs) {
    printf("Début de l'élément : %s\n", name);
}

void xmlParser(){
	// Initialisation à zéro de tous les membres (NULL pour un pointeur par conversion)
    xmlSAXHandler sh = { 0 };

    // Affectation des fonctions de rappel
    sh.startElement = debut_element;

    xmlParserCtxtPtr ctxt;
    // Création du contexte
    if ((ctxt = xmlCreateFileParserCtxt("Restaurants.xml")) == NULL) {
        fprintf(stderr, "Erreur lors de la création du contexte\n");
        return EXIT_FAILURE;
    }
    // Fonctions de rappel à utiliser
    ctxt->sax = &sh;
    // Analyse
    xmlParseDocument(ctxt);
    // Le document est-il bien formé ?
    if (ctxt->wellFormed) {
        printf("Document XML bien formé\n");
    } else {
        fprintf(stderr, "Document XML mal formé\n");
        xmlFreeParserCtxt(ctxt);
        return EXIT_FAILURE;
    }
    // Libération de la mémoire
    xmlFreeParserCtxt(ctxt);

    return EXIT_SUCCESS;
}
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



void DataBase::delUser(User userToDel) {
	char* errorMsg;
	std::string gu = "'";
	std::string query = "DELETE FROM Utilisateurs WHERE (NameId = "+gu+userToDel.getName()+gu;
	query += ")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);	
}
 


User DataBase::getUserByName(std::string nameId) {
	char* errorMsg;
	std::string gu="'";
	std::string query = "SELECT NameId, Email, Password, dateInscription FROM Utilisateurs WHERE(NameId = "+gu+nameId+gu;
	query += ")";
	User* userRequested = new User("bidon", "bidon", "bidon", -1);
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), selectCallbackFunction, userRequested, &errorMsg);
	checkError(errorStatus, errorMsg);
	std::cout<<"adr1 "<<userRequested<<std::endl;
	//std::cout<<userRequested->getEmail()<<std::endl;
	return *userRequested;
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



int DataBase::selectCallbackFunction(void* user, int argc, char** argv, char** azColName) {
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

Bar Database::fetchBarInfos()



DataBase::~DataBase() {
	sqlite3_close(_dataBase);
}
