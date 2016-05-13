#ifndef GUI_INTERFACE_HPP
#define GUI_INTERFACE_HPP


#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QMainWindow>
#include <QRect>
#include <QCheckBox>
#include <QSize>
#include <string>
#include <iostream>
#include "SearchWidget.hpp"
#include "PageRecherche.hpp"
#include "HomeWindow.hpp"
#include "UserProfilePage.hpp"
#include "../database/DataBase.hpp"
#include "HomeWindow.hpp"
#include "ProfilePage.hpp"
#include "TaskBar.hpp"
#include "LogWidget.hpp"
#include "AdminWidget.hpp"
#include <iostream>


class GuiInterface: public QApplication {
	Q_OBJECT
	private:
		int _width;
		int _height;
		DataBase* _dataBase;
		QMainWindow* _mainWindow;
		QWidget* _currentWindow;
		ProfilePage* _profilePage;
		UserProfilePage* _userProfile;
		TaskBar* _taskBar;
		AdminWidget* _adminWindow = nullptr;
		PageRecherche* _searchPage = nullptr;
		QWidget* _w;
		QWidget* _t;
		SearchWidget* _searchWidget;
		HomeWindow* _homeWindow;
		LogWidget* _connection = nullptr;
		User* _user = nullptr;

	public:
		GuiInterface(DataBase*, int, char**);
		void connectWidgets();
		void connectLog();

	public slots:
		void searchSigSlot(std::string);
		void makeEtabProfileSlot(unsigned);
		void makeUserProfileSlot(std::string);
		void loginSlot();
		void signinSlot();
		void canceledSlot();
		void loggedSlot();
		void logoutSlot();
		void adminSlot();
};




#endif /*GUI_INTERFACE_HPP*/