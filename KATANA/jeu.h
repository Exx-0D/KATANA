#include <string>
#include <vector>

#ifndef HEADER_FONCTION
#define HEADER_FONCTION
#define TAILLE 7

int nb_joueur();
void start(int nb_joueur);
void role_create(int nb_joueur);
void role_destiny(int nb_joueur);
void position(int nb_joueur);
void changeStatut(int i);
void perso_destiny(int nb_joueur);
void distrib_point_honneur(int nb_joueur);
void what_role(int nb_joueur);
void pioche_generation();
void piocheCarte(int i);
void distribution(int nb_joueur);
void deck(int i);
void stats(int i);
void firstStats(int nb_joueur);
void recuperation(int i);
int distance(int i, std::string joueur1, std::string joueur2);
void piocheVide();
void pioche2Cartes(int i);
void impactBushido(int i);
void detailByName(std::string name);
void affichePerma(int i);
void tour(int nb_joueur);
bool inDeck(int i, std::string carte);
std::string typeByName(std::string name);
bool attaqueIn(int i);
bool joueurInGame(std::string name);
bool joueurCiblable(std::string name);
int cibleValide(std::string cible, std::string carte);
int verifBushido();
int precisionByName(std::string name);
int attaqueByName(std::string name);
void choixAttaque(int i, int nb_joueur);
void attBushido(std::string name);
void criDeGuerre(int i, int nb_joueur);
void daimyo(int i);
void diversion(int i, std::string cible, int nb_joueur);
int getPosByName(std::string name, int nb_joueur);
void geisha(int i, std::string cible, int nb_joueur);
void meditation(int i, std::string cible, int nb_joueur);
void ceremonie(int i, int nb_joueur);
void jujitsu(int i);
void attaque(int i, int nb_joueur);
void phaseDefausse(int i);
void verifDaimyo(int i);
void victoireEpe(std::string attaquant, std::string cible, int nb_joueur);
void finGame(std::string attaquant, std::string cible, int nb_joueur);



#endif
