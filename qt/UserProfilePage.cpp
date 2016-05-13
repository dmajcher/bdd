#include "UserProfilePage.hpp"

UserProfilePage::UserProfilePage(std::string auteur,DataBase* db,int height,int width, QWidget* parent) : QWidget(parent){
	_height = height;
	_width = width;
	_parent = parent;
	_db = db;
	std::string gu = "\"";
	_requestCom = "Auteur = "+ gu+auteur+ gu;
	std::string request = "NameId = "+ gu+auteur+gu;
	User user = _db->getUserByCond(request); 
	_user = &(user);
	parent->setStyleSheet("background:url(../qt/Images/wood.jpg)");
	makeCommentTable();
	initPage();
	fillPage();
	setStyle();
	connectButton();
	//makeSearchTableSlot(request);
}


void UserProfilePage::setStyle() {
	this->resize(_width, _height);
	this->setStyleSheet("QWidget{background :transparent;}");
	this->setFont(QFont("URW Gothic L", 13));
	this->raise();
	this->show();
}


void UserProfilePage::initPage(){
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

void UserProfilePage::fillPage(){
	_name = new QLabel(const_cast<char*>(_user->getName().c_str()),this);
	_name->setGeometry(QRect(_width/15+2*_width/13+ _width/20,_height/8,2*_width/13,_height/15));
	_name->setStyleSheet("QLabel{font: 18pt;background: transparent;}");
	_name->setFont(QFont("URW Gothic L", 10));
	_name->show();
	_name->raise();

	_admin = new QLabel(this);
	_admin->setGeometry(QRect(_width/15+2*_width/13+ _width/20,_height/8+_height/20,2*_width/13,_height/15));
	if(_user->isAdmin()){
		_admin->setStyleSheet("QLabel{font: 16pt;background: transparent;color :red}");
		_admin->setText("Admin");
	}
	else{
		_admin->setStyleSheet("QLabel{font: 16pt;background: transparent;color :green}");
		_admin->setText("Regular");
	}
	_admin->raise();
	_admin->show();
	_admin->setFont(QFont("URW Gothic L", 10));

	_siteIco = new QLabel(this);
	_siteIco->setGeometry(QRect(_width/15+2*_width/13+ _width/20,_height/8+_height/20+_height/15,_width/15,_height/15));
	_siteIco->setStyleSheet("QLabel{background: transparent;}");
	_siteIco->setPixmap(QPixmap("../qt/Images/laptop.png"));
	_siteIco->raise();
	_siteIco->show();

	_email = new QLabel(const_cast<char*>(_user->getEmail().c_str()),this);
	_email->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25,_height/8+_height/20+_height/15,_width/4,_height/15));
	_email->setStyleSheet("QLabel{background: transparent;}");
	_email->raise();
	_email->show();
	_email->setFont(QFont("URW Gothic L", 10));

	_date = new QLabel("17/05/2016",this);
	_date->setGeometry(QRect(_width/15+2*_width/13+ _width/20+_width/25+_width/4,_height/8+_height/20+_height/15,_width/15,_height/15));
	_date->setStyleSheet("QLabel{background: transparent;}");
	_date->raise();
	_date->show();
}

void UserProfilePage::connectButton(){
	connect(_returnButton,SIGNAL(clicked()),this,SLOT(returnSlot()));
}

void UserProfilePage::returnSlot(){
	emit canceled();
}

void UserProfilePage::makeCommentTable(){
	_commentTable = new TableCommentaire(_db->getCommByCond(_requestCom),this);
    _commentTable->setGeometry(QRect(_width/5+_width/37,_height/3+_height/22,_width/2+_width/4+_width/20,_height/3+_height/9+_height/225));
    _commentTable->raise();
    _commentTable->show();
}

UserProfilePage::~UserProfilePage(){
	delete _commentTable;
	delete _name;
	delete _siteIco;
	delete _email;
	delete _mainLabel;
	delete _logo;
}