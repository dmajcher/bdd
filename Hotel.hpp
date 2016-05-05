#include <string>
#include "Etablissement.hpp"


class Hotel: public Etablissement {
	private:
		int _HID;
		int _nbEtoiles;
		int _indicePrix;

	public:
		int getHid();
		int getEtoiles();
		int getIndicePrix();

};