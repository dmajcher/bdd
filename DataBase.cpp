#include "DataBase.hpp"


DataBase::DataBase(char* dataBaseName) {
	_nextUserId = 1;
	_nextAdminId = 1;
	sqlite3_open(dataBaseName, &_dataBase);
	sqlite3_exec(_dataBase, "PRAGMA foreign_keys = ON", 0, 0, 0);
	initUsersTable();
	initEtablishmentTable();
	const char* dbRequest = "INSERT INTO Utilisateurs(NameId, Email, Password, dateInscription) VALUES('David', 'david@gmail.com', 'password123', 160502)";
	char* errorMsg;
	User newUser("Flo", "legrand", "flo@gmail.com", 160502);
	int errorStatus = sqlite3_exec(_dataBase, dbRequest, callbackFunction, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	addUser(newUser);
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



void DataBase::addUser(User newUser) {
	char* userAdding; 
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



int DataBase::callbackFunction(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   std::cout<<argc<<std::endl;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
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



DataBase::~DataBase() {
	sqlite3_close(_dataBase);
}
