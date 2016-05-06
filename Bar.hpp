#ifndef BAR_HPP
#define BAR_HPP
#include "Etablissement.hpp"

class Bar: public Etablissement{
	int _BID;
	bool _fumeur;
	bool _petiteRestaur;
public:
    Bar(bool, bool);
	int getBid();
	bool isFumeur();
	bool hasPetiteResto();
    bool setFumeur(bool);
    bool setPetiteResto(bool);
};
#endif /* BAR_HPP */