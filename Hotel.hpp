#ifndef HOTEL_HPP
#define HOTEL_HPP
#include "Etablissement.hpp"

class Hotel: public Etablissement{
	int _HID;
	int _nbEtoiles;
	int _nbChambres;
	int _indicePrix;

public:
    Hotel(int, int, int); 
	int getHid();
	int getEtoiles();
	int getChambres();
	int getIndicePrix();
    void setEtoiles(int);
    void setChambres(int);
    void setIndicePrix(int);
};

#endif /* HOTEL_HPP */