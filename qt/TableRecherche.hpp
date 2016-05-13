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
#include <string>
#include "SearchWidget.hpp"
#include "../database/Etablissement.hpp"
#include "CelluleRecherche.hpp"


class TableRecherche : public QTableWidget{
Q_OBJECT
	QWidget* _parent;
	std::vector<QLabel*> _currentTableItems;
	std::vector<Etablissement*> _etabs;
	void connectCells();
	void buildTable();
public:
	TableRecherche(std::vector<Etablissement*>,QWidget*);
		void initTable();
	 ~TableRecherche();
	//void initRows();
public slots:
	void goToEtabProfileSlot(int,int);
signals:
	void visitEtabSig(unsigned);
};

#endif /* TABLERECHERCHE_HPP */