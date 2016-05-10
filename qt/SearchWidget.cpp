#include "SearchWidget.hpp"



SearchWidget::SearchWidget(int width, int height, QWidget* parent) : QWidget(parent) {
	_width = width;
	_height = height;
	_parent = parent;
	_thisWidth = _width/3;
	_thisHeight = _height/6;
	_borderSize = _thisHeight/3;
	_searchEntry = new QLineEdit(this);
	_searchButton = new QPushButton(this);
	_restoCheck = new QCheckBox(this);
	_barCheck = new QCheckBox(this);
	_hotelCheck = new QCheckBox(this);
}



void SearchWidget::setWidgetsPosition() {
	this->setGeometry(_thisWidth, _height/4, _thisWidth, _thisHeight);
	_searchEntry->setGeometry(0, 0, _thisWidth/2, _borderSize);
	_searchButton->setGeometry(_thisWidth/2 + _borderSize, 0, (_thisWidth)/6 - _borderSize, _borderSize);
	_restoCheck->setGeometry(_borderSize, _borderSize+(_borderSize/2), _thisWidth/3, _borderSize/1.5);
	_hotelCheck->setGeometry(_borderSize + _thisWidth/3, _borderSize+(_borderSize/2), _thisWidth/3, _borderSize/1.5);
	_hotelCheck->setGeometry(_borderSize + (_thisWidth/3*2), _borderSize+(_borderSize/2), _thisWidth/3, _borderSize/1.5);
}



