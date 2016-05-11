#include "CelluleRecherche.hpp"

void CelluleRecherche::initItem(int width, int height){
	this->setGeometry(QRect(0,0, width, height));
	this->setStyleSheet("QLabel{background: transparent;border: 3px solid #f2be03;}");
	std::cout<<"hllll"<<std::endl;
	
	// _pictureFrame = new QLabel(this);
	// _pictureFrame->setPixmap(QPixmap(QString::fromStdString()));
	// _pictureFrame->setAlignment(Qt::AlignTop | Qt::AlignCenter);
	// _pictureFrame->setGeometry(QRect(width-width/3,0, width, height));
	// _pictureFrame->raise();
	// _pictureFrame->show();
	// _pictureFrame->setStyleSheet("QLabel{background: transparent;border: 4px solid #f2be03};");
	
	_estabName = new QLabel(const_cast<char*>(_etab->getNom().c_str()),this);
	_estabName->setGeometry(QRect(width*2,height/8, width*5, height/5));
	_estabName->setStyleSheet("QLabel{font: 16pt; background: transparent;border :0px solid #f2be03 !important ;color:#f2be03;};");
	_estabName->raise();
	_estabName->show();

	_localite = new QLabel(const_cast<char*>(_etab->getAdresse().c_str()),this);
	_localite->setGeometry(QRect(width*8,height/2+height/4,width*2, height/5));
	_localite->raise();
	_localite->show();

	//int  score = _etab->getScore();
	int score = 0;
	std::string label5 = "Note: "+std::to_string(score);
	_score = new QLabel(this);
	_score->setGeometry(QRect(width*8,height/8,width*2, height/5));
	_score->setText(QString(label5.c_str()));
	_score->raise();
	_score->show();
}

unsigned int CelluleRecherche::getEid(){
	return _etab->getEid();
}

CelluleRecherche::CelluleRecherche(Etablissement* etab,int width,int height,QWidget* parent): QLabel(parent){
	_etab = etab;
	_bar = dynamic_cast<Bar*>(_etab);
	_resto = dynamic_cast<Restaurant*>(_etab);
	_hotel = dynamic_cast<Hotel*>(_etab);
	initItem(width,height);
}

CelluleRecherche::~CelluleRecherche(){
	//delete _pictureFrame;
	delete _estabName;
	delete _localite;
	delete _score;
}