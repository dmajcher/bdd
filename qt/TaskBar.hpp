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
		QPushButton* _adminButton = nullptr;

	public: 
		TaskBar(int, int, QWidget*);
		void connectButtons();
		void setWidgetStyle();
		void hideSign();
		void hideLog();
		void showButtons();
		void setStatusLogged();
		void setAdminTools();

	public slots:
		void loginSlot();
		void signinSlot();
		void logOutSlot();
		void adminManageSlot();

	signals:
		void loginSig();
		void signinSig();
		void logoutSig();
		void adminSig();

};




#endif /*TASKBAR_HPP*/