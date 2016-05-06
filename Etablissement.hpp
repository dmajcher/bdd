#ifndef ETABLISSEMENT_HPP
#define ETABLISSEMENT_HPP

#include <string>

class Etablissement {
	int _EID;
	std::string _nom;
	std::string _adresse;
	std::string _numTel;
	int _localite;
	std::string _siteWeb;
	int _adminCreateur;
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
	int getAdmin();
	int getDateCreation();
	float getLatitude();
	float getLongitude();
	void setEid(int);
	void setEtabInfos(std::string, std::string, int, std::string, std::string, int, int, float, float);
	void setNom(std::string);
	void setAdresse(std::string);
	void setNumTel(std::string);
	void setLocalite(int);
	void setSiteWeb(std::string);
	void setCoords(float, float);
};

#endif /* ETABLISSEMENT_HPP */