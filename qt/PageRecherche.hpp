#ifndef PAGERECHERCHE_HPP
#define PAGERECHERCHE_HPP

#include <QRect>
#include <QDesktopWidget>
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QListView>
#include <QGridLayout>
#include <QString>
#include <string>
#include <iostream>
#include "TableRecherche.hpp"
#include "../database/DataBase.hpp"
#include "SearchWidget.hpp"

class PageRecherche: public QWidget {
	Q_OBJECT

	std::vector<std::string> _establishmentList;
	int _width,_height;
	QWidget* _parent;
	TableRecherche* _searchTable;
	SearchWidget* _searchEntry =nullptr;
	DataBase* _db;

	void initPage();
	//void showWindow();
	void connectEntry();
	void connectButtons();
	//void connectFriendAndSearch();
	//void connectChangeUser();
	//void makeTableFriendAndSearch(unsigned);

public:
	PageRecherche(DataBase*, std::string,int,int, QWidget*,SearchWidget*);
	//void keyPressEvent(QKeyEvent*);
	 ~PageRecherche();
public slots:
	void makeSearchTableSlot(std::string);
	//void searchSlot();
signals:
	//void changeUserSig(unsigned int);
	//void goBackToMenuSig();
};


#endif // PAGERECHERCHE_HPP
