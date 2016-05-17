#include "AdminWidget.hpp"



AdminWidget::AdminWidget(int w, int h, DataBase* db, User* u, QWidget* parent) : QWidget(parent) {
	_width = w;
	_height = h;
	_db = db;
	_user = u;
	_parent = parent;
	_buttonWidth = _width/10;
	_buttonHeight = _height/20;
	this->resize(_width, _height);
	_parent->setStyleSheet("background : url(../qt/Images/wood.jpg)");
	_addBarButton = new QPushButton(this);	
	_addRestoButton = new QPushButton(this);	
	_addHotelButton = new QPushButton(this);
	_okButton = new QPushButton(this);
	_confirmButton = new QPushButton(this);
	_entryWidth = _width/2.5;
	_entryHeight = _height/30;
	_addHotelButton->setText("Ajouter un hotel");
	_addRestoButton->setText("Ajouter un restaurant");
	_addBarButton->setText("Ajouter un bar");
	_addBarButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_addRestoButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_addHotelButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_okButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_confirmButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");

	_addBarButton->setGeometry(_width/2 - _buttonWidth/2, _height/2 - _buttonHeight, _buttonWidth, _buttonHeight);
	_addRestoButton->setGeometry(_width/2 - _buttonWidth*2, _height/2 - _buttonHeight, _buttonWidth, _buttonHeight);
	_addHotelButton->setGeometry(_width/2 + _buttonWidth, _height/2 - _buttonHeight, _buttonWidth, _buttonHeight);
	_okButton->setGeometry(_width - _buttonWidth - _height/20, _height-_buttonWidth/2, _buttonWidth, _height/20);
	_okButton->setText("Valider");
	_confirmButton->setGeometry(_width - _buttonWidth - _height/20, _height-_buttonWidth/2, _buttonWidth, _height/20);
	_confirmButton->setText("Confirmer");

	_confirmButton->setFont(QFont("URW Gothic L", 12));
	_addBarButton->setFont(QFont("URW Gothic L", 12));
	_addRestoButton->setFont(QFont("URW Gothic L", 12));
	_addHotelButton->setFont(QFont("URW Gothic L", 12));
	_okButton->setFont(QFont("URW Gothic L", 12));

	connectButtons();

	raise();
	show();
	_okButton->hide();
	_confirmButton->hide();

} 



void AdminWidget::restoSlot() {
	std::cout<<"fezfe"<<std::endl;
	_okButton->hide();
	_confirmButton->raise();
	_confirmButton->show();
	_prixPlats = new QLineEdit(this);
	_nbPlaces = new QLineEdit(this);
	_livraison = new QCheckBox(this);
	_takeAway = new QCheckBox(this);

	_prixPlats->setGeometry(_width/2 - _entryWidth/6, _height/3, _entryWidth/3, _entryHeight);
	_nbPlaces->setGeometry(_width/2 - _entryWidth/6, _height/3+_entryHeight*2, _entryWidth/3, _entryHeight);
	_livraison->setGeometry(_width/2 - _entryWidth/6, _height/3+_entryHeight*4, _entryWidth/3, _entryHeight);
	_takeAway->setGeometry(_width/2 - _entryWidth/6, _height/3+_entryHeight*6, _entryWidth/3, _entryHeight);

	_prixPlats->raise();
	_nbPlaces->raise();
	_livraison->raise();
	_takeAway->raise();

	_prixPlats->show();
	_nbPlaces->show();
	_livraison->show();
	_takeAway->show();

}


void AdminWidget::barSlot() {
	_okButton->hide();
	_confirmButton->raise();
	_confirmButton->show();
}



void AdminWidget::hotelSlot() {}


void AdminWidget::okSlot() {
	if (_kind == "R") {
		_newResto->setEtabInfos(_nomEtab->text().toStdString(), _adresseEtab->text().toStdString(), std::stoi(_localiteEtab->text().toStdString()), _numTelEtab->text().toStdString(),_siteEtab->text().toStdString(),_user->getName(),"",std::stof(_latitudeEtab->text().toStdString()),std::stof(_longitEtab->text().toStdString()));
		restoSlot();
	}
	else if (_kind == "B") {
		_newBar->setEtabInfos(_nomEtab->text().toStdString(), _adresseEtab->text().toStdString(), std::stoi(_localiteEtab->text().toStdString()), _numTelEtab->text().toStdString(),_siteEtab->text().toStdString(),_user->getName(),"",std::stof(_latitudeEtab->text().toStdString()),std::stof(_longitEtab->text().toStdString()));
		barSlot();
	}
	else {
		_newHotel->setEtabInfos(_nomEtab->text().toStdString(), _adresseEtab->text().toStdString(), std::stoi(_localiteEtab->text().toStdString()), _numTelEtab->text().toStdString(),_siteEtab->text().toStdString(),_user->getName(),"",std::stof(_latitudeEtab->text().toStdString()),std::stof(_longitEtab->text().toStdString()));
		hotelSlot();
	}
	_nomEtab->hide();
	_adresseEtab->hide();
	_localiteEtab->hide();
	_numTelEtab->hide();
	_siteEtab->hide();
	_latitudeEtab->hide();
	_longitEtab->hide();
	
}


void AdminWidget::connectButtons() {
	connect(_addRestoButton, SIGNAL(clicked()), this, SLOT(addRestoSlot()));
	connect(_addBarButton, SIGNAL(clicked()), this, SLOT(addBarSlot()));
	connect(_addHotelButton, SIGNAL(clicked()), this, SLOT(addHotelSlot()));
	connect(_okButton, SIGNAL(clicked()), this, SLOT(okSlot()));
	connect(_confirmButton, SIGNAL(clicked()), this, SLOT(confSlot()));
}


void AdminWidget::addRestoSlot() {
	hideButtons();
	_kind = "R";
	_newResto = new Restaurant(-1, false, false, "0OOOOOO", -1);
	askEtabInfos();
	
}

void AdminWidget::addBarSlot() {
	hideButtons();
	_kind = "B";
	_newBar = new Bar(false, false);
	askEtabInfos();
	
	
}

void AdminWidget::addHotelSlot() {
	hideButtons();
	_kind = "H";
	_newHotel = new Hotel(-1, -1, -1);
	askEtabInfos();
	
}


void AdminWidget::askEtabInfos() {
	_nomEtab = new QLineEdit(this);
	_adresseEtab = new QLineEdit(this);
	_localiteEtab = new QLineEdit(this);
	_numTelEtab = new QLineEdit(this);
	_siteEtab = new QLineEdit(this);
	_latitudeEtab = new QLineEdit(this);
	_longitEtab = new QLineEdit(this);

	_nomEtab->setPlaceholderText("Nom");
	_adresseEtab->setPlaceholderText("Adresse");
	_localiteEtab->setPlaceholderText("Localité");
	_numTelEtab->setPlaceholderText("Téléphone");
	_siteEtab->setPlaceholderText("Site web");
	_latitudeEtab->setPlaceholderText("latitute");
	_longitEtab->setPlaceholderText("Longitude");
	_nomEtab->setFont(QFont("URW Gothic L", 12));
	_adresseEtab->setFont(QFont("URW Gothic L", 12));
	_localiteEtab->setFont(QFont("URW Gothic L", 12));
	_numTelEtab->setFont(QFont("URW Gothic L", 12));
	_siteEtab->setFont(QFont("URW Gothic L", 12));
	_latitudeEtab->setFont(QFont("URW Gothic L", 12));
	_longitEtab->setFont(QFont("URW Gothic L", 12));

	_nomEtab->setGeometry(_width/2 - _entryWidth/2, _height/6, _entryWidth, _entryHeight);
	_adresseEtab->setGeometry(_width/2 - _entryWidth/2, _height/6 + (_entryHeight*2), _entryWidth, _entryHeight);
	_localiteEtab->setGeometry(_width/2 - _entryWidth/2, _height/6 + (_entryHeight*4), _entryWidth, _entryHeight);
	_numTelEtab->setGeometry(_width/2 - _entryWidth/2, _height/6 + (_entryHeight*6), _entryWidth, _entryHeight);
	_siteEtab->setGeometry(_width/2 - _entryWidth/2, _height/6 + (_entryHeight*8), _entryWidth, _entryHeight);
	_latitudeEtab->setGeometry(_width/2 - _entryWidth/2, _height/6 + (_entryHeight*10), _entryWidth, _entryHeight);
	_longitEtab->setGeometry(_width/2 - _entryWidth/2, _height/6 + (_entryHeight*12), _entryWidth, _entryHeight);

	_nomEtab->raise();
	_adresseEtab->raise();
	_localiteEtab->raise();
	_numTelEtab->raise();
	_siteEtab->raise();
	_latitudeEtab->raise();
	_longitEtab->raise();

	_nomEtab->show();
	_adresseEtab->show();
	_localiteEtab->show();
	_numTelEtab->show();
	_siteEtab->show();
	_latitudeEtab->show();
	_longitEtab->show();

}



void AdminWidget::hideButtons() {
	_addHotelButton->hide();
	_addRestoButton->hide();
	_addBarButton->hide();
	_okButton->raise();
	_okButton->show();
}