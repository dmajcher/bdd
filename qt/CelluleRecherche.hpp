#ifndef CELLULERECHERCHE_HPP
#define CELLULERECHERCHE_HPP

#include <QWidget>
#include <QRect>
#include <QFont>
#include <QLabel>
#include <string>
#include <iostream>
#include <QString>
#include "../database/Etablissement.hpp"
#include "../database/Restaurant.hpp"
#include "../database/Hotel.hpp"
#include "../database/Bar.hpp"

class CelluleRecherche: public QLabel{
Q_OBJECT
	QLabel* _pictureFrame;
	QLabel* _estabName;
	QLabel* _localite;
	QLabel* _score;
	Etablissement* _etab;
	Restaurant* _resto;
	Bar* _bar;
	Hotel* _hotel;
	void initItem(int,int);
public:
	unsigned int getEid();
	CelluleRecherche(Etablissement*,int,int,QWidget*);
	~CelluleRecherche();

};

#endif /* CELLULERECHERCHE_HPP */