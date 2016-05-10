#include "../DataBase.hpp"
#include "GuiInterface.hpp"


int main(int argc, char** argv) {
	DataBase database("database.db");
	GuiInterface* gui = new GuiInterface(argc, argv);
	return 0;
	
}
