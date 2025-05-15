#include <string>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur {

public:
	// Constructeur
	Joueur(string name);
	string getName();
	string getRole();
	string getPerso();
	int getHP();
	string getAbility();
	string getCarte(int i);
	int getHpMax();
	bool getStatut();
	int getBonusAttaque();
	list<string> getDeck();
	std::vector<std::vector<string>>& getCartePerma();
	std::vector<std::vector<string>>& getCarteAction();
	std::vector<std::vector<string>>& getCarteAttaque();
	int getPosition();
	int getPointHonneur();
	bool getBushido();
	void setRole(string role);
	void setPerso(string perso);
	void setHP(int hp);
	void setAbility(string ability);
	void setPointHonneur(int pts);
	void setPosition(int position);
	void setCarte(string name);
	void setHpMax(int hpMax);
	void setStatut(bool statut);
	void setBushido(bool statut);
	void removeCarte(string name);
	void moreBonusAttaque();
	void resetBonusAttaque();

private :
	int pts;
	string ability;
	int hp;
	string perso;
	string name;
	string role;
	int position;
	list<string> deck;
	std::vector<std::vector<string>> cartePerma;
	std::vector<std::vector<string>> carteAction;
	std::vector<std::vector<string>> carteAttaque;
	int hpMax;
	bool statut;
	int bonusAttaque;
	bool bushido;

};

#endif