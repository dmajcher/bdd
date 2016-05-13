#include "ProfilePage.hpp"

ProfilePage::ProfilePage(unsigned eid,DataBase* db,int height,int width, QWidget* parent) : QWidget(parent){
	_height = height;
	_width = width;
	_parent = parent;
	_db = db;
	_requestCom = "EidConcerne = "+ std::to_string(eid);
	std::string request = "EID = "+ std::to_string(eid);
	_etab = _db->getEtabByCond(request)[0];
	_bar = dynamic_cast<Bar*>(_etab);
	_resto = dynamic_cast<Restaurant*>(_etab);
	_hotel = dynamic_cast<Hotel*>(_etab);
	parent->setStyleSheet("background:url(../qt/Images/wood.jpg)");
	makeCommentTable();
	initPage();
	fillLabel();
	setStyle();
	connectButton();
	//makeSearchTableSlot(request);
}


void ProfilePage::setStyle() {
	this->resize(_width, _height);
	this->setStyleSheet("QWidget{background :transparent;}");
	this->setFont(QFont("URW Gothic L", 13));
	this->raise();
	this->show();
}


void ProfilePage::initPage(){
	//_commentButton = new QPushButton("Commentaires",this);

	_mainLabel = new QLabel(this);
	_mainLabel->setGeometry(QRect(0,_height/8,_width,_height/5));
    _mainLabel->setStyleSheet("QLabel {background: rgba(255,255,255,180);border-radius:10px;border-color:grey;border:5px}");
    _mainLabel->setFont(QFont("URW Gothic L", 12));

    _logo = new QLabel(this);
	_logo->setGeometry(QRect(_width/20,_height/8,_width/5,_height/5));
	_logo->setPixmap(QPixmap("../qt/Images/test.png"));
	_logo->setStyleSheet("QLabel{background: transparent;border:0px}");
	_logo->show();
	_logo->raise();

	_returnButton = new QPushButton("Retour au menu",this);
	_returnButton->setGeometry(QRect(_width-_width/7, _height-_height/8, _width/8, _height/20));
	_returnButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_returnButton->show();
	_returnButton->raise();
	_returnButton->setFont(QFont("URW Gothic L", 13));
}

void ProfilePage::fillLabel(){
	_name = new QLabel(const_cast<char*>(_etab->getNom().c_str()),this);
	_name->setGeometry(QRect(_width/15+2*_width/13+ _width/20,_height/8,2*_width/13,_height/15));
	_name->setStyleSheet("QLabel{font: 18pt;background: transparent;}");
	_name->setFont(QFont("URW Gothic L", 10));

		//int  score = _etab->getScore();
	int score = 0;
	std::string label5 = "Note: "+std::to_string(score);
	_score = new QLabel(this);
	_score->setGeometry(QRect(_width/15+2*_width/13+ _width/20,_height/8+_height/20,2*_width/13,_height/15));
	_score->setStyleSheet("QLabel{font: 16pt;background: transparent;}");
	_score->setText(QString(label5.c_str()));
	_score->raise();
	_score->show();
	_score->setFont(QFont("URW Gothic L", 10));

	_siteIco = new QLabel(this);
	_siteIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20,_height/8+_height/20+_height/15,_width/15,_height/15));
	_siteIco->setStyleSheet("QLabel{background: transparent;}");
	_siteIco->setPixmap(QPixmap("../qt/Images/laptop.png"));
	_siteIco->raise();
	_siteIco->show();

	_site = new QLabel(const_cast<char*>(_etab->getSiteWeb().c_str()),this);
	_site->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25,_height/8+_height/20+_height/15,_width/4,_height/15));
	_site->setStyleSheet("QLabel{background: transparent;}");
	_site->raise();
	_site->show();
	_site->setFont(QFont("URW Gothic L", 10));

	_telIco = new QLabel(this);
	_telIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4,_height/8+_height/20+_height/15,_width/15,_height/15));
	_telIco->setStyleSheet("QLabel{background: transparent;}");
	_telIco->setPixmap(QPixmap("../qt/Images/smartphones.png"));
	_telIco->raise();
	_telIco->show();

	_tel = new QLabel(const_cast<char*>(_etab->getNumTel().c_str()),this);
	_tel->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/25,_height/8+_height/20+_height/15,_width/8,_height/15));
	_tel->setStyleSheet("QLabel{background: transparent;}");
	_tel->raise();
	_tel->show();
	_tel->setFont(QFont("URW Gothic L", 10));

	_adressIco = new QLabel(this);
	_adressIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20+2*_width/12,_height/8,_width/15,_height/15));
	_adressIco->setStyleSheet("QLabel{background: transparent;}");
	_adressIco->setPixmap(QPixmap("../qt/Images/placeholder.png"));
	_adressIco->raise();
	_adressIco->show();

	_adress = new QLabel(const_cast<char*>(_etab->getAdresse().c_str()),this);
	_adress->setGeometry(QRect(_width/15+2*_width/13+ _width/20+2*_width/12+_width/50,_height/8,_width/6,_height/15));
	_adress->setStyleSheet("QLabel{background: transparent;}");
	_adress->raise();
	_adress->show();
	_adress->setFont(QFont("URW Gothic L", 10));

	float lat = _etab->getLatitude();
	float longi = _etab->getLongitude();
	std::string latlong = "Latitude: "+ std::to_string(lat)+ "   Longitude: "+ std::to_string(longi);
	_latlong = new QLabel(this);
	_latlong->setText(QString(latlong.c_str()));
	_latlong->setGeometry(QRect(_width/15+2*_width/13+ _width/20+2*_width/12+_width/50+_width/7,_height/8,_width/8,_height/15));
	_latlong->setStyleSheet("QLabel{background: transparent;}");
	_latlong->raise();
	_latlong->show();
	_latlong->setFont(QFont("URW Gothic L", 10));

	if (_bar){
		_fumeur = new QLabel(this);
		_fumeur->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/25+_width/7 ,_height/8+_height/20+_height/15,_width/15,_height/15));
		_fumeur->setStyleSheet("QLabel{background: transparent;}");
		if (_bar->isFumeur()){_fumeur->setPixmap(QPixmap("../qt/Images/smoking.png"));}
		else{_fumeur->setPixmap(QPixmap("../qt/Images/nosmoking.png"));}
		_fumeur->raise();
		_fumeur->show();
		_fumeur->setFont(QFont("URW Gothic L", 10));

		_petiteRestoIco = new QLabel(this);
		_petiteRestoIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/25+_width/5 + _width/14,_height/8+_height/20+_height/10,_width/15,_height/15));
		_petiteRestoIco->setAlignment(Qt::AlignTop);
		_petiteRestoIco->setPixmap(QPixmap("../qt/Images/sandwich.png"));

		_petiteResto = new QLabel(this);
		_petiteResto->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/25+_width/5 + _width/14+_width/25,_height/8+_height/20+_height/9,_width/15,_height/15));
		_petiteResto->setAlignment(Qt::AlignTop);
		_petiteResto->raise();
		_petiteResto->show();
		_petiteResto->setFont(QFont("URW Gothic L", 10));

		if (_bar->hasPetiteResto()){
			_petiteResto->setStyleSheet("QLabel{background: transparent;color:green;}");
			_petiteResto->setText("Oui");
		}
		else{
			_petiteResto->setStyleSheet("QLabel{background: transparent;color:red;}");
			_petiteResto->setText("Non");
		}

	}

	if(_resto){
		_deliveryIco = new QLabel(this);
		_deliveryIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/25+_width/8 ,_height/8+_height/20+_height/15,_width/15,_height/15));
		_deliveryIco->setStyleSheet("QLabel{background: transparent;}");
		if (_resto->hasLivraison()){_deliveryIco->setPixmap(QPixmap("../qt/Images/delivery.png"));}
		else{_deliveryIco->setPixmap(QPixmap("../qt/Images/nodelivery.png"));}
		_deliveryIco->setAlignment(Qt::AlignBottom);
		_deliveryIco->raise();
		_deliveryIco->show();

		_takeAwayIco = new QLabel(this);
		_takeAwayIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/25+_width/5 ,_height/8+_height/25+_height/10,_width/15,_height/15));
		_takeAwayIco->setAlignment(Qt::AlignTop);
		_takeAwayIco->setPixmap(QPixmap("../qt/Images/takeAway.png"));

		_takeAway = new QLabel(this);
		_takeAway->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/25+_width/5 +_width/25,_height/8+_height/25+_height/9,_width/15,_height/15));
		_takeAway->setAlignment(Qt::AlignTop);
		_takeAway->raise();
		_takeAway->show();
		_takeAway->setFont(QFont("URW Gothic L", 10));

		if (_resto->hasTakeAway()){
			_takeAway->setStyleSheet("QLabel{background: transparent;color:green;}");
			_takeAway->setText("Oui");
		}
		else{
			_takeAway->setStyleSheet("QLabel{background: transparent;color:red;}");
			_takeAway->setText("Non");
		}

		_priceIco = new QLabel(this);
		_priceIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/26+_width/5,_height/8,_width/6,_height/15));
		_priceIco->setAlignment(Qt::AlignCenter);
		_priceIco->setStyleSheet("QLabel{background: transparent;}");
		_priceIco->setPixmap(QPixmap("../qt/Images/price.png"));
		_price = new QLabel(this);
		_price->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/26+_width/5 +_width/25,_height/8,_width/6,_height/15));
		_price->setAlignment(Qt::AlignCenter);
		_price->setStyleSheet("QLabel{background: transparent;}");
		_price->setText(QString(std::to_string(_resto->getPrix()).c_str()));
		_price->raise();
		_price->show();
		_price->setFont(QFont("URW Gothic L", 10));

		_seatsIco = new QLabel(this);
		_seatsIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/26+_width/5+_width/12,_height/8+_height/30+_height/9,_width/6,_height/15));
		_seatsIco->setAlignment(Qt::AlignTop);
		_seatsIco->setStyleSheet("QLabel{background: transparent;}");
		_seatsIco->setPixmap(QPixmap("../qt/Images/table.png"));
		_seats = new QLabel(this);
		_seats->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/26+_width/5 +_width/9,_height/8+_height/30+_height/9,_width/6,_height/15));
		_seats->setAlignment(Qt::AlignTop);
		_seats->setStyleSheet("QLabel{background: transparent;}");
		_seats->setText(QString(std::to_string(_resto->getNbPlaces()).c_str()));
		_seats->raise();
		_seats->show();
		_seats->setFont(QFont("URW Gothic L", 10));

	}

}

void ProfilePage::connectButton(){
	connect(_returnButton,SIGNAL(clicked()),this,SLOT(returnSlot()));
}

void ProfilePage::returnSlot(){
	emit canceled();
}

void ProfilePage::makeCommentTable(){
	_commentTable = new TableCommentaire(_db->getCommByCond(_requestCom),this);
    _commentTable->setGeometry(QRect(_width/5+_width/37,_height/3+_height/22,_width/2+_width/4+_width/20,_height/3+_height/9+_height/225));
    _commentTable->raise();
    _commentTable->show();
}

void ProfilePage::makeLabelTable(){
	_labelTable = new TableLabel(_db->getLabelByCond(_requestCom),this);
	_labelTable->setGeometry(QRect(0,_height/3+_height/22,_width/7,_height/3+_height/9+_height/225));
    _labelTable->raise();
    _labelTable->show();
}
// void ProfilePage::connectButton(){
// 	connect(_searchEntry,SIGNAL(searchSig(std::string)),this,SLOT(makeSearchTableSlot(std::string)));
// }

// void ProfilePage::makeSearchTableSlot(std::string request){
// 	delete _searchTable; 
// 	_searchTable = new TableRecherche(_db->getEtabByCond(request),this);
// 	std::cout<<"setgeo"<<std::endl;
//     _searchTable->setGeometry(_width/15+2*_width/13+ _width/70,_height/6,_width-_width/3,_height/2 +_height/5);
//     _searchTable->raise();
//     _searchTable->show();
// }

ProfilePage::~ProfilePage(){
	if(_bar){
		delete _fumeur;
		delete _petiteResto;
		delete _petiteRestoIco;
	}
	if(_resto){
		delete _deliveryIco;
		delete _takeAwayIco;
		delete _takeAway;
		delete _seats;
		delete _seatsIco;
		delete _priceIco;
	}
	delete _commentTable;
	delete _labelTable;
	delete _name;
	delete _score;
	delete _siteIco;
	delete _site;
	delete _adressIco;
	delete _adress;
	delete _telIco;
	delete _tel;
	delete _latlong;
	delete _mainLabel;
	delete _logo;
}