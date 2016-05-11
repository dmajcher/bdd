#include "HomeWindow.hpp"



HomeWindow::HomeWindow(int width, int height, QWidget* parent) : QWidget(parent) {
	_width = width;
	_height = height;
	_parent = parent;
	setGeometry(0, 0, _width, _height);

}