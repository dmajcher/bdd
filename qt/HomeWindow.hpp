#ifndef HOME_WINDOW_HPP
#define HOME_WINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>


class HomeWindow: public QWidget {
	private:
		int _width;
		int _height;
        int _h;
        int _w;
		QWidget* _parent;
        QWidget* _icoWidget;
        QWidget* _panoWidget;

	public:
		HomeWindow(int, int, int, int, QWidget*);
        void setStyle();
        ~HomeWindow();


};


#endif /*HOME_WINDOW_HPP*/