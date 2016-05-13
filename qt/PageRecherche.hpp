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
#include <unistd.h>
#include "TableRecherche.hpp"
#include "../database/DataBase.hpp"
#include "SearchWidget.hpp"

class PageRecherche: public QWidget {
	Q_OBJECT

	std::vector<std::string> _establishmentList;
	int _width,_height;
	QWidget* _parent;
	TableRecherche* _searchTable=nullptr;
	SearchWidget* _searchEntry =nullptr;
	DataBase* _db;

	void initPage();
	//void showWindow();
	void connectEntry();
	void connectButtons();
	void connectEtabVisit();
	//void connectChangeUser();
	//void makeTableFriendAndSearch(unsigned);

public:
	PageRecherche(DataBase*, std::string,int,int, QWidget*);
	void setStyle();
	//void keyPressEvent(QKeyEvent*);
	 ~PageRecherche();
public slots:
	void makeSearchTableSlot(std::string);
	void makeEtabProfileSlot(unsigned);
	//void searchSlot();
signals:
	void profileSig(unsigned);
};


#endif // PAGERECHERCHE_HPP
