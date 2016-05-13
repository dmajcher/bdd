#ifndef USERPROFILEPAGE_HPP
#define USERPROFILEPAGE_HPP

#include <QRect>
#include <QDesktopWidget>
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QListView>
#include <QGridLayout>
#include <QString>
#include <QPixmap>
#include <string>
#include <iostream>
#include <unistd.h>
#include "TableCommentaire.hpp"
#include "../database/Commentaire.hpp"
#include "../database/DataBase.hpp"
#include "../database/User.hpp"
#include "SearchWidget.hpp"

class UserProfilePage: public QWidget {
	Q_OBJECT

	int _width,_height;
	QWidget* _parent;
	TableCommentaire* _commentTable =nullptr;
	std::string _requestCom;
	DataBase* _db;

	User* _user;

	QPushButton* _returnButton;
	
	QLabel* _mainLabel;
	QLabel* _logo;
	QLabel* _name;
	QLabel* _date;
	QLabel* _email;
	QLabel* _admin;
	QLabel* _siteIco;

	void fillPage();
	void initPage();
	void connectButton();
	void makeCommentTable();
public:
	UserProfilePage(std::string,DataBase*,int,int, QWidget*);
	void setStyle();
	 ~UserProfilePage();
public slots:
	void returnSlot();
	//void searchSlot();
signals:
	void canceled();
	//void goBackToMenuSig();
};


#endif // USERPROFILEPAGE_HPP
