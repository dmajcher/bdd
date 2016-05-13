#ifndef TASKBAR_HPP
#define TASKBAR_HPP


#include <QWidget>
#include <QFont>
#include <QPushButton>


class TaskBar: public QWidget {
	Q_OBJECT
	private:
		int _width;
		int _height;
		int _buttonWidth;
		QWidget* _parent;
		QPushButton* _signinButton;
		QPushButton* _loginButton;

	public: 
		TaskBar(int, int, QWidget*);
		void connectButtons();
		void setWidgetStyle();
		void hideSign();
		void hideLog();
		void showButtons();
		void setStatusLogged();

	public slots:
		void loginSlot();
		void signinSlot();
		void logOutSlot();

	signals:
		void loginSig();
		void signinSig();

};




#endif /*TASKBAR_HPP*/