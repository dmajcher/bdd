#include "LogWidget.hpp"


LogWidget::LogWidget(int width, int height, int state, DataBase* db, QWidget* parent) : QWidget(parent){
	_width = width;
	_height = height;
	_state = state;
	_entryWidth = _width/8;
	_entryHeight = _height/30;
	_buttonWidth = _width/10;
	_database = db;
	this->resize(_width, _height);
	_pseudoEntry = new QLineEdit(this);
	_passwordEntry = new QLineEdit(this);
	_logButton = new QPushButton(this);
	_cancelButton = new QPushButton(this);
	_errorText = new QLabel(this);
	parent->setStyleSheet("background : url(../qt/Images/wood.jpg)");
	_pseudoEntry->setFont(QFont("URW Gothic L", 12));
	_passwordEntry->setFont(QFont("URW Gothic L", 12));
	_cancelButton->setFont(QFont("URW Gothic L", 12));
	_logButton->setFont(QFont("URW Gothic L", 12));
	_errorText->setFont(QFont("URW Gothic L", 10));
	_errorText->setGeometry(_width/2 - _entryWidth/2,  _height/3 - _entryHeight, _entryWidth, _entryHeight);
	_pseudoEntry->setGeometry(_width/2 - _entryWidth/2, _height/3 + (2*_entryHeight), _entryWidth, _entryHeight);
	_passwordEntry->setGeometry(_width/2 - _entryWidth/2, _height/3 + (4*_entryHeight), _entryWidth, _entryHeight);
	_logButton->setGeometry(_width/2 - _buttonWidth/2, _height/3 + (6*_entryHeight), _buttonWidth, _height/20);
	_cancelButton->setGeometry(_width - _buttonWidth - _height/20, _height-_buttonWidth/2, _buttonWidth, _height/20);
	_cancelButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_logButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_errorText->setStyleSheet("background : transparent; color : red");
	_passwordEntry->setEchoMode(QLineEdit::Password);
	if (_state == 2)
		setSignStyle();
	else
		setLogStyle();
	connectButtons();
	raise();
	show();
}


void LogWidget::setSignStyle() {
	_emailEntry = new QLineEdit(this);
	_logButton->setText("Confirmer");
	_cancelButton->setText("Annuler");
	_passwordEntry->setPlaceholderText("Mot de passe");
	_emailEntry->setPlaceholderText("Email");
	_pseudoEntry->setPlaceholderText("Pseudonyme");
	_emailEntry->setFont(QFont("URW Gothic L", 12));
	_emailEntry->setGeometry(_width/2 - _entryWidth/2, _height/3, _entryWidth, _entryHeight);

}


void LogWidget::setLogStyle() {
	_logButton->setText("Valider");
	_cancelButton->setText("Annuler");
	_passwordEntry->setPlaceholderText("Mot de passe");
	_pseudoEntry->setPlaceholderText("Pseudonyme ou email");
}


void LogWidget::confirmSlot() {
	std::string pseudo = _pseudoEntry->text().toStdString();
	std::string password = _passwordEntry->text().toStdString();
	if (_state == 2) {
		std::string email = _emailEntry->text().toStdString();
		if (pseudo == "" || password == "" || email == "") { 
			_errorText->move(_width/2 - _entryWidth/2,  _height/3 - _entryHeight);
			_errorText->setText("Pseudonyme, password ou email vide");
			_errorText->raise();
			_errorText->show();
		}
		else {
			User newUser(pseudo, password, email, 160511, false);
			int check = _database->addUser(newUser);
			if (check) {
				_pseudoEntry->clear();
				_emailEntry->clear();
				_errorText->move(_width/2 - _entryWidth/2,  _height/3 - _entryHeight);
				_errorText->setText("Pseudonyme ou email déjà utilisé");
				_errorText->raise();
				_errorText->show();
			}
			else {
				_user = &newUser;
				emit logSig();
			}
		}
	}
	else {
		std::string gu = "\"";
		if (pseudo == "" || password == "") {
			_errorText->move(_width/2 - _entryWidth/2,  _pseudoEntry->y() - _entryHeight);
			_errorText->setText("Nom ou mot de passe vide");
			_errorText->raise();
			_errorText->show();
		}
		else {
			std::string cond = "(Email = "+gu+pseudo+gu+" OR NameId = "+gu+pseudo+gu+") AND Password = "+gu+password+gu;
			User meUser = _database->getUserByCond(cond); 
			std::cout<<meUser.getName();
			if (meUser.getName() == "") {
				_errorText->move(_width/2 - _entryWidth/2,  _pseudoEntry->y() - _entryHeight);
				_errorText->setText("Nom ou mot de passe invalide");
				_errorText->raise();
				_errorText->show();
			}
			else {
				_user = &meUser;
				emit logSig();
			}
		}
	}
}


void LogWidget::cancelSlot() {
	emit canceled();
}


void LogWidget::connectButtons() {
	connect(_logButton, SIGNAL(clicked()), this, SLOT(confirmSlot()));
	connect(_cancelButton, SIGNAL(clicked()), this, SLOT(cancelSlot()));
}

User* LogWidget::getCurrentUser() {
	return _user;
}


LogWidget::~LogWidget() {
	delete _pseudoEntry;
	delete _passwordEntry;
	delete _logButton;
	delete _cancelButton;
	delete _emailEntry;
	delete _errorText;
}