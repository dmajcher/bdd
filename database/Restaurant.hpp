#ifndef RESTAURANT_HPP
#define RESTAURANT_HPP

#include "Etablissement.hpp"
#include <vector>
#include <string>

class Restaurant: public Etablissement {
	int _nbDePlaceBanquet;
	int  _prixPlats;
	std::string _horaireDeFermeture;
	bool _takeAway;
	bool _livraison;

public:
	Restaurant(int, bool, bool, std::string, int);
	int getNbPlaces();
	int getPrix();
	std::string getHoraire();
	bool hasTakeAway();
	bool hasLivraison();
	void setTakeAway(bool);
	void setLivraison(bool);
	void setPrix(float);
	void setNbPlaces(int);
	void setHoraire(std::string);
	//~Restaurant();
};

#endif /* RESTAURANT_HPP */