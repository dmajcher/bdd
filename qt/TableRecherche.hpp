#ifndef TABLERECHERCHE_HPP
#define TABLERECHERCHE_HPP

#include <QWidget>
#include <QTableWidget>
#include <QRect>
#include <QFont>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <vector>
#include <QLabel>
#include <iostream>
#include "SearchWidget.hpp"
#include "../database/Etablissement.hpp"
#include "CelluleRecherche.hpp"


class TableRecherche : public QTableWidget{
Q_OBJECT
	QWidget* _parent;
	std::vector<QLabel*> _currentTableItems;
	std::vector<Etablissement*> _etabs;
	void initTable();
	void connectCells();
	void buildTable();
public:
	TableRecherche(std::vector<Etablissement*>,QWidget*);
	 ~TableRecherche();
	//void initRows();
public slots:
	void goToEtabProfileSlot(int,int);
signals:
	void deleteTextOrEntrySig();
	void changeUserSig(unsigned);
};

#endif /* TABLERECHERCHE_HPP */