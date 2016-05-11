#include "TableRecherche.hpp"

void TableRecherche::initTable(){
	this->horizontalHeader()->hide();
	this->verticalHeader()->hide();
	this->setStyleSheet("QTableWidget{background: transparent;};");
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->verticalHeader()->setDefaultSectionSize(this->height()*4+this->height()/3);
	this->setShowGrid(false);
	this->setFrameStyle(QFrame::NoFrame);
}

void TableRecherche::buildTable(){
	for (int i = 0;i<_etabs.size();++i){
		_currentTableItems.push_back(new CelluleRecherche(_etabs[i],this->horizontalHeader()->defaultSectionSize(),this->verticalHeader()->defaultSectionSize(),this));
		setCellWidget(i,0,_currentTableItems[i]);
	}
}                                           

void TableRecherche::connectCells(){
	connect(this,SIGNAL(cellPressed(int,int)),this,SLOT(goToEtabProfileSlot(int,int)));
}

void TableRecherche::goToEtabProfileSlot(int row,int column){
	emit changeUserSig(dynamic_cast<CelluleRecherche*>(_currentTableItems[row])->getEid());
}

TableRecherche::TableRecherche(std::vector<Etablissement*> etabs,QWidget* parent): QTableWidget(etabs.size(),1,parent){
	initTable();
	connectCells();
	_etabs = etabs;
	this->raise();
	this->show();
}

TableRecherche::~TableRecherche(){
	for (int i = 0;i<_currentTableItems.size();++i){
		delete _currentTableItems[i];
	}
	std::cout<<"destrpassed"<<std::endl;
}