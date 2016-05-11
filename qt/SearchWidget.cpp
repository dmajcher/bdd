#include "SearchWidget.hpp"



SearchWidget::SearchWidget(int width, int height, QWidget* parent) : QWidget(parent) {
	_width = width;
	_height = height;
	_parent = parent;
	_thisWidth = _width/3;
	_thisHeight = _height/8;
	_borderSize = _thisHeight/3;
	_searchEntry = new QLineEdit(this);
	_searchButton = new QPushButton(this);
	_restoCheck = new QCheckBox(this);
	_barCheck = new QCheckBox(this);
	_hotelCheck = new QCheckBox(this);
	setWidgetsPosition();
	setWidgetsStyle();
	this->raise();
	this->show();
}



void SearchWidget::setWidgetsPosition() {
	this->setGeometry(_thisWidth-_borderSize/2, _height/4, _thisWidth + _borderSize, _thisHeight-_borderSize/2);
	_searchEntry->setGeometry(_borderSize/2, _borderSize/2, _thisWidth-_thisWidth/4-_borderSize/2, _borderSize/1.5);
	_searchButton->setGeometry(_thisWidth - _thisWidth/4 + _borderSize/2, _borderSize/2, _thisWidth/4, _borderSize/1.5);
	_restoCheck->setGeometry(_borderSize/2, _borderSize+(_borderSize/2), (_thisWidth/1.5)/3, _borderSize/1.5);
	_hotelCheck->setGeometry((_borderSize/2) + ((_thisWidth/1.5)/3) + _borderSize/2, _borderSize+(_borderSize/2), (_thisWidth/1.5)/3, _borderSize/1.5);
	_barCheck->setGeometry((_borderSize/2) + (((_thisWidth/1.5)/3)*2) + _borderSize/2, _borderSize+(_borderSize/2), (_thisWidth/1.5)/3, _borderSize/1.5);
}



void SearchWidget::setWidgetsStyle() {
	this->setStyleSheet("background : lightgrey ; border-radius : 7px");
	_hotelCheck->setText("Hôtels");
	_barCheck->setText("Bars");
	_restoCheck->setText("Restaurants");
	_searchButton->setStyleSheet("background : white ; border-radius : 5px");
	_searchEntry->setStyleSheet("background : white ; border-radius : 5px");
	_searchButton->setText("Rechercher");
}