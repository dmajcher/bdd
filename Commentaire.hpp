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
		std::string _date;

	public:
		Commentaire(std::string, std::string, std::string, int, int eidConcerne = -1);
		int getCid();
		int getScore();
		int getEidConcerne();
		std::string getTexte();
		std::string getAuteur();
		std::string getDate();
		void setCid(int);
		void setScore(int);
		void setEidConcerne(int);
		void setText(std::string);
		void setAuteur(std::string);
		void setDate(std::string);

};





#endif /* COMMENTAIRE_HPP */