#include <string>
#include "Etablissement.hpp"


class Restaurant: public Etablissement {
	private:
		int _RID;
		int _demiJours;
		int _NbPlacesBanquet;
		float _prixPlats;
		bool _takeAway;
		std::string _horaireFermeture;

	public:
		int getRid();
		float getPrix();
		bool getTakeAway();
		int getDemiJours();
		int getNbPlaces();
		std::string getHoraire();
};