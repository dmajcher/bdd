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
#include "SearchWidget.hpp"
#include "PageRecherche.hpp"
#include "HomeWindow.hpp"
#include "../DataBase.hpp"
#include "HomeWindow.hpp"


class GuiInterface: public QApplication {
	private:
		int _width;
		int _height;
		DataBase* _dataBase;
		QMainWindow* _mainWindow;
		QWidget* _currentWindow;
		PageRecherche* _searchPage;
		SearchWidget* _searchWidget;
		HomeWindow* _homeWindow;
	public:
		GuiInterface(DataBase*, int, char**);
		void connectSearch();
	public slots:
		void searchSigSlot(std::string);

};




#endif /*GUI_INTERFACE_HPP*/