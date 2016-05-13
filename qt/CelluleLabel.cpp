#include "CelluleLabel.hpp"

void CelluleLabel::initItem(int width, int height){
	this->setGeometry(QRect(0,0, width, height));
	this->setStyleSheet("QLabel{background: lightgrey;border: 1px solid;}");

	_etiquette = new QTextEdit(this);
	_etiquette->setReadOnly(true);
	_etiquette->setGeometry(QRect(width,height/3+height/8, width*9, height/2));
	int poids = _label->getPoids();
	poids = log(poids)/log(1.1);
	std::string font= std::to_string(poids);
	std::string styleSheet = "QTextEdit{background: transparent;border :0px;font: "+font+"pt };";
	_etiquette->setStyleSheet(QString(styleSheet.c_str()));
	_etiquette->append(const_cast<char*>(_label->getEtiquette().c_str()));
	_etiquette->raise();
	_etiquette->show();
	_etiquette->setFont(QFont("URW Gothic L", 10));

	int  score = _label->getPoids();
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

// unsigned int CelluleLabel::getEid(){
// 	return _etab->getEid();
// }

CelluleLabel::CelluleLabel(Label* label,int width,int height,QWidget* parent): QLabel(parent){
	std::cout<<"cell constr"<<std::endl;
	_label = label;
	initItem(width,height);
}

CelluleLabel::~CelluleLabel(){
	//delete _pictureFrame;
	delete _etiquette;
	delete _note;
}