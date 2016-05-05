#include <string>
#include "Etablissement.hpp"


class Bar: public Etablissement {
	private:
		int _BID;
		bool _fumeur;
		bool _petiteResto;

	public:
		int getBid();
		bool getFumeur();
		bool getPetiteResto();

};