#ifndef CELLULELABEL_HPP
#define CELLULELABEL_HPP

#include <QWidget>
#include <QRect>
#include <QFont>
#include <QLabel>
#include <string>
#include <iostream>
#include <QString>
#include <QTextEdit>
#include "../database/Label.hpp"

class CelluleLabel: public QLabel{
Q_OBJECT
	QTextEdit* _etiquette;
	QLabel* _note;
	Label* _label;
	
	void initItem(int,int);
public:
	//unsigned int getEid();
	CelluleLabel(Label*,int,int,QWidget*);
	~CelluleLabel();

};

#endif /* CELLULELABEL_HPP */