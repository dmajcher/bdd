#include "DataBase.hpp"


DataBase::DataBase(char* dataBaseName) {
	char* errorMsg;
	sqlite3_open(dataBaseName, &_dataBase);
	sqlite3_exec(_dataBase, "PRAGMA foreign_keys = ON", 0, 0, 0);
	initUsersTable();
	initEtablishmentTable();
	initCommentsTable();
	initLabelsPrototypeTable();
	initLabelsContainerTable();
	xmlParser("../database/Restaurants.xml");
	_isRestaurant = false;
	xmlParser("../database/Cafes.xml");
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
	"Score INT NOT NULL,"\
	"EidConcerne INTEGER NOT NULL,"\
	"FOREIGN KEY (EidConcerne) REFERENCES Etablissements ON DELETE CASCADE,"\
	"FOREIGN KEY (Auteur) REFERENCES Utilisateurs ON DELETE CASCADE)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);

}
void DataBase::initLabelsPrototypeTable(){
	int errorStatus;
	char* errorMsg;
	const char* tableCreation = "CREATE TABLE IF NOT EXISTS Labels("\
	"LID INTEGER PRIMARY KEY AUTOINCREMENT,"\
	"Etiquette TEXT NOT NULL UNIQUE,"\
	"NbEtab INTEGER)";
	errorStatus = sqlite3_exec(_dataBase, tableCreation, NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}

void DataBase::initLabelsContainerTable(){
	int errorStatus;
	char* errorMsg;
	const char* tableCreation = "CREATE TABLE IF NOT EXISTS LabelContainer("\
	"UID TEXT NOT NULL,"\
	"EidConcerne INTEGER NOT NULL,"\
	"LID INTEGER NOT NULL,"\
	"PRIMARY KEY (UID , EidConcerne , LID),"\
	"FOREIGN KEY (UID) REFERENCES Utilisateurs ON DELETE CASCADE,"\
	"FOREIGN KEY (EidConcerne) REFERENCES Etablissements ON DELETE CASCADE,"\
	"FOREIGN KEY (LID) REFERENCES Labels ON DELETE CASCADE)";
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
			addAndDeleteCommentsObj();
			addAndDeleteLabObj();

		}
		// _currentEtab = new Etablissement();
		_currentEtab = new Restaurant(-1,false,false,"",-1);
		_currentEtab->setDate(temp->Attribute("creationDate"));
		User* currentUser  = new User(temp->Attribute("nickname"),"",temp->Attribute("nickname"),0,true);
		addUser(*currentUser);
		_currentEtab->setAdmin(temp->Attribute("nickname"));
	}
	else if (info == "Cafe"){
		if (_currentBar)
			addBar(*_currentBar);
			addAndDeleteCommentsObj();
			addAndDeleteLabObj();
		_currentBar = new Bar(false,false);
		_currentBar->setDate(temp->Attribute("creationDate"));
		User* currentUser  = new User(temp->Attribute("nickname"),"",temp->Attribute("nickname"),0,true);
		addUser(*currentUser);
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
		
void DataBase::addAndDeleteCommentsObj(){
	for (int i = 0;i<_currentComments.size();++i){
		addCommentaire(*_currentComments[i]);
		delete _currentComments[i];
	}
	_currentComments.clear();
}

void DataBase::addAndDeleteLabObj(){
	std::cout<<_currentLabels.size()<<std::endl;
	for (int i = 0;i<_currentLabels.size();++i){
		addLabel(*_currentLabels[i]);
		delete _currentLabels[i];
	}
	_currentLabels.clear();
}

template<typename xml, class etab>
void DataBase::restCase(xml temp,etab currentEtab){
	User* currentUser;
	std::string tempText;
		if (temp->GetText()){tempText = temp->GetText();}
		std::string elem = temp->Value();
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
		else if(elem =="Comment"){
			Commentaire* currentComment = new Commentaire("","","",0);
			currentUser = new User(temp->Attribute("nickname"),"",temp->Attribute("nickname"),0,false);
			addUser(*currentUser);
			currentComment->setAuteur(temp->Attribute("nickname"));
			currentComment->setDate(temp->Attribute("date"));
			currentComment->setScore(std::stoi(temp->Attribute("score")));
			currentComment->setText(tempText);
			_currentComments.push_back(currentComment);
		}
		else if(elem=="Tag"){
			TiXmlElement* tempUser = temp->FirstChildElement();
			while(tempUser){
				currentUser=new User(tempUser->Attribute("nickname"),"",tempUser->Attribute("nickname"),0,false);
				addUser(*currentUser);
				Label* currentLabel = new Label(-1,-1);
				currentLabel->setAuteur(tempUser->Attribute("nickname"));
				std::cout<<"Tag"<<std::endl;
				currentLabel->setEtiquette(temp->Attribute("name"));
				std::cout<<"Tag"<<std::endl;
				_currentLabels.push_back(currentLabel);
				if(tempUser->NextSiblingElement()){tempUser = tempUser->NextSiblingElement();}
				else{tempUser=nullptr;}
			}
		}
}



void DataBase::restInfos(TiXmlElement* temp){

	std::string tempCongeAttrib;
	std::string tempText;
	if (temp->GetText()){tempText = temp->GetText();}
	std::string elem = temp->Value();
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
	std::string::size_type sz;
	if(elem == "Smoking"){_currentBar->setFumeur(true);}
	else if (elem == "Snack"){_currentBar->setPetiteResto(true);}
}


void DataBase::addLabel(Label &newLabel) {
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string eidConcerne = std::to_string(newLabel.getEid());
	std::string lid = "(SELECT MAX(LID) FROM Labels)";
	if (eidConcerne == "-1") 
		eidConcerne = "(SELECT MAX(EID) FROM Etablissements)";
	std::string query = "INSERT INTO Labels(Etiquette, NbEtab) VALUES(" +gu+newLabel.getEtiquette()+gu+vir +"0)";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
	query = "INSERT INTO LabelContainer(UID, LID, EidConcerne) VALUES(" +gu+newLabel.getAuteur()+gu+vir +\
	lid+vir+eidConcerne+")";
	errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}


int DataBase::addUser(User &newUser) {
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string query = "INSERT INTO Utilisateurs(NameId, Email, Password, dateInscription, Admin) VALUES("+\
	gu+newUser.getName()+gu+vir +gu+newUser.getEmail()+gu+vir +gu+newUser.getPassword()+gu+vir +std::to_string(newUser.getCreationDate())+vir+\
	std::to_string(newUser.isAdmin())+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	int check = errorStatus;
	checkError(errorStatus, errorMsg);
	return check;
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
	std::cout<<"in comments"<<std::endl;
	char* errorMsg;
	std::string vir = ",";
	std::string gu = "\"";
	std::string eidConcerne = std::to_string(newComm.getEidConcerne());
	std::cout<<"out of comments"<<std::endl;
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
 


User DataBase::getUserByCond(std::string cond) {
	char* errorMsg;
	std::string gu="\"";
	std::string query = "SELECT NameId, Email, Password, dateInscription FROM Utilisateurs WHERE("+cond+")";
	User userRequested("", "", "", -1, -1);
    User* userRequestedPtr = &userRequested;
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), getUserCallback, userRequestedPtr, &errorMsg);
	checkError(errorStatus, errorMsg);
	return userRequested;
}



std::vector<Commentaire*> DataBase::getCommByCond(std::string cond) {
	char* errorMsg;
	std::string gu = "\"";
	std::string query = "SELECT Auteur, Date, Texte, Score, EidConcerne FROM Commentaires WHERE(" +cond+")";
	std::vector<Commentaire*> commVec;
	std::vector<Commentaire*> * commVecPtr = &commVec;
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), getCommCallback, commVecPtr, &errorMsg);
	checkError(errorStatus, errorMsg);
	return commVec;
}


std::vector<Label*> DataBase::getLabelByCond(std::string cond) {
	char* errorMsg;
	std::string gu = "\"";
	std::string query = "SELECT LID, COUNT(LID) FROM LabelContainer WHERE("+cond+") GROUP BY LID";
	std::string lid;
	std::vector<Label*> labelVec;
	std::vector<Label*> * labelVecPtr = &labelVec;
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), getLabelCallback, labelVecPtr, &errorMsg);
	checkError(errorStatus, errorMsg);
	for (int i = 0; i<labelVec.size(); ++i) {
		lid = std::to_string(labelVec[i]->getLid()) + ")";
		query = "SELECT Etiquette FROM Labels WHERE(LID = " +lid;
		errorStatus = sqlite3_exec(_dataBase, query.c_str(), getEtiqCallback, labelVec[i], &errorMsg);
		checkError(errorStatus, errorMsg);
	} 
	return labelVec;
}



int DataBase::getLabelCallback(void* labVecPtr, int argc, char** argv, char** azColName) {
	std::vector<Label*> * vecPtr = (std::vector<Label*>*) labVecPtr;
	vecPtr->push_back(new Label(atoi(argv[0]), atoi(argv[1])));
	return 0;
}



int DataBase::getEtiqCallback(void* labPtr, int argc, char** argv, char** azColName){
	Label* label = (Label*) labPtr;
	label->setEtiquette(argv[0]);
	return 0;
}



int DataBase::getCommCallback(void* commVecPtr, int argc, char** argv, char** azColName) {
	std::vector<Commentaire*> * vectorPtr = (std::vector<Commentaire*>*) commVecPtr;
	vectorPtr->push_back(new Commentaire(argv[0], argv[1], argv[2], atoi(argv[3]), atoi(argv[4])));
	return 0;
}



std::vector<Etablissement*> DataBase::getEtabByCond(std::string condition) {
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
		eid = std::to_string(etabVector[i]->getEid()) + ")";
		barPtr = dynamic_cast<Bar*>(etabVector[i]);
		restoPtr = dynamic_cast<Restaurant*>(etabVector[i]);
		hotelPtr = dynamic_cast<Hotel*>(etabVector[i]);
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
		query = "SELECT AVG(Score) FROM Commentaires WHERE(EidConcerne = "+eid;
		errorStatus = sqlite3_exec(_dataBase, query.c_str(), getNoteCallback, etabVector[i], &errorMsg);
		checkError(errorStatus, errorMsg);
	}
	std::cout<<"end"<<std::endl;
	return etabVector;
}



int DataBase::getEtabCallback(void* etabVectorPtr, int argc, char** argv, char** azColName) {
   	std::vector<Etablissement*> * vectorPtr = (std::vector<Etablissement*>*) etabVectorPtr;
   	if (std::string(argv[0]) == "R") {
   		vectorPtr->push_back(new Restaurant(-1, false, false, "", -1));
   	}
   	else if (std::string(argv[0]) == "H") {
   		vectorPtr->push_back(new Hotel(-1, -1, -1));
	}
   	else if (std::string(argv[0]) == "B") {
   		vectorPtr->push_back(new Bar(false, false));
   	}
   	vectorPtr->at(vectorPtr->size()-1)->setEid(atoi(argv[1]));
   	vectorPtr->at(vectorPtr->size()-1)->setNom(argv[2]);
   	vectorPtr->at(vectorPtr->size()-1)->setAdresse(argv[3]);
   	vectorPtr->at(vectorPtr->size()-1)->setLocalite(atoi(argv[4]));
   	vectorPtr->at(vectorPtr->size()-1)->setNumTel(argv[5]);
   	vectorPtr->at(vectorPtr->size()-1)->setSiteWeb(argv[6]);
   	vectorPtr->at(vectorPtr->size()-1)->setAdmin(argv[7]);
   	vectorPtr->at(vectorPtr->size()-1)->setDate(argv[8]);
   	vectorPtr->at(vectorPtr->size()-1)->setCoords(atof(argv[9]), atof(argv[10]));
   	return 0;	
}



int DataBase::getNoteCallback(void* notePtr, int argc, char** argv, char** azColName) {
	Etablissement* note = (Etablissement*) notePtr;
	note->setNote(atof(argv[0] ? argv[0] : "-1.0"));
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
    User* tempUser = (User*) userPtr; 	
    tempUser->setName(argv[0] ? argv[0] : "NULL");
    tempUser->setEmail(argv[1] ? argv[1] : "NULL");
    tempUser->setPassword(argv[2] ? argv[2] : "NULL");
    tempUser->setCreationDate(atoi(argv[3] ? argv[3] : "-1"));
    return 0;	
}



void DataBase::updateData(std::string table, std::string key, std::string newValue, std::string cond) {
	char* errorMsg;
	std::string gu = "\"";
	std::string query = "UPDATE "+table+" SET "+key+" = "+gu+newValue+gu+" WHERE("+cond+")";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), NULL, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



void DataBase::checkError(int errorStatus, char* errorMsg) {
    if (errorStatus) {
        fprintf(stderr, "Error on database: %s\n", errorMsg);
	}
    else {
        fprintf(stdout, "Operation succeed\n");
    }
}



void DataBase::requeteR1() {
	char* errorMsg;
	std::string query = "SELECT Auteur FROM (SELECT Auteur, COUNT(Auteur) AS CNT FROM ("\
	"SELECT Auteur,Score FROM Commentaires WHERE(EidConcerne IN ("\
	"SELECT EidConcerne FROM Commentaires WHERE(Auteur = 'Brenda' AND Score >=4)) AND Score >=4)) GROUP BY Auteur HAVING CNT >= 3)";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), printCallback, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}


void DataBase::requeteR2() {
	char* errorMsg;
	std::string sd = "SELECT EidConcerne FROM Commentaires WHERE(Auteur IN (SELECT Auteur, COUNT(Auteur) AS CNT FROM ("\
	"SELECT Auteur,Score FROM Commentaires WHERE(EidConcerne IN ("\
	"SELECT EidConcerne FROM Commentaires WHERE(Auteur = 'Brenda' AND Score >=4)) AND Score >=4)) GROUP BY Auteur HAVING COUNT(SELECT EidConcerne WHERE(Auteur = 'Brenda' AND Score>=4)) = CNT)";
	int errorStatus = sqlite3_exec(_dataBase, sd.c_str(), printCallback, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}

// void DataBase::requeteR3(){}
// 	 SELECT EidConcerne,COUNT(EidConcerne) AS CNT FROM Commentaires GROUP BY EidConcerne HAVING CNT<=1


void DataBase::requeteR4() {
	char* errorMsg;
	std::string query = "SELECT * FROM Utilisateurs WHERE NameId in (SELECT DISTINCT Etablissements.AdminCreateur FROM Etablissements WHERE NOT EXISTS "\
	"(SELECT Commentaires.Auteur FROM Commentaires WHERE (Etablissements.Nom = Etablissements.AdminCreateur AND Etablissements.AdminCreateur  = Commentaires.Auteur)))";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), printCallback, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}


void DataBase::requeteR5() {
	char* errorMsg;
	std::string query = "SELECT DISTINCT E.Nom , E.Adresse, E.Localite, E.NumTel, E.AdminCreateur,"\
	"E.DateCreation, E.SiteWeb,  E.Latitude, E.Longitude, E.Type"\
	"FROM Etablissements AS E , (SELECT EidConcerne , COUNT(EidConcerne) AS CNT , AVG(Score) AS average FROM "\
	"Commentaires GROUP BY EidConcerne HAVING CNT >= 3 ORDER BY average ) AS C WHERE(E.Nom = C.EidConcerne) ORDER BY C.average";
	int errorStatus = sqlite3_exec(_dataBase, query.c_str(), printCallback, 0, &errorMsg);
	checkError(errorStatus, errorMsg);
}



int DataBase::printCallback(void* notUsed, int argc, char** argv, char** azColName) {
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n"); 
    return 0;
}



DataBase::~DataBase() {
	sqlite3_close(_dataBase);
}