#ifndef ETABLISSEMENT_HPP
#define ETABLISSEMENT_HPP

#include <string>

class Etablissement{
	int _EID;
	std::string _nom;
	std::string _adresse;
	int _numTel;
	std::string _siteWeb;
	std::string _adminCreateur;
	int _dateDeCreation;
	float _latitude;
	float _longitude;
public:
	int getEid();
	std::string getNom();
	std::string getAdresse();
	int getNumTel();
	std::string getSiteWeb();
	std::string getAdmin();
	int getDateCreation();
	float getLatitude();
	float getLongitude();
};

#endif /* ETABLISSEMENT_HPP */