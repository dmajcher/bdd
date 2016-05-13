#include "LogWidget.hpp"


LogWidget::LogWidget(int width, int height, int state, QWidget* parent) : QWidget(parent){
	_width = width;
	_height = height;
	_state = state;
	_entryWidth = _width/8;
	_entryHeight = _height/30;
	_buttonWidth = _width/10;
	this->resize(_width, _height);
	_pseudoEntry = new QLineEdit(this);
	_passwordEntry = new QLineEdit(this);
	_logButton = new QPushButton(this);
	_cancelButton = new QPushButton(this);
	parent->setStyleSheet("background : url(../qt/Images/wood.jpg)");
	_pseudoEntry->setFont(QFont("URW Gothic L", 12));
	_passwordEntry->setFont(QFont("URW Gothic L", 12));
	_cancelButton->setFont(QFont("URW Gothic L", 12));
	_logButton->setFont(QFont("URW Gothic L", 12));

	_pseudoEntry->setGeometry(_width/2 - _entryWidth/2, _height/3 + (2*_entryHeight), _entryWidth, _entryHeight);
	_passwordEntry->setGeometry(_width/2 - _entryWidth/2, _height/3 + (4*_entryHeight), _entryWidth, _entryHeight);
	_logButton->setGeometry(_width/2 - _buttonWidth/2, _height/3 + (6*_entryHeight), _buttonWidth, _height/20);
	_cancelButton->setGeometry(_width - _buttonWidth - _height/20, _height-_buttonWidth/2, _buttonWidth, _height/20);
	_cancelButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	_logButton->setStyleSheet("QPushButton::hover{background : lightgrey} QPushButton{background : rgba(255,255,255,180) ; border-radius : 5px}");
	if (_state == 2)
		setSignStyle();
	else
		setLogStyle();
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



void LogWidget::connectButtons() {
	connect(_logButton, SIGNAL(clicked()), this, SLOT(confirmSlot()));
}


void LogWidget::~LogWidget() {
	delete _pseudoEntry;
	delete _passwordEntry;
	delete _logButton;
	delete _entryWidth;
	delete _cancelButton;
	delete _emailEntry;
}