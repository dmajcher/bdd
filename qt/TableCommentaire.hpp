#ifndef TABLECOMMENATAIRE_HPP
#define TABLECOMMENATAIRE_HPP

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
#include "../database/Commentaire.hpp"
#include "CelluleCommentaire.hpp"


class TableCommentaire : public QTableWidget{
Q_OBJECT
	QWidget* _parent;
	std::vector<QLabel*> _currentTableItems;
	std::vector<Commentaire*> _comments;
	void connectCells();
	void buildTable();
public:
	TableCommentaire(std::vector<Commentaire*>,QWidget*);
		void initTable();
	 ~TableCommentaire();
	//void initRows();
public slots:
	void goToEtabProfileSlot(int,int);
signals:
	void visitEtabSig(unsigned);
};

#endif /* TABLECOMMENATAIRE_HPP */