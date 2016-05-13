#include "TaskBar.hpp"



TaskBar::TaskBar(int width, int height, QWidget* parent) : QWidget(parent) {
	_width = width;
	_height = height;
	_buttonWidth = _width/10;
	_parent = parent;
	_signinButton = new QPushButton(this);
	_loginButton = new QPushButton(this);
	setWidgetStyle();
	connectButtons();
}



void TaskBar::setWidgetStyle() {
	_signinButton->setText("Créer un compte");
	_loginButton->setText("Se connecter");
	this->setGeometry(0, 0, _width, _height/10);
	_loginButton->setGeometry(_width-(_buttonWidth*2) - _buttonWidth/2, _height/40, _buttonWidth, _height/20);
	_signinButton->setGeometry(_loginButton->x() + _buttonWidth+_buttonWidth/4, _height/40, _buttonWidth, _height/20);
	this->setStyleSheet("transparent");
	_loginButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_signinButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_loginButton->setFont(QFont("URW Gothic L", 13));
	_signinButton->setFont(QFont("URW Gothic L", 13));
}



void TaskBar::adminManageSlot() {
	emit adminSig();
}


void TaskBar::setAdminTools() {
	_adminButton = new QPushButton(this);
	_adminButton->setGeometry(_loginButton->x() + _buttonWidth+_buttonWidth/4 - _height/10, _height/40, _height/20, _height/20);
	_adminButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_adminButton->setIcon(QIcon("../qt/Images/settings.png"));
	_adminButton->raise();
	_adminButton->show();
	connect(_adminButton, SIGNAL(clicked()), this, SLOT(adminManageSlot()));
}


void TaskBar::hideSign() {
	_signinButton->hide();
	_loginButton->show();
}


void TaskBar::hideLog() {
	_loginButton->hide();
	_signinButton->show();
}

void TaskBar::showButtons() {
	_loginButton->raise();
	_signinButton->raise();
	_loginButton->show();
	_signinButton->show();
}


void TaskBar::loginSlot() {
	emit loginSig();
}

void TaskBar::signinSlot() {
	emit signinSig();
}


void TaskBar::logOutSlot() {
	delete _adminButton;
	_signinButton->setText("Créer un compte");
	disconnect(_signinButton, SIGNAL(clicked()), this, SLOT(logOutSlot()));
	showButtons();
	connectButtons();
	emit logoutSig();
}


void TaskBar::setStatusLogged() {
	hideLog();
	_signinButton->setText("Se déconnecter");
	disconnect(_signinButton, SIGNAL(clicked()), this, SLOT(signinSlot()));
	disconnect(_loginButton,SIGNAL(clicked()), this, SLOT(loginSlot()));
	connect(_signinButton, SIGNAL(clicked()), this, SLOT(logOutSlot()));
	_signinButton->raise();
}



void TaskBar::connectButtons() {
	connect(_signinButton, SIGNAL(clicked()), this, SLOT(signinSlot()));
	connect(_loginButton, SIGNAL(clicked()), this, SLOT(loginSlot()));
}