#include "Restaurant.hpp"

int Restaurant::getRid(){return _RID;}
int Restaurant::getNbDePlaceBanquet(){return _nbDePlaceBanquet;}
int Restaurant::getNbDemiJourDeConge(){return _nbDemiJourDeConge;}
std::vector<int> Restaurant::getPrixPlats(){return _prixPlats;}
std::string Restaurant::getHorraireDeFermeture(){return _horraireDeFermeture;}
bool Restaurant::hasTakeAway(){return _takeAway;}
bool Restaurant::hasLivraison(){return _livraison;}