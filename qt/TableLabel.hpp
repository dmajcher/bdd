#ifndef TABLELABEL_HPP
#define TABLELABEL_HPP

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
#include "../database/Label.hpp"
#include "CelluleLabel.hpp"


class TableLabel : public QTableWidget{
Q_OBJECT
	QWidget* _parent;
	std::vector<QLabel*> _currentTableItems;
	std::vector<Label*> _labels;
	void connectCells();
	void buildTable();
public:
	TableLabel(std::vector<Label*>,QWidget*);
		void initTable();
	 ~TableLabel();
	//void initRows();
public slots:
	//void goToEtabProfileSlot(int,int);
signals:
	//void visitEtabSig(unsigned);
};

#endif /* TABLELABEL_HPP */