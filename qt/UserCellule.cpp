#include "UserCellule.hpp"

void UserCellule::initItem(int width, int height){
	this->setGeometry(QRect(0,0, width, height));
	this->setStyleSheet("QLabel{background: lightgrey;border: 1px solid;}");
	std::cout<<"hllll"<<std::endl;
	
	int etab = _comment->getEidConcerne();
	_etab = new QLabel(QString(std::to_string(etab).c_str()));
	_etab->setGeometry(QRect(width,height/8, width*5, height/5));
	_etab->setStyleSheet("QLabel{font: 14pt; background: transparent;border :0px solid #f2be03 !important;};");
	_etab->raise();
	_etab->show();
	_etab->setFont(QFont("URW Gothic L", 10));
	
	_text = new QTextEdit(this);
	_text->setReadOnly(true);
	_text->setGeometry(QRect(width,height/3+height/8, width*9, height/2));
	_text->setStyleSheet("QTextEdit{background: transparent;border :0px };");
	_text->append(const_cast<char*>(_comment->getTexte().c_str()));
	_text->raise();
	_text->show();
	_text->setFont(QFont("URW Gothic L", 10));

	_date = new QLabel(const_cast<char*>(_comment->getDate().c_str()),this);
	_date->setGeometry(QRect(width*7,height/8,width*3, height/5));
	_date->setStyleSheet("QLabel{background: transparent;border :0px };");
	_date->raise();
	_date->show();
	_date->setFont(QFont("URW Gothic L", 10));

	int  score = _comment->getScore();
	std::string label5 = "Note: "+std::to_string(score);
	_note = new QLabel(this);
	_note->setGeometry(QRect(width*12,height/2+height/4,width*5, height/5));
	_note->setStyleSheet("QLabel{background: transparent;border :0px };");
	_note->setText(QString(label5.c_str()));
	_note->raise();
	_note->show();
	_note->setFont(QFont("URW Gothic L", 10));
	this->raise();
	this->show();
}

// unsigned int UserCellule::getEid(){
// 	return _etab->getEid();
// }

UserCellule::UserCellule(Commentaire* comment,int width,int height,QWidget* parent): QLabel(parent){
	std::cout<<"cell constr"<<std::endl;
	_comment = comment;
	initItem(width,height);
}

UserCellule::~UserCellule(){
	//delete _pictureFrame;
	delete _etab;
	delete _text;
	delete _date;
	delete _note;
}