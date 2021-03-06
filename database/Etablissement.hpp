#ifndef ETABLISSEMENT_HPP
#define ETABLISSEMENT_HPP

#include <string>

class Etablissement {
	int _EID;
	std::string _nom;
	std::string _adresse;
	std::string _numTel;
	int _localite;
	float _note;
	std::string _siteWeb;
	std::string _adminCreateur;
	std::string _dateDeCreation;
	float _latitude;
	float _longitude;

public:
	int getEid();
	std::string getNom();
	std::string getAdresse();
	std::string getNumTel();
	int getLocalite();
	float getNote();
	std::string getSiteWeb();
	std::string getAdmin();
	std::string getDateCreation();
	float getLatitude();
	float getLongitude();
	void setEid(int);
	void setEtabInfos(std::string, std::string, int, std::string, std::string, std::string, std::string, float, float);
	void setNom(std::string);
	void setAdresse(std::string);
	void setNumTel(std::string);
	void setAdmin(std::string);
	void setNote(float);
	void setLocalite(int);
	void setSiteWeb(std::string);
	void setCoords(float, float);
	void setDate(std::string);
	virtual ~Etablissement();

};

#endif /* ETABLISSEMENT_HPP */