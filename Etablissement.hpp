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
	std::string getSiteWeb();
	std::string getAdmin();
	std::string getDateCreation();
	float getLatitude();
	float getLongitude();
	void setEid(int);
	void setEtabInfos(std::string, std::string, int, std::string, std::string, int, int, float, float);
	void setNom(std::string);
	void setAdresse(std::string);
	void setNumTel(std::string);
	void setAdmin(std::string);
	void setLocalite(int);
	void setSiteWeb(std::string);
	void setCoords(float, float);
	void setDate(std::string);
	virtual void setTakeAway(bool);
	virtual void setLivraison(bool);
	virtual void setPrix(float);
	virtual void setNbPlaces(int);
	virtual void setHorraire(std::string);
	virtual void setFumeur(bool);
    virtual void setPetiteResto(bool);

};

#endif /* ETABLISSEMENT_HPP */