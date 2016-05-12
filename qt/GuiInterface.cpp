#include "GuiInterface.hpp"



GuiInterface::GuiInterface(DataBase* database, int argc, char** argv) : QApplication(argc, argv) {
	_dataBase = database;
	QRect rec(desktop()->screenGeometry());
	_width = rec.width();
	_height = rec.height();
	_mainWindow = new QMainWindow();
	setApplicationName("RestHoBar");
	setWindowIcon(QIcon("../qt/Images/test.png"));
	_mainWindow->setStyleSheet("background : transparent");
	_taskBar = new TaskBar(_width, _height, _mainWindow);
	_searchWidget = new SearchWidget(_width, _height, _mainWindow);
	_homeWindow = new HomeWindow(_width, _height, _searchWidget->height(), _searchWidget->width(), _mainWindow);
	_currentWindow = _homeWindow;
	_searchWidget->raise();
	_searchWidget->show();
	_taskBar->raise();
	_taskBar->show();
	connectWidgets();
	_mainWindow->resize(_width, _height);
	_mainWindow->show();
	exec();
}



void GuiInterface::searchSigSlot(std::string askedSearch) {
	if (_searchPage == nullptr) {
		delete _currentWindow;
		_searchPage = new PageRecherche(_dataBase, askedSearch, _height, _width, _mainWindow);
		_searchWidget->move(_width/15+2*_width/13+ _width/70,_height/6-_searchWidget->height()-_height/200);
		_currentWindow = _searchPage;
		_currentWindow->raise();
		_currentWindow->show();
	}
	else {
		_searchPage->makeSearchTableSlot(askedSearch);
	}
	_searchWidget->raise();
}



void GuiInterface::connectWidgets() {
	connect(_searchWidget, SIGNAL(searchSig(std::string)), this,SLOT(searchSigSlot(std::string)));
}
