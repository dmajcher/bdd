#include "Hotel.hpp"


Hotel::Hotel(int nbEtoiles, int nbChambres, int indicePrix) {
    _nbEtoiles = nbEtoiles;
    _nbChambres = nbChambres;
    _indicePrix = indicePrix;
}


int Hotel::getHid(){return _HID;}

int Hotel::getEtoiles(){return _nbEtoiles;}

int Hotel::getChambres(){return _nbChambres;}

int Hotel::getIndicePrix(){return _indicePrix;}

void Hotel::setEtoiles(int nbEtoiles) {
    _nbEtoiles = nbEtoiles;
}

void Hotel::setChambres(int nbChambres) {
    _nbChambres = nbChambres;
}

void Hotel::setIndicePrix(int indicePrix) {
    _indicePrix = indicePrix;
}