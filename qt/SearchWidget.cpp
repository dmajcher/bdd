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



void SearchWidget::setWidgetsStyle() {
	_searchEntry->setPlaceholderText("Rechercher par nom ou localité");
	_hotelCheck->setText("Hôtels");
	_barCheck->setText("Bars");
	_restoCheck->setText("Restaurants");
	_searchEntry->setStyleSheet("background : rgba(255,255,255,180) ; border-radius : 5px");
	_barCheck->setStyleSheet("background : rgba(255,255,255,180) ; border-radius : 4px");
	_restoCheck->setStyleSheet("background : rgba(255,255,255,180) ; border-radius : 4px");
	_hotelCheck->setStyleSheet("background : rgba(255,255,255,180) ; border-radius : 4px");
	_searchButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_searchButton->setText("Rechercher");
}



void SearchWidget::connectWidgets() {
	connect(_searchButton, SIGNAL(clicked()), this, SLOT(searchSlot()));
}



void SearchWidget::searchSlot() {
	std::string gu = "\"";
	std::string askedSearch = _searchEntry->text().toStdString();
	std::string cond = "Nom LIKE "+gu+"\%"+askedSearch+"\%"+gu + " OR Localite = "+gu+askedSearch+gu;
	emit searchSig(cond);
}