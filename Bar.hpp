#ifndef BAR_HPP
#define BAR_HPP
#include "Etablissement.hpp"

class Bar: public Etablissement{
	bool _fumeur;
	bool _petiteRestaur;
public:
    Bar(bool, bool);
	bool isFumeur();
	bool hasPetiteResto();
    void setFumeur(bool);
    void setPetiteResto(bool);
};

#endif /* BAR_HPP */