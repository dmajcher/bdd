#include "../database/DataBase.hpp"
#include "GuiInterface.hpp"


int main(int argc, char** argv) {
	DataBase database("../database.db");
	GuiInterface* gui = new GuiInterface(&database, argc, argv);
	return 0;
}
