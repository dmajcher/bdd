#include "TableRecherche.hpp"

void TableRecherche::initTable(){
	this->horizontalHeader()->hide();
	this->verticalHeader()->hide();
	this->setStyleSheet("QTableWidget{background: transparent;border-radius: 5px;}");
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->verticalHeader()->setDefaultSectionSize(this->height()*4+this->height()/3);
	this->setShowGrid(false);
	this->setFrameStyle(QFrame::NoFrame);
	this->setFont(QFont("URW Gothic L", 13));
}

void TableRecherche::buildTable(){
	std::cout<<_etabs.size()<<std::endl;
	for (int i = 0;i<_etabs.size();++i){
		std::cout<<"cell "<<i<<std::endl;
		_currentTableItems.push_back(new CelluleRecherche(_etabs[i],this->horizontalHeader()->defaultSectionSize(),this->verticalHeader()->defaultSectionSize(),this));
		setCellWidget(i,0,_currentTableItems[i]);
	}
}                                           

void TableRecherche::connectCells(){
	connect(this,SIGNAL(cellPressed(int,int)),this,SLOT(goToEtabProfileSlot(int,int)));
}

void TableRecherche::goToEtabProfileSlot(int row,int column){
	emit visitEtabSig(dynamic_cast<CelluleRecherche*>(_currentTableItems[row])->getEid());
}

TableRecherche::TableRecherche(std::vector<Etablissement*> etabs,QWidget* parent): QTableWidget(etabs.size(),1,parent){
	_etabs = etabs;
	initTable();
	buildTable();
	connectCells();
	this->raise();
	this->show();
}

TableRecherche::~TableRecherche(){
	for (int i = 0;i<_currentTableItems.size();++i){
		delete _currentTableItems[i];
	}
	std::cout<<"destrpassed"<<std::endl;
}