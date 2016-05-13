#ifndef CELLULECOMMEBTAIRE_HPP
#define CELLULECOMMEBTAIRE_HPP

#include <QWidget>
#include <QRect>
#include <QFont>
#include <QLabel>
#include <QPushButton>
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
	QPushButton* _auteur;
	QLabel* _date;

	Commentaire* _comment;
	
	void initItem(int,int);
	void connectButton();
public:
	//unsigned int getEid();
	CelluleCommentaire(Commentaire*,int,int,QWidget*);
	~CelluleCommentaire();
public slots:
	void slot();
signals:
	void sig(std::string);

};

#endif /* CELLULECOMMEBTAIRE_HPP */