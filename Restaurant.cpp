#include "Restaurant.hpp"

int Restaurant::getRid(){return _RID;}
int Restaurant::getNbPlaces(){return _nbDePlaceBanquet;}
int Restaurant::getDemiJours(){return _nbDemiJourDeConge;}
float Restaurant::getPrix(){return _prixPlats;}
std::string Restaurant::getHoraire(){return _horraireDeFermeture;}
bool Restaurant::hasTakeAway(){return _takeAway;}
bool Restaurant::hasLivraison(){return _livraison;}