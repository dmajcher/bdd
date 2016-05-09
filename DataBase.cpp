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
	User yoUser = getUserByName("Flo");
	xmlParser("Restaurants.xml");
	_isRestaurant = false;
	xmlParser("Cafes.xml");
    Restaurant resto(12, true, true, "FOOOOOO", 50);
    Commentaire comm("Flo", "10/05/16", "mauvais", 1, 1);
    addCommentaire(comm);
    std::vector<Etablissement*> t = getEtabByName("Nom = 'Mirabelle'");
    Bar* barPtr;
    Restaurant* restoPtr;
    Hotel* hotelPtr;
    barPtr = dynamic_cast<Bar*>(t[0]);
	restoPtr = dynamic_cast<Restaurant*>(t[0]);
	hotelPtr = dynamic_cast<Hotel*>(t[0]);
	Restaurant rest = *restoPtr;


    // comm.setCid(1);
    // delCommentaire(comm);
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
	"Date TEXT NOT NULL,"\
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
	"Longitude REAL NOT NULL,"\
	"Type CHARACTER(1) NOT NULL)";
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



int DataBase::xmlParser(std::string filename){
	std::cout<<filename<<std::endl;
	TiXmlDocument doc(filename);
	if(!doc.LoadFile()){
    	std::cerr << "erreur lors du chargement" << std::endl;
    	std::cerr << "error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << std::endl;
    return 1;
	}

	TiXmlHandle hdlparent(&doc);
	TiXmlElement* etablissement = hdlparent.FirstChildElement().FirstChildElement().Element();
	recursiveParser(etablissement);
	//TiXmlElement* temp = doc
}



int DataBase::recursiveParser(TiXmlElement *temp){
	std::string info = temp->Value();
	if (temp == nullptr) 
		return 1;
	else if (info == "Restaurant"){
		_isRestaurant = true;
		if (_currentEtab){
			_currentEtab->setHoraire(_tempConge);
			_tempConge="00000000000000";
			addRestaurant(*_currentEtab);
		}
		// _currentEtab = new Etablissement();
		_currentEtab = new Restaurant(-1,false,false,"",-1);
		_currentEtab->setDate(temp->Attribute("creationDate"));
		_currentEtab->setAdmin(temp->Attribute("nickname"));
	}
	else if (info == "Cafe"){
		if (_currentBar)
			addBar(*_currentBar);
		_currentBar = new Bar(false,false);
		_currentBar->setDate(temp->Attribute("creationDate"));
		_currentBar->setAdmin(temp->Attribute("nickname"));
	}

	if (_isRestaurant){
		restCase(temp,_currentEtab);
		restInfos(temp);
	}
	else{
		restCase(temp,_currentBar);
		barInfos(temp);
	}

	if (temp->FirstChildElement()) 
		recursiveParser(temp->FirstChildElement());
	if (temp->NextSiblingElement()) 
		recursiveParser(temp->NextSiblingElement()); 
}
		


template<typename xml, class etab>
void DataBase::restCase(xml temp,etab currentEtab){
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



void DataBase::restInfos(TiXmlElement* temp){

	std::string tempCongeAttrib;
	std::string tempText;
	if (temp->GetText()){tempText = temp->GetText();}
	std::string elem = temp->Value();
	std::cout<<elem<<std::endl;
	std::string::size_type sz;
	if(elem =="On"){
		if (temp->Attribute("hour")){tempCongeAttrib = temp->Attribute("hour");}
		if (tempCongeAttrib=="am"){_tempConge.replace(std::stoi(temp->Attribute("day"))*2,1,"F");}
		else if (tempCongeAttrib=="pm"){_tempConge.replace(std::stoi(temp->Attribute("day"))*2+1,1,"F");}
		else{_tempConge.replace(std::stoi(temp->Attribute("day"))*2,2,"FF");}
	}	
	else if(elem =="TakeAway"){_currentEtab->setTakeAway(true);}
	else if(elem =="Delivery"){_currentEtab->setLivraison(true);}
	else if(elem =="PriceRange"){_currentEtab->setPrix(std::stof((tempText),&sz));}
	else if(elem =="Banquet"){_currentEtab->setNbPlaces(std::stoi(temp->Attribute("capacity")));}

}



void DataBase::barInfos(TiXmlElement* temp){
	std::string tempText;
	if (temp->GetText()){tempText = temp->GetText();}
	std::string elem = temp->Value();
	std::cout<<elem<<std::endl;
	std::string::size_type sz;
	if(elem == "Smoking"){_currentBar->setFumeur(true);}
	else if (elem == "Snack"){_currentBar->setPetiteResto(true);}
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



void DataBase::addEtablissement(Etablissement &newEtab, std::string type) {
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Etablissements(Nom, Adresse, Localite, NumTel, SiteWeb, AdminCreateur, DateCreation, Latitude, Longitude, Type) VALUES("+\
    gu+newEtab.getNom()+gu+vir +gu+newEtab.getAdresse()+gu+vir +std::to_string(newEtab.getLocalite())+vir +gu+newEtab.getNumTel()+gu+vir +gu+newEtab.getSiteWeb()+gu+vir+\
	gu+newEtab.getAdmin()+gu+vir +gu+newEtab.getDateCreation()+gu+vir +std::to_string(newEtab.getLatitude())+vir +std::to_string(newEtab.getLongitude())+vir +gu+type+gu+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::addRestaurant(Restaurant &newResto) {
	addEtablissement(newResto, "R");
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
	addEtablissement(newBar, "B");
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
	addEtablissement(newHotel, "H");
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
	std::string eidConcerne = std::to_string(newComm.getEidConcerne());
	if (eidConcerne == "-1") 
		eidConcerne = "(SELECT MAX(EID) FROM Etablissements)";
	std::string query = "INSERT INTO Commentaires(Auteur, Date, Texte, Score, EidConcerne) VALUES("+\
	gu+newComm.getAuteur()+gu+vir +gu+newComm.getDate()+gu+vir +gu+newComm.getTexte()+gu+vir +\
	std::to_string(newComm.getScore())+vir +eidConcerne+")";
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



std::vector<Etablissement*> DataBase::getEtabByName(std::string condition) {
	char* errorMsg;
	std::string gu="\"";
   	std::string restoQuery = "SELECT PrixPlats, TakeAway, Livraison, HoraireFermeture, NbPlacesBanquet FROM Restaurants WHERE(RID = ";
   	std::string barQuery = "SELECT Fumeur, PetiteRestauration FROM Bars WHERE(BID = ";
   	std::string hotelQuery = "SELECT NbEtoiles, NbChambres, IndicePrix FROM Hotels WHERE(HID = ";
	std::string query = "SELECT Type, EID, Nom, Adresse, Localite, NumTel, SiteWeb, AdminCreateur, DateCreation, Latitude, Longitude FROM Etablissements WHERE("+condition+")";
	std::string eid;
	std::vector<Etablissement*> etabVector;
	std::vector<Etablissement*> * vectorPtr = &etabVector;
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), getEtabCallback, vectorPtr, &errorMsg);
	checkError(errorStatus, errorMsg);

	Bar* barPtr;
	Restaurant* restoPtr;
	Hotel* hotelPtr;
	for (int i = 0; i<etabVector.size(); ++i) {
		barPtr = dynamic_cast<Bar*>(etabVector[i]);
		restoPtr = dynamic_cast<Restaurant*>(etabVector[i]);
		hotelPtr = dynamic_cast<Hotel*>(etabVector[i]);
		eid = std::to_string(etabVector[i]->getEid()) + ")";
		if (barPtr != nullptr) {
			query = barQuery + eid;
			errorStatus = sqlite3_exec(_dataBase, query.c_str(), getBarCallback, etabVector[i], &errorMsg);
		}
		else if (restoPtr != nullptr) {
			query = restoQuery + eid;
			errorStatus = sqlite3_exec(_dataBase, query.c_str(), getRestoCallback, etabVector[i], &errorMsg);
		}
		else if (hotelPtr != nullptr) {
			query = hotelQuery + eid;
			errorStatus = sqlite3_exec(_dataBase, query.c_str(), getHotelCallback, etabVector[i], &errorMsg);
		}
		checkError(errorStatus, errorMsg);

	}

	return etabVector;
}



int DataBase::getEtabCallback(void* etabVectorPtr, int argc, char** argv, char** azColName) {
   	std::vector<Etablissement*> * vectorPtr = (std::vector<Etablissement*>*) etabVectorPtr;
   	std::cout<<argv[0]<<std::endl;
   	for (int i = 0; i<argc; i += 11) {
   		if (std::string(argv[i]) == "R") {
   			std::cout<<"R"<<std::endl;
   			vectorPtr->push_back(new Restaurant(-1, false, false, "", -1));
   		}
   		else if (std::string(argv[i]) == "H") {
   			std::cout<<"H"<<std::endl;
   			vectorPtr->push_back(new Hotel(-1, -1, -1));
   		}
   		else if (std::string(argv[i]) == "B") {
   			std::cout<<"B"<<std::endl;
   			vectorPtr->push_back(new Bar(false, false));
   		}
   		vectorPtr->at(i)->setEid(atoi(argv[1]));
   		vectorPtr->at(i)->setNom(argv[i+2]);
   		vectorPtr->at(i)->setAdresse(argv[i+3]);
   		vectorPtr->at(i)->setLocalite(atoi(argv[i+4]));
   		vectorPtr->at(i)->setNumTel(argv[i+5]);
   		vectorPtr->at(i)->setSiteWeb(argv[i+6]);
   		vectorPtr->at(i)->setAdmin(argv[i+7]);
   		vectorPtr->at(i)->setDate(argv[i+8]);
   		vectorPtr->at(i)->setCoords(atof(argv[i+9]), atof(argv[i+10]));
   		
   	}
   	return 0;	
}



int DataBase::getRestoCallback(void* restoPtr, int argc, char** argv, char** azColName) {
	Restaurant* tempRest = (Restaurant*) restoPtr;
	tempRest->setPrix(atoi(argv[0]));
	tempRest->setTakeAway(atoi(argv[1]));
	tempRest->setLivraison(atoi(argv[2]));
	tempRest->setHoraire(argv[3]);
	tempRest->setNbPlaces(atoi(argv[4]));
	return 0;
}



int DataBase::getBarCallback(void* barPtr, int argc, char** argv, char** azColName) {
	Bar* tempBar = (Bar*) barPtr;
	tempBar->setFumeur(atoi(argv[0]));
	tempBar->setPetiteResto(atoi(argv[1]));
	return 0;
}



int DataBase::getHotelCallback(void* hotelPtr, int argc, char** argv, char** azColName) {
	Hotel* tempHotel = (Hotel*) hotelPtr;
	tempHotel->setEtoiles(atoi(argv[0]));
	tempHotel->setChambres(atoi(argv[1]));
	tempHotel->setIndicePrix(atoi(argv[2]));
	return 0;
}



int DataBase::getUserCallback(void* userPtr, int argc, char** argv, char** azColName) {
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n"); 
    User* tempUser = (User*) userPtr; 	
    tempUser->setName(argv[0]);
    tempUser->setEmail(argv[1]);
    tempUser->setPassword(argv[2]);
    tempUser->setCreationDate(atoi(argv[3]));
    // if (argv[4] != "NULL")
    //     temp->setAdminId(atoi(argv[4]));
    // else
    //     temp->setAdminId(-1);
    return 0;	
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