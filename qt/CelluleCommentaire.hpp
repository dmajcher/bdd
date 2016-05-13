#ifndef CELLULECOMMEBTAIRE_HPP
#define CELLULECOMMEBTAIRE_HPP

#include <QWidget>
#include <QRect>
#include <QFont>
#include <QLabel>
#include <string>
#include <iostream>
#include <QString>
#include <QTextEdit>
#include "../database/Commentaire.hpp"

class CelluleCommentaire: public QLabel{
Q_OBJECT
	QLabel* _pictureFrame;
	QTextEdit* _text;
	QLabel* _note;
	QLabel* _auteur;
	QLabel* _date;

	Commentaire* _comment;
	
	void initItem(int,int);
public:
	//unsigned int getEid();
	CelluleCommentaire(Commentaire*,int,int,QWidget*);
	~CelluleCommentaire();

};

#endif /* CELLULECOMMEBTAIRE_HPP */