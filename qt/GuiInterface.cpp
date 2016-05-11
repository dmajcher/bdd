#include "GuiInterface.hpp"



GuiInterface::GuiInterface(DataBase* database, int argc, char** argv) : QApplication(argc, argv) {
	_dataBase = database;
	_mainWindow = new QMainWindow();
	_mainWindow->setStyleSheet("background : url(Images/wood.jpg)");
	QRect rec(desktop()->screenGeometry());
	_width = rec.width();
	_height = rec.height();
	_searchWidget = new SearchWidget(_width, _height, _mainWindow);
	QWidget* w = new QWidget(_mainWindow);
	QWidget* t = new QWidget(_mainWindow);

	w->setGeometry(0, _height/5.5, _width, _height/1.75);
	w->setStyleSheet("background : url(Images/horeca.jpg)");
	int wi = sw->size().width();
	int h = sw->size().height(); 
	int x = sw->geometry().x();
	t->setGeometry(_width/9, h/2000, wi/2, h*1.7);
	t->setStyleSheet("QWidget{background: url(Images/test.png) center center}");
	// _searchWidget->move(x,(_height/2-h));

	// _mainWindow->resize(_width, _height);
	_mainWindow->showMaximized();
	// w->raise();
	 t->raise();
	 t->show();
	// w->show();
	_searchWidget->raise();
	_searchWidget->show();
	exec();
	// _homeWindow = new HomeWindow(_width, _height, _mainWindow);
}

void GuiInterface::searchSigSlot(std::string askedSearch) {
	if (_searchPage == nullptr) {
		_searchPage = new PageRecherche(_dataBase, askedSearch, _width, _height, _mainWindow);
	}
}

