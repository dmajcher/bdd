#include "Etablissement.hpp"

class Bar: public Etablissement{
	int _BID;
	bool _fumeur;
	bool _petiteRestaur;
public:
	int getBid();
	bool isFumeur();
	bool hasPetiteRestaur();
};