#include "GuiInterface.hpp"



GuiInterface::GuiInterface(DataBase* database, int argc, char** argv) : QApplication(argc, argv) {
	_dataBase = database;
	_mainWindow = new QMainWindow();
	_mainWindow->resize(_width, _height);
	_mainWindow->setStyleSheet("background : url(Images/wood.jpg)");
	QRect rec(desktop()->screenGeometry());
	_width = rec.width();
	_height = rec.height();
	_searchWidget = new SearchWidget(_width, _height, _mainWindow);
	QWidget* w = new QWidget(_mainWindow);
	QWidget* t = new QWidget(_mainWindow);

	w->setGeometry(0, _height/5.5, _width, _height/1.75);
	w->setStyleSheet("background : url(Images/horeca.jpg)");
	int wi = _searchWidget->size().width();
	int h = _searchWidget->size().height(); 
	int x = _searchWidget->geometry().x();
	t->setGeometry(_width/9, h/2000, wi/2, h*1.7);
	t->setStyleSheet("QWidget{background: url(Images/test.png) center center}");
	_mainWindow->showMaximized();
	 t->raise();
	 t->show();
	_searchWidget->raise();
	_searchWidget->show();
	connectWidgets();
	exec();
}



void GuiInterface::connectSearch(){
	connect(_searchWidget,SIGNAL(searchSig(std::string)),this,SLOT(searchSigSlot(std::string)));
}



void GuiInterface::searchSigSlot(std::string askedSearch) {
	std::cout<<"tichke"<<std::endl;
	if (_searchPage == nullptr) {
		_searchPage = new PageRecherche(_dataBase, askedSearch, _width, _height, _mainWindow,_searchWidget);
	}
}



void GuiInterface::connectWidgets() {
	connect(_searchWidget, SIGNAL(searchSig(std::string)), this,SLOT(searchSigSlot(std::string)));
}
