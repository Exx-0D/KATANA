#include "joueur.h"
#include <string>
#include <list>

using namespace std;

Joueur::Joueur(string name)
{
	this->name = name;
}

string Joueur::getName()
{
	return this->name;
}

string Joueur::getRole()
{
	return this->role;
}

string Joueur::getPerso()
{
	return this->perso;
}

string Joueur::getAbility()
{
	return this->ability;
}

string Joueur::getCarte(int i)
{
	auto it = next(this->deck.begin(), i); // Obtenir l'itérateur pointant vers l'élément
	string name = *it; // Accéder à la valeur de l'élément
	return name;
}

int Joueur::getHpMax()
{
	return this->hpMax;
}

list<string> Joueur::getDeck()
{
	return this->deck;
}

std::vector<std::vector<string>>& Joueur::getCartePerma()
{
	return this->cartePerma;
}

std::vector<std::vector<string>>& Joueur::getCarteAction()
{
	return this->carteAction;
}

std::vector<std::vector<string>>& Joueur::getCarteAttaque()
{
	return this->carteAttaque;
}

int Joueur::getPosition()
{
	return this->position;
}

int Joueur::getHP()
{
	return this->hp;
}

int Joueur::getPointHonneur()
{
	return this->pts;
}

bool Joueur::getBushido()
{
	return this->bushido;
}

bool Joueur::getStatut()
{
	return this->statut;
}

int Joueur::getBonusAttaque()
{
	return this->bonusAttaque;
}

void Joueur::setRole(string role)
{
	this->role = role;
}

void Joueur::setPerso(string perso)
{
	this->perso = perso;
}

void Joueur::setAbility(string ability)
{
	this->ability = ability;
}

void Joueur::setHP(int hp)
{
	this->hp = hp;
}

void Joueur::setPointHonneur(int pts)
{
	this->pts = pts;
}

void Joueur::setPosition(int position)
{
	this->position = position;
}

void Joueur::setCarte(string name)
{
	this->deck.push_back(name);
}

void Joueur::setHpMax(int hpMax)
{
	this->hpMax = hpMax;
}

void Joueur::setStatut(bool statut)
{
	this->statut = statut;
}

void Joueur::setBushido(bool statut)
{
	this->bushido = statut;
}

void Joueur::removeCarte(string name)
{
	int i = 0;
	for (const auto& element : this->deck) 
	{
		if (element == name)
		{
			auto it = next(this->deck.begin(), i); // Obtenir l'itérateur pointant vers l'élément
			this->deck.erase(it); // Supprimer l'élément à la position spécifiée
			break;
		}
		i += 1;
	}
}

void Joueur::moreBonusAttaque()
{
	this->bonusAttaque += 1;
}

void Joueur::resetBonusAttaque()
{
	this->bonusAttaque = 0;
}

