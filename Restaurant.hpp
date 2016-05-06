#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

#include "Etablissement.hpp"
#include <vector>
#include <string>

class Restaurant: public Etablissement {
	int _RID;
	int _nbDePlaceBanquet;
	int _nbDemiJourDeConge;
	float  _prixPlats;
	std::string _horraireDeFermeture;
	bool _takeAway;
	bool _livraison;

public:
	Restaurant(float, bool, bool, std::string, int, int);
	int getRid();
	int getNbPlaces();
	int getDemiJours();
	float getPrix();
	std::string getHoraire();
	bool hasTakeAway();
	bool hasLivraison();
	void setNbPlaces(int);
	void setDemiJours(int);
	void setPrix(float);
	void setHoraire(std::string);
	void setTakeAway(bool);
	void setLivraison(bool);
};

#endif /* RESTAURANT_HPP */