#include "Commentaire.hpp"


Commentaire::Commentaire(std::string auteur, std::string texte, int score, int eidConcerne) {
	_auteur = auteur;
	_texte = texte;
	_score = score;
	_eidConcerne = eidConcerne;
}



int Commentaire::getCid() {return _CID;}

int Commentaire::getScore() {return _score;}

int Commentaire::getEidConcerne() {return _eidConcerne;}

std::string Commentaire::getTexte() {return _texte;}

std::string Commentaire::getAuteur() {return _auteur;}

void Commentaire::setCid(int cid) {_CID = cid;}

void Commentaire::setScore(int score) {_score = score;}

void Commentaire::setEidConcerne(int eid) {_eidConcerne = eid;}

void Commentaire::setText(std::string text) {_texte = text;}

void Commentaire::setAuteur(std::string auteur) {_auteur = auteur;}