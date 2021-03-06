#include "Restaurant.hpp"


Restaurant::Restaurant(int prixPlats, bool takeAway, bool livraison, std::string horaire, int nbPlaces) {
    _nbDePlaceBanquet = nbPlaces;
    _prixPlats = prixPlats;
    _horaireDeFermeture = horaire;
    _takeAway = takeAway;
    _livraison = livraison;
}

int Restaurant::getNbPlaces(){return _nbDePlaceBanquet;}

int Restaurant::getPrix(){return _prixPlats;}

std::string Restaurant::getHoraire(){return _horaireDeFermeture;}

bool Restaurant::hasTakeAway(){return _takeAway;}

bool Restaurant::hasLivraison(){return _livraison;}

void Restaurant::setTakeAway(bool takeAway){_takeAway = takeAway;}

void Restaurant::setLivraison(bool livraison){_livraison = livraison;}

void Restaurant::setPrix(float prix){_prixPlats = prix;}

void Restaurant::setNbPlaces(int nbPlaces){_nbDePlaceBanquet = nbPlaces;}

void Restaurant::setHoraire(std::string horaire) {_horaireDeFermeture = horaire;}