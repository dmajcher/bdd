#ifndef PROFILEPAGE_HPP
#define PROFILEPAGE_HPP

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
#include "TableLabel.hpp"
#include "../database/Commentaire.hpp"
#include "../database/Label.hpp"
#include "../database/DataBase.hpp"
#include "SearchWidget.hpp"
#include "../database/Etablissement.hpp"
#include "../database/Restaurant.hpp"
#include "../database/Hotel.hpp"
#include "../database/Bar.hpp"

class ProfilePage: public QWidget {
	Q_OBJECT

	int _width,_height;
	QWidget* _parent;
	TableCommentaire* _commentTable =nullptr;
	TableLabel* _labelTable=nullptr;
	std::string _requestCom;
	DataBase* _db;

	Etablissement* _etab;
	Restaurant* _resto;
	Bar* _bar;
	Hotel* _hotel;

	QPushButton* _returnButton;
	
	QLabel* _mainLabel;
	QLabel* _logo;
	QLabel* _name;
	QLabel* _score;
	QLabel* _site;
	QLabel* _siteIco;
	QLabel* _tel;
	QLabel* _telIco;
	QLabel* _adress;
	QLabel* _adressIco;
	QLabel* _latlong;

	QLabel* _petiteResto;
	QLabel* _petiteRestoIco;
	QLabel* _fumeur;

	QLabel* _priceIco;
	QLabel* _price;
	QLabel* _deliveryIco;
	QLabel* _takeAwayIco;
	QLabel* _takeAway;
	QLabel* _horraireIco;
	QLabel* _horraire;
	QLabel* _seatsIco;
	QLabel*	_seats;


	void fillLabel();
	void initPage();
	void connectButton();
	void makeCommentTable();
	void makeLabelTable();
public:
	ProfilePage(unsigned,DataBase*,int,int, QWidget*);
	void setStyle();
	 ~ProfilePage();
public slots:
	void returnSlot();
	void slot(std::string);
	//void searchSlot();
signals:
	void canceled();
	void sig(std::string);
	//void goBackToMenuSig();
};


#endif // PROFILEPAGE_HPP
