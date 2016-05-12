#ifndef SEARCHWIDGET_HPP
#define SEARCHWIDGET_HPP

#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <iostream>
#include <string>


class SearchWidget: public QWidget {
	Q_OBJECT
	private:
		int _width;
		int _height;
		int _thisWidth;
		int _thisHeight;
		int _borderSize;
		int _checkSize;
		QWidget* _parent;
		QLineEdit* _searchEntry;
		QPushButton* _searchButton;
		QCheckBox* _hotelCheck;
		QCheckBox* _barCheck;
		QCheckBox* _restoCheck;

	public:
		SearchWidget(int, int, QWidget*);
		void setWidgetsPosition();
		void setWidgetsStyle();
		void connectWidgets();

	public slots:
		void searchSlot();
		void entrySlot();

	signals:
		void searchSig(std::string);
};


#endif /*SEARCHWIDGET_HPP*/