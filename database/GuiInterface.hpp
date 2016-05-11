#ifndef GUI_INTERFACE_HPP
#define GUI_INTERFACE_HPP


#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QRect>
#include <QCheckBox>
#include <QWidget>
#include "SearchWidget.hpp"
#include "../bdd/DataBase.hpp"


class GuiInterface: public QApplication {
	private:
		int _width;
		int _height;
		QMainWindow* _mainWindow;
		QWidget* _currentWindow;
		QLineEdit* _searchWidget;
		// HomeWindow* _homeWindow;
	public:
		GuiInterface(int, char**);

};




#endif /*GUI_INTERFACE_HPP*/