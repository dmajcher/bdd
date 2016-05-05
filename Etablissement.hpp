#ifndef ETABLISSEMENT_HPP
#define ETABLISSEMENT_HPP

#include <string>

class Etablissement{
	int _EID;
	std::string _nom;
	std::string _adresse;
	std::string _numTel;
	int _localite;
	std::string _siteWeb;
	std::string _adminCreateur;
	int _dateDeCreation;
	float _latitude;
	float _longitude;

public:
	int getEid();
	std::string getNom();
	std::string getAdresse();
	std::string getNumTel();
	int getLocalite();
	std::string getSiteWeb();
	std::string getAdmin();
	int getDateCreation();
	float getLatitude();
	float getLongitude();
	void setNom(std::string);
	void setAdresse(std::string);
	void setNumTel(std::string);
	void setLocalite(int);
	void setSiteWeb(std::string);
	void setCoords(float, float);
};

#endif /* ETABLISSEMENT_HPP */