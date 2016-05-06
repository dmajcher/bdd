#ifndef HOTEL_HPP
#define HOTEL_HPP
#include "Etablissement.hpp"

class Hotel: public Etablissement{
	int _HID;
	int _nbEtoiles;
	int _nbChambres;
	int _indicePrix;
public:
	int getHid();
	int getNbEtoiles();
	int getNbChambres();
	int getIndicePrix();
};

#endif /* HOTEL_HPP */