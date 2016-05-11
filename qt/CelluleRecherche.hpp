#ifndef CELLULERECHERCHE_HPP
#define CELLULERECHERCHE_HPP

#include <QWidget>
#include <QRect>
#include <QFont>
#include <QLabel>
#include <iostream>
#include <QString>
#include "../Etablissement.hpp"
#include "../Restaurant.hpp"
#include "../Hotel.hpp"
#include "../Bar.hpp"

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