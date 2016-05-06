#include "Etablissement.hpp"
#include <vector>
#include <string>

class Restaurant: public Etablissement {
	int _RID;
	int _nbDePlaceBanquet;
	int _nbDemiJourDeConge;
	std::vector<int> _prixPlats;
	std::string _horraireDeFermeture;
	bool _takeAway;
	bool _livraison;

public:
	int getRid();
	int getNbDePlaceBanquet();
	int getNbDemiJourDeConge();
	std::vector<int> getPrixPlats();
	std::string getHorraireDeFermeture();
	bool hasTakeAway();
	bool hasLivraison();
};