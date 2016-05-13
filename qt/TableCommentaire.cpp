#include "TableCommentaire.hpp"

void TableCommentaire::initTable(){
	this->horizontalHeader()->hide();
	this->verticalHeader()->hide();
	this->setStyleSheet("QTableWidget{background: transparent;border-radius: 5px;}");
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	this->verticalHeader()->setDefaultSectionSize(this->height()*4+this->height()/3);
	this->setShowGrid(false);
	this->setFrameStyle(QFrame::NoFrame);
	this->setFont(QFont("URW Gothic L", 13));
}

void TableCommentaire::buildTable(){
	std::cout<<_comments.size()<<std::endl;
	for (int i = 0;i<_comments.size();++i){
		std::cout<<"cell "<<i<<std::endl;
		_currentTableItems.push_back(new CelluleCommentaire(_comments[i],this->horizontalHeader()->defaultSectionSize(),this->verticalHeader()->defaultSectionSize(),this));
		setCellWidget(i,0,_currentTableItems[i]);
	}
}                                           

void TableCommentaire::connectCells(){
	connect(this,SIGNAL(cellPressed(int,int)),this,SLOT(goToEtabProfileSlot(int,int)));
}

// void TableCommentaire::goToEtabProfileSlot(int row,int column){
// 	emit visitEtabSig(dynamic_cast<CelluleCommentaire*>(_currentTableItems[row])->getEid());
// }

TableCommentaire::TableCommentaire(std::vector<Commentaire*> comments,QWidget* parent): QTableWidget(comments.size(),1,parent){
	_comments = comments;
	initTable();
	buildTable();
	connectCells();
	this->raise();
	this->show();
}

TableCommentaire::~TableCommentaire(){
	for (int i = 0;i<_currentTableItems.size();++i){
		delete _currentTableItems[i];
	}
	std::cout<<"destrpassed"<<std::endl;
}