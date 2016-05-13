#ifndef LOGINWIDGET_HPP
#define LOGINWIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>


class LogWidget: public QWidget {
	Q_OBJECT
	private:
		int _width;
		int _state;
		int _height;
		int _entryHeight;
		int _entryWidth;
		int _buttonWidth;
		QPushButton* _logButton;
		QPushButton* _cancelButton;
		QLineEdit* _pseudoEntry;
		QLineEdit* _passwordEntry;
		QLineEdit* _emailEntry = nullptr;

	public:
		LogWidget(int, int, int, QWidget*);
		void setLogStyle();
		void setSignStyle();
		void connectButtons();
		~LogWidget();

	public slots:
		void confirmSlot();
		void cancelSlot();

	signals:
		void canceled();

} ;





#endif /*LOGINWIDGET_HPP*/