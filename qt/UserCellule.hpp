#ifndef USERCELLULE_HPP
#define USERCELLULE_HPP

#include <QWidget>
#include <QRect>
#include <QFont>
#include <QLabel>
#include <string>
#include <iostream>
#include <QString>
#include <QTextEdit>
#include "../database/Commentaire.hpp"

class UserCellule: public QLabel{
Q_OBJECT
	
	Commentaire* _comment;
	QTextEdit* _text;
	QLabel* _note;
	QLabel* _etab;
	QLabel* _date;
	
	void initItem(int,int);
public:
	//unsigned int getEid();
	UserCellule(Commentaire*,int,int,QWidget*);
	~UserCellule();

};

#endif /* USERCELLULE_HPP */