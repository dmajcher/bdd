#ifndef GUI_INTERFACE_HPP
#define GUI_INTERFACE_HPP


#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QRect>
#include <QCheckBox>
#include <QWidget>
#include <QSize>
#include <string>
#include <iostream>
#include "SearchWidget.hpp"
#include "PageRecherche.hpp"
#include "HomeWindow.hpp"
#include "../database/DataBase.hpp"
#include "HomeWindow.hpp"
#include <iostream>


class GuiInterface: public QApplication {
	Q_OBJECT
	private:
		int _width;
		int _height;
		DataBase* _dataBase;
		QMainWindow* _mainWindow;
		QWidget* _currentWindow;
		PageRecherche* _searchPage;
		QWidget* _w;
		QWidget* _t;
		SearchWidget* _searchWidget;
		HomeWindow* _homeWindow;

	public:
		GuiInterface(DataBase*, int, char**);
		void connectWidgets();
	public slots:
		void searchSigSlot(std::string);

};




#endif /*GUI_INTERFACE_HPP*/