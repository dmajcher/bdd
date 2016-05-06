#include "Restaurant.hpp"

int Restaurant::getRid(){return _RID;}
int Restaurant::getNbPlaces(){return _nbDePlaceBanquet;}
int Restaurant::getDemiJours(){return _nbDemiJourDeConge;}
float Restaurant::getPrix(){return _prixPlats;}
std::string Restaurant::getHoraire(){return _horraireDeFermeture;}
bool Restaurant::hasTakeAway(){return _takeAway;}
bool Restaurant::hasLivraison(){return _livraison;}
void Restaurant::setTakeAway(bool takeAway){_takeAway = takeAway;}
void Restaurant::setLivraison(bool livraison){_livraison = livraison;}
void Restaurant::setPrix(float prix){_prixPlats = prix;}
void Restaurant::setNbPlaces(int nbPlaces){_nbDePlaceBanquet = nbPlaces;}
void Restaurant::setHorraire(){}