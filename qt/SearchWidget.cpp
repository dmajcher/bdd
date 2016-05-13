#include "SearchWidget.hpp"



SearchWidget::SearchWidget(int width, int height, QWidget* parent) : QWidget(parent) {
	_width = width;
	_height = height;
	_parent = parent;
	_thisWidth = _width/3;
	_thisHeight = _height/8;
	_borderSize = _thisHeight/3;
	_checkSize = (_thisWidth-_thisWidth/4-_borderSize/2)/3 - _borderSize/3;
	_searchEntry = new QLineEdit(this);
	_searchButton = new QPushButton(this);
	_restoCheck = new QCheckBox(this);
	_barCheck = new QCheckBox(this);
	_hotelCheck = new QCheckBox(this);
	setWidgetsPosition();
	setWidgetsStyle();
	connectWidgets();
	this->raise();
	this->show();
}



void SearchWidget::setWidgetsPosition() {
	this->setGeometry(_thisWidth-_borderSize/2, (_height/2-(_thisHeight-_borderSize/2)), _thisWidth + _borderSize, _thisHeight-_borderSize/2);
	_searchEntry->setGeometry(_borderSize/2, _borderSize/2, _thisWidth-_thisWidth/4-_borderSize/2, _borderSize/1.5);
	_searchButton->setGeometry(_thisWidth - _thisWidth/4 + _borderSize/2, _borderSize/2, _thisWidth/4, _borderSize/1.5);
	_restoCheck->setGeometry(_borderSize/2, _borderSize+(_borderSize/2), _checkSize, _borderSize/1.5);
	_hotelCheck->setGeometry((_borderSize) + (_checkSize) , _borderSize+(_borderSize/2), _checkSize, _borderSize/1.5);
	_barCheck->setGeometry((_borderSize/2)*3 + (_checkSize)*2, _borderSize+(_borderSize/2), _checkSize, _borderSize/1.5);
}


void SearchWidget::centerWidget() {
	this->move(_thisWidth-_borderSize/2, (_height/2-(_thisHeight-_borderSize/2)));	
}



void SearchWidget::setWidgetsStyle() {
	_searchEntry->setPlaceholderText("Rechercher par nom, ville, adresse ou localité");
	_hotelCheck->setText("Hôtels");
	_barCheck->setText("Bars");
	_restoCheck->setText("Restaurants");
	_searchEntry->setStyleSheet("background : rgba(255,255,255,180) ; border-radius : 5px");
	_barCheck->setStyleSheet("background : rgba(255,255,255,180) ; border-radius : 4px");
	_restoCheck->setStyleSheet("background : rgba(255,255,255,180) ; border-radius : 4px");
	_hotelCheck->setStyleSheet("background : rgba(255,255,255,180) ; border-radius : 4px");
	_searchButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_searchButton->setText("Rechercher");
	_searchButton->setFont(QFont("URW Gothic L", 12));
	_searchEntry->setFont(QFont("URW Gothic L", 11));
	_hotelCheck->setFont(QFont("URW Gothic L", 12));
	_barCheck->setFont(QFont("URW Gothic L", 12));
	_restoCheck->setFont(QFont("URW Gothic L", 12));
}



void SearchWidget::connectWidgets() {
	connect(_searchButton, SIGNAL(clicked()), this, SLOT(searchSlot()));
	connect(_searchEntry, SIGNAL(returnPressed()), this, SLOT(searchSlot()));
	connect(_searchEntry, SIGNAL(textChanged(const QString&)),this,SLOT(entrySlot()));
}


void SearchWidget::entrySlot() {
	_searchEntry->setStyleSheet("color : black");
	_searchEntry->setPlaceholderText("Rechercher par nom, ville, adresse ou localité");
}


void SearchWidget::searchSlot() {
	std::string resto = "";
	std::string bar = "";
	std::string hotel = "";
	int count = 0;
	if (_hotelCheck->isChecked()) {
		count += 1;
		hotel += "H";
	}
	if (_barCheck->isChecked()){
		bar += "B";
		count += 1;
	}
	if (_restoCheck->isChecked()){
		resto += "R";
		count += 1;
	}
	if (count == 0) {
		_searchEntry->clear();
		_searchEntry->setPlaceholderText("Sélectionnez un ou plusieurs établissements à rechercher");
		_searchEntry->setStyleSheet("color : red");
	}
	else {
		std::string gu = "\"";
		std::string askedSearch = _searchEntry->text().toStdString();
		std::string cond = "(Type = "+gu+hotel+gu+" OR Type = "+gu+bar+gu+" OR Type = "+gu+resto+gu+") AND (Nom LIKE "+gu+"\%"+askedSearch+"\%"+gu + " OR Localite = "+gu+askedSearch+gu +" OR Adresse LIKE " +gu+"\%"+askedSearch+"\%"+gu+")";
		emit searchSig(cond);
	}
}