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
#include "../database/Commentaire.hpp"
//#include "../database/Label.hpp"
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
	//TableCommentaire* _commentaireTable=nullptr;
	//TableLabels* _labelsTable=nullptr;
	std::vector<Commentaire*> commentsVect;
	//std::vector<Label*> LabelsVect;
	std::string _requestCom;
	DataBase* _db;

	Etablissement* _etab;
	Restaurant* _resto;
	Bar* _bar;
	Hotel* _hotel;

	QPushButton* LabelsButton;
	QPushButton* CommentsButton;
	
	QLabel* _mainLabel;
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


	void fillLabel();
	void initPage();
	void connectButtons();
	void makeCommentTable();
public:
	ProfilePage(unsigned,DataBase*,int,int, QWidget*);
	void setStyle();
	 ~ProfilePage();
public slots:
	//void makeCommentsTableSlot();
	//void makeLabelsTableSlot();
	//void searchSlot();
signals:
	//void goBackToMenuSig();
};


#endif // PROFILEPAGE_HPP
