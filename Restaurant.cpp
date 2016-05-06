#include "Restaurant.hpp"


Restaurant::Restaurant(float prixPlats, bool takeAway, bool livraison, std::string horaire, int demiJours, int nbPlaces) {
    _nbDePlaceBanquet = nbPlaces;
    _nbDemiJourDeConge = demiJours;
    _prixPlats = prixPlats;
    _horraireDeFermeture = horaire;
    _takeAway = takeAway;
    _livraison = livraison;
}



int Restaurant::getRid(){return _RID;}

int Restaurant::getNbPlaces(){return _nbDePlaceBanquet;}

int Restaurant::getDemiJours(){return _nbDemiJourDeConge;}

float Restaurant::getPrix(){return _prixPlats;}

std::string Restaurant::getHoraire(){return _horraireDeFermeture;}

bool Restaurant::hasTakeAway(){return _takeAway;}

bool Restaurant::hasLivraison(){return _livraison;}

void Restaurant::setNbPlaces(int nbPlaces) {
    _nbDePlaceBanquet = nbPlaces;
}

void Restaurant::setDemiJours(int demiJours) {
    _nbDemiJourDeConge = demiJours;
}

void Restaurant::setPrix(float prix) {
    _prixPlats = prix;
}

void Restaurant::setHoraire(std::string horaire) {
    _horraireDeFermeture = horaire;
}

void Restaurant::setTakeAway(bool takeAway) {
    _takeAway = takeAway;
}

void Restaurant::setLivraison(bool livraison) {
    _livraison = livraison;
}