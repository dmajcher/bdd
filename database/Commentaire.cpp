#include "Commentaire.hpp"


Commentaire::Commentaire(std::string auteur, std::string date, std::string texte, int score, int eidConcerne) {
	_auteur = auteur;
	_texte = texte;
	std::replace(_texte.begin(),_texte.end(),'\"','\'');
	_score = score;
	_date = date;
	_eidConcerne = eidConcerne;
}



int Commentaire::getCid() {return _CID;}

int Commentaire::getScore() {return _score;}

int Commentaire::getEidConcerne() {return _eidConcerne;}

std::string Commentaire::getTexte() {return _texte;}

std::string Commentaire::getAuteur() {return _auteur;}

std::string Commentaire::getDate() {return _date;}

void Commentaire::setCid(int cid) {_CID = cid;}

void Commentaire::setScore(int score) {_score = score;}

void Commentaire::setEidConcerne(int eid) {_eidConcerne = eid;}

void Commentaire::setText(std::string text) {
	_texte = text;
	std::replace(_texte.begin(),_texte.end(),'\"','\'');
}

void Commentaire::setAuteur(std::string auteur) {_auteur = auteur;}

void Commentaire::setDate(std::string date) {_date = date;}