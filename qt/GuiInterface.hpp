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
#include "../DataBase.hpp"


class GuiInterface: public QApplication {
	private:
		int _width;
		int _height;
		DataBase* _dataBase;
		QMainWindow* _mainWindow;
		QWidget* _currentWindow;
		PageRecherche* _searchPage;
		HomePage* _homePage;
		SearchWidget* _searchWidget;
		// HomeWindow* _homeWindow;
	public:
		GuiInterface(DataBase*, int, char**);

	public:
		void searchSigSlot(std::string);

};




#endif /*GUI_INTERFACE_HPP*/