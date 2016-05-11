#ifndef HOME_WINDOW_HPP
#define HOME_WINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>


class HomeWindow: public QWidget {
	private:
		int _width;
		int _height;
		QWidget* _parent;
		QLineEdit* _searchBar;

	public:
		HomeWindow(int, int, QWidget*);


};


#endif /*HOME_WINDOW_HPP*/