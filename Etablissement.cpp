#include "Etablissement.hpp"


int Etablissement::getEid(){return _EID;}

std::string Etablissement::getNom(){return _nom;}

std::string Etablissement::getAdresse(){return _adresse;}

std::string Etablissement::getNumTel(){return _numTel;}

int Etablissement::getLocalite(){return _localite;} 

std::string Etablissement::getSiteWeb(){return _siteWeb;}

std::string Etablissement::getAdmin(){return _adminCreateur;}

std::string Etablissement::getDateCreation(){return _dateDeCreation;}

float Etablissement::getLatitude(){return _latitude;}

float Etablissement::getLongitude(){return _longitude;}

void Etablissement::setEtabInfos(std::string nom, std::string adresse, int localite, std::string numTel, std::string siteWeb, int admin, int date, float latitude, float longitude) {
    _nom = nom;
    _adresse = adresse;
    _localite = localite;
    _numTel = numTel;
    _siteWeb = siteWeb;
    _adminCreateur = admin;
    _dateDeCreation = date;
    _latitude = latitude;
    _longitude = longitude;
}

void Etablissement::setEid(int eid){
    _EID = eid;
}

void Etablissement::setNom(std::string name) {
	_nom = name;
}

void Etablissement::setAdresse(std::string addr) {
	_adresse = addr;
}

void Etablissement::setNumTel(std::string numTel) {
	_numTel = numTel;
}

void Etablissement::setLocalite(int localite) {
	_localite = localite;
}

void Etablissement::setSiteWeb(std::string site) {
	_siteWeb = site;
}
void Etablissement::setAdmin(std::string admin){
	_adminCreateur = admin;
}

void Etablissement::setCoords(float latitude, float longitude) {
	_latitude = latitude;
	_longitude = longitude;
}

void Etablissement::setDate(std::string date){_dateDeCreation = date;}

Etablissement::~Etablissement() {}