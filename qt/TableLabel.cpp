#include "TableLabel.hpp"

void TableLabel::initTable(){
	this->horizontalHeader()->hide();
	this->verticalHeader()->hide();
	this->setStyleSheet("QTableWidget{background: transparent;border-radius: 5px;}");
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->verticalHeader()->setDefaultSectionSize(this->height()+this->height()/3);
	this->setShowGrid(false);
	this->setFrameStyle(QFrame::NoFrame);
}

void TableLabel::buildTable(){
	std::cout<<_labels.size()<<std::endl;
	for (int i = 0;i<_labels.size();++i){
		std::cout<<"cell "<<i<<std::endl;
		_currentTableItems.push_back(new CelluleLabel(_labels[i],this->horizontalHeader()->defaultSectionSize(),this->verticalHeader()->defaultSectionSize(),this));
		setCellWidget(i,0,_currentTableItems[i]);
	}
}                                           

void TableLabel::connectCells(){
	connect(this,SIGNAL(cellPressed(int,int)),this,SLOT(goToEtabProfileSlot(int,int)));
}

// void TableLabel::goToEtabProfileSlot(int row,int column){
// 	emit visitEtabSig(dynamic_cast<CelluleCommentaire*>(_currentTableItems[row])->getEid());
// }

TableLabel::TableLabel(std::vector<Label*> labels,QWidget* parent): QTableWidget(labels.size(),1,parent){
	_labels = labels;
	initTable();
	buildTable();
	connectCells();
	this->raise();
	this->show();
}

TableLabel::~TableLabel(){
	for (int i = 0;i<_currentTableItems.size();++i){
		delete _currentTableItems[i];
	}
	std::cout<<"destrpassed"<<std::endl;
}