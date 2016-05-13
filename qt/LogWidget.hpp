#ifndef LOGINWIDGET_HPP
#define LOGINWIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "../database/DataBase.hpp"


class LogWidget: public QWidget {
	Q_OBJECT
	private:
		int _width;
		int _state;
		int _height;
		int _entryHeight;
		int _entryWidth;
		int _buttonWidth;
		User* _user = nullptr;
		DataBase* _database;
		QPushButton* _logButton;
		QPushButton* _cancelButton;
		QLineEdit* _pseudoEntry;
		QLineEdit* _passwordEntry;
		QLineEdit* _emailEntry = nullptr;
		QLabel* _errorText;

	public:
		LogWidget(int, int, int, DataBase*, QWidget*);
		void setLogStyle();
		void setSignStyle();
		void connectButtons();
		User* getCurrentUser();
		~LogWidget();

	public slots:
		void confirmSlot();
		void cancelSlot();

	signals:
		void canceled();
		void logSig();

} ;





#endif /*LOGINWIDGET_HPP*/