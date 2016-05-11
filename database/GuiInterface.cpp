#include "GuiInterface.hpp"



GuiInterface::GuiInterface(int argc, char** argv) : QApplication(argc, argv) {
	_mainWindow = new QMainWindow();
	_mainWindow->setStyleSheet("background : transparent");
	QRect rec(desktop()->screenGeometry());
	_width = rec.width();
	_height = rec.height();
	SearchWidget* sw = new SearchWidget(_width, _height, _mainWindow);
	sw->raise();
	sw->show();
	// _homeWindow = new HomeWindow(_width, _height, _mainWindow);
}
