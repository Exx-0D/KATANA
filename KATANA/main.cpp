#include <iostream>
#include "jeu.h"
#include <Windows.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	int nbJoueur = nb_joueur();
	start(nbJoueur);
	role_create(nbJoueur);
	role_destiny(nbJoueur);
	position(nbJoueur);
	perso_destiny(nbJoueur);
	distrib_point_honneur(nbJoueur);
	what_role(nbJoueur);
	pioche_generation();
	distribution(nbJoueur);
	firstStats(nbJoueur);
	while (1 == 1)
	{
		tour(nbJoueur);
	}


}

