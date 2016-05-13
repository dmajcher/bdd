#include "ProfilePage.hpp"

ProfilePage::ProfilePage(unsigned eid,DataBase* db,int height,int width, QWidget* parent) : QWidget(parent){
	_height = height;
	_width = width;
	_parent = parent;
	_db = db;
	std::string _request = "EID = "+ std::to_string(eid); 
	_etab = _db->getEtabByCond(_request)[0];
	_bar = dynamic_cast<Bar*>(_etab);
	_resto = dynamic_cast<Restaurant*>(_etab);
	_hotel = dynamic_cast<Hotel*>(_etab);
	parent->setStyleSheet("background:url(../qt/Images/wood.jpg)");
	initPage();
	fillLabel();
	setStyle();
	//makeSearchTableSlot(request);
}


void ProfilePage::setStyle() {
	this->resize(_width, _height);
	this->setStyleSheet("QWidget{background :transparent;}");
	this->raise();
	this->show();
}


void ProfilePage::initPage(){
	//_commentButton = new QPushButton("Commentaires",this);

	_mainLabel = new QLabel(this);
	_mainLabel->setGeometry(QRect(0,_height/8,_width,_height/5));
    _mainLabel->setStyleSheet("QLabel {background: rgba(255,255,255,180);border-radius:10px;border-color:grey;border:5px}");

}

void ProfilePage::fillLabel(){
	_name = new QLabel(const_cast<char*>(_etab->getNom().c_str()),this);
	_name->setGeometry(QRect(_width/15+2*_width/13+ _width/20,_height/8,2*_width/13,_height/15));
	_name->setStyleSheet("QLabel{font: 25pt;background: transparent;}");

		//int  score = _etab->getScore();
	int score = 0;
	std::string label5 = "Note: "+std::to_string(score);
	_score = new QLabel(this);
	_score->setGeometry(QRect(_width/15+2*_width/13+ _width/20,_height/8+_height/20,2*_width/13,_height/15));
	_score->setStyleSheet("QLabel{font: 16pt;background: transparent;}");
	_score->setText(QString(label5.c_str()));
	_score->raise();
	_score->show();

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

	_telIco = new QLabel(this);
	_telIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4,_height/8+_height/20+_height/15,_width/15,_height/15));
	_telIco->setStyleSheet("QLabel{background: transparent;}");
	_telIco->setPixmap(QPixmap("../qt/Images/smartphones.png"));
	_telIco->raise();
	_telIco->show();

	_tel = new QLabel(const_cast<char*>(_etab->getNumTel().c_str()),this);
	_tel->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4+_width/25,_height/8+_height/20+_height/15,_width/5,_height/15));
	_tel->setStyleSheet("QLabel{background: transparent;}");
	_tel->raise();
	_tel->show();

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

	float lat = _etab->getLatitude();
	float longi = _etab->getLongitude();
	std::string latlong = "Latitude: "+ std::to_string(lat)+ "   Longitude: "+ std::to_string(longi);
	_latlong = new QLabel(this);
	_latlong->setText(QString(latlong.c_str()));
	_latlong->setGeometry(QRect(_width/15+2*_width/13+ _width/20+2*_width/12+_width/50+_width/7,_height/8,_width/8,_height/15));
	_latlong->setStyleSheet("QLabel{background: transparent;}");
	_latlong->raise();
	_latlong->show();


}


void ProfilePage::makeCommentTable(){
	delete _commentTable; 
	_commentTable = new TableCommentaire(_db->getComByCond(_request),this);
    _commentTable->setGeometry(QRect(_width/15+2*_width/13+ _width/70,_height/3+_height/22,_width-_width/3,_height/3+_height/9+_height/225));
    _commentTable->raise();
    _commentTable->show();
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
	// delete _searchTable;
	// delete _searchEntry;
}