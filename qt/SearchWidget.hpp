#ifndef SEARCHWIDGET_HPP
#define SEARCHWIDGET_HPP

#include <QLineEdit>
#include <QWidget>
#include <QPushButton>
#include <QCheckBox>


class SearchWidget: public QWidget {
	private:
		int _width;
		int _height;
		int _thisWidth;
		int _thisHeight;
		int _borderSize;
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
};


#endif /*SEARCHWIDGET_HPP*/