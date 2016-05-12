#include "HomeWindow.hpp"



HomeWindow::HomeWindow(int width, int height, int h, int w, QWidget* parent) : QWidget(parent) {
	_width = width;
	_height = height;
	_parent = parent;
    _w = w;
    _h = h; 
    _panoWidget = new QWidget(this);
    _icoWidget = new QWidget(this);
    setStyle();
    raise();
    show();
}



void HomeWindow::setStyle(){
    resize(_width, _height);
    _panoWidget->setGeometry(0, _height/5.5, _width, _height/1.75);
    this->setStyleSheet("background : url(../qt/Images/wood.jpg)");
    _panoWidget->setStyleSheet("background : url(../qt/Images/horeca.jpg)");
    _icoWidget->setGeometry(_width/9, _h/2000, _w/2, _h*1.7);
    _icoWidget->setStyleSheet("QWidget{background: url(../qt/Images/test.png) center center}");
}



HomeWindow::~HomeWindow() {
    delete _panoWidget;
    delete _icoWidget;
}