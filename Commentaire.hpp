#ifndef COMMENTAIRE_HPP
#define COMMENTAIRE_HPP


#include <string>


class Commentaire {
	private:
		int _CID;
		int _score;
		int _eidConcerne;
		std::string _texte;
		std::string _auteur;

	public:
		Commentaire(std::string, std::string, int, int);
		int getCid();
		int getScore();
		int getEidConcerne();
		std::string getTexte();
		std::string getAuteur();
		void setCid(int);
		void setScore(int);
		void setEidConcerne(int);
		void setText(std::string);
		void setAuteur(std::string);

};





#endif /* COMMENTAIRE_HPP */