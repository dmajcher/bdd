#include "Bar.hpp"



Bar::Bar(bool isFumeur, bool petiteResto) {
    _fumeur = isFumeur;
    _petiteRestaur = petiteResto;
}
bool Bar::isFumeur(){return _fumeur;}
bool Bar::hasPetiteResto(){return _petiteRestaur;}
void Bar::setFumeur(bool isFumeur) {
    _fumeur = isFumeur;
}
void Bar::setPetiteResto(bool petiteResto){
    _petiteRestaur = petiteResto;
}