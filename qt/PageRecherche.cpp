#include "PageRecherche.hpp"

PageRecherche::PageRecherche(DataBase* db,std::string request,int height,int width, QWidget* parent) : QWidget(parent){
	std::cout<<"yooop"<<std::endl;
	_height = height;
	_width = width;
	_parent = parent;
	_db = db;
	parent->setStyleSheet("background:url(../qt/Images/wood.jpg)");
	// _searchEntry = searchEntry;
	// initPage();
	//makeLabelTableSlot();
	setStyle();
	makeSearchTableSlot(request);
	connectEtabVisit();
	// connectEntry();
	// raise();
	// show();
}


void PageRecherche::setStyle() {
	this->resize(_width, _height);
	this->setStyleSheet("QWidget{background :transparent;}");
	this->raise();
	this->show();
}


void PageRecherche::initPage(){
	_searchEntry->move(_width/15+2*_width/13+ _width/70,_height/6-_searchEntry->height()-_height/200);
}

void PageRecherche::connectEntry(){
	connect(_searchEntry,SIGNAL(searchSig(std::string)),this,SLOT(makeSearchTableSlot(std::string)));
}
void PageRecherche::connectEtabVisit(){
	connect(_searchTable,SIGNAL(visitEtabSig(unsigned)),this,SLOT(makeEtabProfileSlot(unsigned)));
}
void PageRecherche::makeEtabProfileSlot(unsigned eid){
	std::cout<<eid<<std::endl;
	emit profileSig(eid);
}

void PageRecherche::makeSearchTableSlot(std::string request){
	delete _searchTable; 
	_searchTable = new TableRecherche(_db->getEtabByCond(request),this);
	std::cout<<"setgeo"<<std::endl;
    _searchTable->setGeometry(_width/15+2*_width/13+ _width/70,_height/6,_width-_width/3,_height/2 +_height/5);
    _searchTable->raise();
    _searchTable->show();
}

PageRecherche::~PageRecherche(){
	delete _searchTable;
}