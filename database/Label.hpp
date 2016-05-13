#ifndef LABEL_HPP
#define LABEL_HPP


#include <string>
#include <vector>


class Label {
	private:
		std::string _etiquette;
		int _nbEtab;
		int _LID;
		std::vector<int> _eidConcernes;
		std::vector<int> _eidPoids;
		std::string _auteur;
		int _eid = -1;
		int _poids = -1;

	public:
		Label(int, int);
		int getLid();
		int getNbEtab();
		int getEid();
		int getPoids();
		std::vector<int> getEidConcernes();
		std::vector<int> getEidPoids();
		std::string getAuteur();
		std::string getEtiquette(); 
		void setLid(int);
		void setNbEtab(int);
		void setEidConcernes(std::vector<int>);
		void setEidPoids(std::vector<int>);
		void setEid(int);
		void setPoids(int);
		void setEtiquette(std::string);
		void setAuteur(std::string);

};


#endif /*LABEL_HPP*/ 