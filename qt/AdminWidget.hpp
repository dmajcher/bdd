#ifndef ADMIN_WIDGET_HPP
#define ADMIN_WIDGET_HPP


#include <string>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include "../database/DataBase.hpp"


class AdminWidget: public QWidget {
	Q_OBJECT
	private:
		int _width;
		int _height;
		int _buttonWidth;
		int _buttonHeight;
		int _entryWidth;
		int _entryHeight;
		std::string _kind;
		DataBase* _db;
		User* _user;
		QWidget* _parent;
		QPushButton* _addRestoButton;
		QPushButton* _addHotelButton;
		QPushButton* _addBarButton;	
		QPushButton* _okButton= nullptr;
		QPushButton* _confirmButton= nullptr;
		QLineEdit* _nomEtab = nullptr;
		QLineEdit* _adresseEtab= nullptr;
		QLineEdit* _localiteEtab= nullptr;
		QLineEdit* _numTelEtab= nullptr;
		QLineEdit* _siteEtab= nullptr;
		QLineEdit* _latitudeEtab= nullptr;
		QLineEdit* _longitEtab= nullptr;
		QCheckBox* _fumeur= nullptr;
		QCheckBox* _peiteResto= nullptr;
		QLineEdit* _nbPlaces= nullptr;
		QCheckBox* _livraison= nullptr;
		QCheckBox* _takeAway= nullptr;
		QLineEdit* _prixPlats= nullptr;
		QLineEdit* _indicePrix= nullptr;
		QLineEdit* _etoiles= nullptr;
		QLineEdit* _chambres= nullptr;
		Restaurant* _newResto = nullptr;
		Bar* _newBar = nullptr;
		Hotel* _newHotel = nullptr;

	public:
		AdminWidget(int, int, DataBase*, User*, QWidget*);	
		void connectButtons();
		void askEtabInfos();
		void hideButtons();
		void hotelSlot();
		void barSlot();
		void restoSlot();

	public slots:
		void addBarSlot();
		void addHotelSlot();
		void addRestoSlot();
		void okSlot();




};




#endif /*ADMIN_WIDGET_HPP*/