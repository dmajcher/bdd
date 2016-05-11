#include "GuiInterface.hpp"



GuiInterface::GuiInterface(int argc, char** argv) : QApplication(argc, argv) {
	_mainWindow = new QMainWindow();
	_mainWindow->setStyleSheet("background : url(Images/bois.jpg)");
	QRect rec(desktop()->screenGeometry());
	_width = rec.width();
	_height = rec.height();
	SearchWidget* sw = new SearchWidget(_width, _height, _mainWindow);
	QWidget* w = new QWidget(_mainWindow);
	QWidget* t = new QWidget(_mainWindow);

	w->setGeometry(0, _height/5.5, _width, _height/1.75);
	w->setStyleSheet("background : url(Images/horeca.jpg)");

	int wi = sw->size().width();
	int h = sw->size().height(); 
	int x = sw->geometry().x();
	t->setGeometry(_width/2-(h*1.5)/2, h, h*1.5, h*1.5);
	t->setStyleSheet("image: url(Images/logo.jpeg) center center");
	sw->move(x,(_height/2-h));
	// _mainWindow->resize(_width, _height);
	_mainWindow->showMaximized();
	w->raise();
	t->raise();
	t->show();
	w->show();
	sw->raise();
	sw->show();
	exec();
	// _homeWindow = new HomeWindow(_width, _height, _mainWindow);
}
