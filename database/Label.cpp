#include "Label.hpp"


Label::Label(int lid, int poids) {
	_LID = lid;
	_poids = poids;
}

int Label::getLid() {return _LID;}

int Label::getNbEtab() {return _nbEtab;}

int Label::getPoids() {return _poids;}

int Label::getEid() {return _eid;}

std::vector<int> Label::getEidConcernes() {return _eidConcernes;}

std::vector<int> Label::getEidPoids() {return _eidPoids;}

std::string Label::getEtiquette() {return _etiquette;}

std::string Label::getAuteur() {return _auteur;}

void Label::setLid(int lid) {_LID = lid;}

void Label::setNbEtab(int nb) {_nbEtab = nb;}

void Label::setEidConcernes(std::vector<int> eids) {_eidConcernes = eids;}

void Label::setPoids(int poids) {_poids = poids;}

void Label::setEid(int eid) {_eid = eid;}

void Label::setEidPoids(std::vector<int> pds) {_eidPoids = pds;}

void Label::setEtiquette(std::string etiq) {_etiquette = etiq;}

void Label::setAuteur(std::string auteur) {_auteur = auteur;}