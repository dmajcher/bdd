#include "PageRecherche.hpp"

PageRecherche::PageRecherche(DataBase* db,std::string request,int height,int width, QWidget*parent,SearchWidget* searchEntry){
	std::cout<<"yooop"<<std::endl;
	_height = height;
	_width = width;
	_db = db;
	_searchEntry = searchEntry;
	this->setParent(parent);
	this->show();
	this->raise();
	initPage();
	//makeLabelTableSlot();
	makeSearchTableSlot(request);
	connectEntry();
}

void PageRecherche::initPage(){
	_searchEntry->setGeometry(QRect(_width/15+2*_width/13+ _width/70,_height/4-_searchEntry->height()-_height/200,_searchEntry->width(),_searchEntry->height()));
}

void PageRecherche::connectEntry(){
	connect(_searchEntry,SIGNAL(searchSig(std::string)),this,SLOT(makeSearchTableSlot(std::string)));
}

void PageRecherche::makeSearchTableSlot(std::string request){

	_searchTable = nullptr;
	delete _searchTable; 
	_searchTable = new TableRecherche(_db->getEtabByCond(request),this);
    _searchTable->setGeometry(QRect(_width/15+2*_width/13+ _width/70,_height/4,_width-_width/3,_height/2 +_height/5));
    _searchTable->raise();
    _searchTable->show();
}

PageRecherche::~PageRecherche(){
	delete _searchTable;
	delete _searchEntry;
}