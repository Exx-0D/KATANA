#include "jeu.h"
#include "joueur.h"
#include "role.h"
#include "pioche.h"
#include <string>
#include <iostream>
#include <random>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

#define NBCARTE 25


int nb_joueur()
{
	int nbJoueur;
	cout << u8"Une partie nécessite entre 4 et 7 joueurs" << endl << "Nombre de joueurs de la partie : ";
	cin >> nbJoueur;
	return nbJoueur;
}

vector<Joueur*> joueurs;

void start(int nb_joueur)
{
	string name;
	cout << u8"Merci de renseigner le nom de chaque joueur. Aucune modification ne sera possible au cours de la partie" << endl;
	for (int i = 0; i < nb_joueur; i++)
	{
		cout << endl << u8"Nom du Joueur " << i + 1 << " : ";
		cin >> name;
		Joueur* joueur = new Joueur(name);
		joueurs.push_back(joueur);
		//joueurs[i] = new Joueur(name);
		cout << u8"Initialisation du Joueur " << i + 1 << " - Nom du Joueur : " << joueurs[i]->getName() << endl;
		joueurs[i]->setPosition(0);
	}
}

Role* roles[TAILLE];
void role_create(int nb_joueur)
{
	roles[0] = new Role("shogun");
	roles[1] = new Role("samouraï");
	roles[2] = new Role("ninja");
	roles[3] = new Role("ninja");

	switch (nb_joueur) {
	case 5:
		roles[4] = new Role("ronin");
		break;
	case 6:
		roles[4] = new Role("ronin");
		roles[5] = new Role("ninja");
		break;
	case 7:
		roles[4] = new Role("ronin");
		roles[5] = new Role("ninja");
		roles[6] = new Role("samouraï");
		break;
	default:
		break;
	}

}

void role_destiny(int nb_joueur)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, nb_joueur-1);

	//Création de la liste
	int position[TAILLE];
	for (int a = 0; a < TAILLE; a++)
	{
		position[a] = 0;
	}

	for (int i = 0; i < nb_joueur; i++)
	{
		position[i] = 1;
	}

	for (int b = 0; b < nb_joueur; b++)
	{

		int randomNumber = dis(gen);
		int random = randomNumber;
		while (position[random] == 0)
		{
			int randomNumber = dis(gen);
			random = randomNumber;
		}
		joueurs[b]->setRole(roles[random]->getRole());
		joueurs[b]->setStatut(true);
		if (joueurs[b]->getRole() == "shogun") {
			this_thread::sleep_for(chrono::seconds(1));
			cout << endl << joueurs[b]->getName() << u8" est le Shogun ! " << endl;
			this_thread::sleep_for(chrono::seconds(5));
		}
		position[random] = 0;
	}

}

void position(int nb_joueur)
{
	int position = 0;
	for (int b = 0; b < nb_joueur; b++)
	{
		if (joueurs[b]->getRole() == "shogun")
		{
			joueurs[b]->setPosition(1);
			position = 1;
		}
		else if (position != 0)
		{
			position += 1;
			joueurs[b]->setPosition(position);
		}
	}
	for (int b = 0; b < nb_joueur; b++)
	{
		if (joueurs[b]->getPosition() == 0)
		{
			position += 1;
			joueurs[b]->setPosition(position);
		}
	}
}

void changeStatut(int i)
{
	if (joueurs[i]->getHP() == 0 || joueurs[i]->getDeck().size() == 0)
	{
		joueurs[i]->setStatut(false);
		cout << endl << joueurs[i]->getName() << u8" est à terre." << endl;
	}
	else if (joueurs[i]->getStatut() == false)
	{
		joueurs[i]->setStatut(true);
		cout << endl << joueurs[i]->getName() << u8" se relève." << endl;
	}
}

string list_perso[12][3] = {
	{"Benkei","5",u8"Les autres joueurs vous attaquent avec une difficulté augmentée de 1"},
	{"Chiyome","4",u8"Seules les armes peuvent vous faire perdre des points de vie.Vous n’êtes donc pas affecté par Cri de guerre ou Ju Jitsu"},
	{"Ginchiyo","4",u8"Vous réduisez de 1 les dégâts des armes(minimum 1).Par exemple, un Nodachi vous cause 2 dégâts au lieu de 3 mais un Shuriken vous cause tout de même 1 dégât"},
	{"Goemon","5",u8"Vous pouvez jouer 1 arme supplémentaire par tour.Par exemple, si vous avez une carte Concentration en jeu, vous pouvez jouer 3 armes par tour"},
	{"Hanzo","4",u8"Vous pouvez jouer vos cartes d’arme comme des parades (à moins que ça ne soit votre dernière carte en main).Vous pouvez aussi utiliser cette capacité contre un Cri de guerre"},
	{"Hideyoshi","4",u8"Durant votre phase de pioche, piochez 1 carte supplémentaire(donc normalement 3 cartes au lieu de 2)"},
	{"Ieyasu","5",u8"Durant votre phase de pioche, vous pouvez prendre la carte du dessus de la défausse au lieu de piocher votre première carte. Vous devez piocher normalement la deuxième(et les suivantes si besoin)"},
	{"Kojiro","5",u8"Vos armes peuvent attaquer n’importe quel autre joueur sans tenir compte de la difficulté"},
	{"Musashi","5",u8"Vos armes causent 1 dégât supplémentaire.N’augmente par les dégâts des autres cartes(Ju Jitsu par exemple)"},
	{"Nobunaga","5",u8"Durant votre tour, vous pouvez perdre 1 point de vie (sauf votre dernier) pour piocher 1 carte"},
	{"Tomoe","5",u8"Chaque fois qu’une de vos armes blesse un joueur, piochez 1 carte.Ne piochez qu’une seule carte par attaque, même si votre arme cause plusieurs points de dégâts"},
	{"Ushiwaka","4",u8"Chaque fois que vous perdez 1 point de vie à cause d’une arme, piochez 1 carte(donc si vous perdez 3 points de vie, vous piochez 3 cartes)"}
};

void perso_destiny(int nb_joueur)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 11);

	int perso_position[12];

	for (int i = 0; i < 12; i++)
	{
		perso_position[i] = 1;
	}

	for (int b = 0; b < nb_joueur; b++)
	{

		int randomNumber = dis(gen);
		int random = randomNumber;
		while (perso_position[random] == 0)
		{
			int randomNumber = dis(gen);
			random = randomNumber;
		}
		joueurs[b]->setPerso(list_perso[random][0]);
		joueurs[b]->setHP(stoi(list_perso[random][1]));
		joueurs[b]->setHpMax(stoi(list_perso[random][1]));
		joueurs[b]->setAbility(list_perso[random][2]);
		perso_position[random] = 0;

	}
}

void distrib_point_honneur(int nb_joueur)
{
	for (int b = 0; b < nb_joueur; b++)
	{
		if (joueurs[b]->getRole() == "shogun")
		{
			joueurs[b]->setPointHonneur(5);
		}
		else
		{

			switch (nb_joueur)
			{
			case 4:
			case 5:
				joueurs[b]->setPointHonneur(3);
				break;
			case 3:
			case 6:
			case 7:
				joueurs[b]->setPointHonneur(4);
				break;
			default:
				break;
			}

		}
	}

	switch (nb_joueur)
	{
	case 4:
	case 5:
		break;
	case 3:
	case 6:
	case 7:
		break;
	default:
		break;
	}
}

void what_role(int nb_joueur)
{
	for (int b = 0; b < nb_joueur; b++)
	{
		if (joueurs[b]->getRole() != "Shogun")
		{
			system("cls");
		}
	}
}

Pioche* pioche[NBCARTE];
void pioche_generation()
{
	pioche[0] = new Pioche("nodachi", 1, 3, 3, "", "attaque");
	pioche[1] = new Pioche("nagayari", 1, 2, 4, "", "attaque");
	pioche[2] = new Pioche("tanegashima", 1, 1, 5, "", "attaque");
	pioche[3] = new Pioche("daikyu", 1, 3, 5, "", "attaque");
	pioche[4] = new Pioche("katana", 1, 3, 2, "", "attaque");
	pioche[5] = new Pioche("kanabo", 1, 2, 3, "", "attaque");
	pioche[6] = new Pioche("wakizashi", 1, 3, 1, "", "attaque");
	pioche[7] = new Pioche("naginata", 2, 1, 4, "", "attaque");
	pioche[8] = new Pioche("bo", 5, 1, 2, "", "attaque");
	pioche[9] = new Pioche("kusarigama", 4, 2, 2, "", "attaque");
	pioche[10] = new Pioche("shuriken", 3, 1, 2, "", "attaque");
	pioche[11] = new Pioche("bokken", 6, 1, 1, "", "attaque");
	pioche[12] = new Pioche("kiseru", 5, 2, 1, "", "attaque");
	pioche[13] = new Pioche("cri_de_guerre", 4, 0, 0, u8"Les joueurs doivent défausser 1 parade ou perdre 1 point de vie. Les joueurs à terre ne sont pas affecter par cette carte.", "action");
	pioche[14] = new Pioche("daimyo", 4, 0, 0, u8"Piochez 2 cartes. Si vous possédez cette carte à la fin de la partie, elle vous rapporte 1 point d’honneur. Ces points ne sont jamais doublés ou triplés. Le ronin ne gagne aucun point grâce à cette carte.", "action");
	pioche[15] = new Pioche("diversion", 4, 0, 0, u8"Piocher au hasard une carte dans la main d'un joueur de votre choix et ajouter la à votre main.", "action");
	pioche[16] = new Pioche("geisha", 6, 0, 0, u8"Défausser une carte permanente en jeu (cible : jeu) ou une carte au hasard dans la main d'un autre joueur de votre choix.", "action");
	pioche[17] = new Pioche("méditation", 3, 0, 0, u8"Récupérez tous vos points de vie. Un autre joueur de votre choix pioche 1 carte. Vous ne pouvez pas soigner les autres joueurs. Vous pouvez jouer cette carte même si vous avez déjà tous vos points de vie.", "action");
	pioche[18] = new Pioche("parade", 15, 0, 0, u8"Si vous êtes la cible d'une carte d'arme, vous pouvez imédiatement l'éviter, même en dehors de votre tour.", "action");
	pioche[19] = new Pioche(u8"cérémonie_du_thé", 4, 0, 0, u8"Piocher 3 cartes, tous les autres joueurs piochent une carte.", "action");
	pioche[20] = new Pioche("jujitsu", 3, 0, 0, u8"Tous les autres joueurs doivent défausser une arme ou perdre 1 point de vie. Les joueurs à terre ne sont pas affecter par cette carte.", "action");
	pioche[21] = new Pioche("attaque_rapide", 3, 0, 0, u8"Vos armes causent 1 dégats suplémentaire par carte Attaque rapide que vous possédez.", "permanente");
	pioche[22] = new Pioche("code_du_bushido", 2, 0, 0, u8"Le Code du bushido peut être placé devant n’importe quel joueur. Si cette carte se trouve devant vous à la fin de votre phase de récupération, retournez la carte du dessus de la pioche et défaussez-la. Si c’est une arme, défaussez 1 arme et passez Code du bushido à votre voisin de gauche, ou perdez 1 point d’honneur et défaussez Code du bushido. Si ce n’est pas une arme, passez Code du bushido à votre voisin de gauche. Il ne peut y avoir qu’un seul Code du bushido en jeu en même temps. Si une telle carte est déjà en jeu, vous ne pouvez pas en jouer une autre.", "permanente");
	pioche[23] = new Pioche("armure", 4, 0, 0, u8"La carte permanente Armure modifie la difficulté d’une attaque visant le joueur qui la porte. Les bonus de plusieurs armures sont cumulables. Les autres joueurs au-delà du joueur en armure sont attaqués normalement.", "permanente");
	pioche[24] = new Pioche("concentration", 6, 0, 0, u8"Vous pouvez jouer 1 arme de plus par tour par carte concentration que vous possédez.", "permanente");
}

//int nb_joueur retiré
void piocheCarte(int i) //i permet de cibler un objet joueur dans joueurs
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 24);
	int randomNumber = dis(gen);
	int random = randomNumber;
	while (pioche[random]->getNumber() == 0)
	{
		int randomNumber = dis(gen);
		random = randomNumber;
	}
	joueurs[i]->setCarte(pioche[random]->getName());
	pioche[random]->setNumber(pioche[random]->getNumber() - 1);
	changeStatut(i);
	cout << endl << u8"Carte piochée : " << pioche[random]->getName() << endl;
	//cout << endl << "Carte : " << pioche[random]->getName() << endl << "Type : " << pioche[random]->getType() << endl;
	piocheVide();
}

void distribution(int nb_joueur)
{
	for (int i = 0; i < nb_joueur; i++)
	{
		if (joueurs[i]->getRole() == "shogun")
		{
			//cout << endl << "Cartes de " << joueurs[i]->getName() << " : " << endl;
			for (int nb = 0; nb < 4; nb++)
			{
				piocheCarte(i);
				//int nb_joueur retiré
			}
			
		}
		else if (joueurs[i]->getPosition() == 2 || joueurs[i]->getPosition() == 3)
		{
			//cout << endl << "Cartes de " << joueurs[i]->getName() << " : " << endl;
			for (int nb = 0; nb < 5; nb++)
			{
				piocheCarte(i);
				//int nb_joueur retiré

			}
		}
		else if (joueurs[i]->getPosition() == 4 || joueurs[i]->getPosition() == 5)
		{
			//cout << endl << "Cartes de " << joueurs[i]->getName() << " : " << endl;
			for (int nb = 0; nb < 6; nb++)
			{
				piocheCarte(i);
				//int nb_joueur retiré

			}
		}
		else if (joueurs[i]->getPosition() == 6 || joueurs[i]->getPosition() == 7)
		{
			//cout << endl << "Cartes de " << joueurs[i]->getName() << " : " << endl;
			for (int nb = 0; nb < 7; nb++)
			{
				piocheCarte(i);
				//int nb_joueur retiré

			}
		}
	}
}

void deck(int i)
{
	for (const auto& element : joueurs[i]->getDeck())
	{
		cout << endl << u8"Carte : " << element << endl;
		for (int i = 0; i < 25; i++)
		{
			if (pioche[i]->getName() == element)
			{
				if (pioche[i]->getType() == "attaque")
				{
					cout << u8"Points d'attaque : " << pioche[i]->getAttaque() << endl;
					cout << u8"Portée : " << pioche[i]->getPortee() << endl;
					cout << u8"Type : " << pioche[i]->getType() << endl;
				}
				else
				{
					cout << u8"Capacité : " << pioche[i]->getCapacity() << endl;
					cout << u8"Type : " << pioche[i]->getType() << endl;
				}
			}
		}
		
	}
}

void stats(int i)
{
	system("cls");
	cout << endl << u8"Affichage des statistiques de : " << joueurs[i]->getName() << endl << u8"Veuillez appuyer sur Entrée afin d'afficher vos statistiques : ";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << endl << endl << endl << u8"Rôle : " << joueurs[i]->getRole() << endl;
	cout << endl << u8"Personnage : " << joueurs[i]->getPerso() << endl;
	cout << endl << u8"Points de vie : " << joueurs[i]->getHP() << endl;
	cout << endl << u8"Points d'honneurs : " << joueurs[i]->getPointHonneur() << endl;
	cout << endl << u8"Capacité : " << joueurs[i]->getAbility() << endl;
	cout << endl << u8"Position : " << joueurs[i]->getPosition() << endl;
	cout << endl << u8"Cartes possédées : " << endl;
	deck(i);
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void firstStats(int nb_joueur)
{
	for (int i = 0; i < nb_joueur; i++)
	{
		stats(i);
	}
}

void recuperation(int i)
{
	if (joueurs[i]->getHP() <= 0)
	{
		joueurs[i]->setHP(joueurs[i]->getHpMax());
		changeStatut(i);
		cout << endl << u8"Tous vos points de vie vous ont été restaurés." << endl;
	}
}

int distance(int nb_joueur, string joueur1, string joueur2)
{
	int j1 = 0;
	int j2 = 0;
	int distance1 = 0;
	int distance2 = 0;
	// Parcours gauche
	for (int b = 0; b < nb_joueur; b++)
	{
		if (joueurs[b]->getName() == joueur1)
		{
			j1 = 1;
		}
		else if (joueurs[b]->getName() == joueur2 && j1 == 1)
		{
			distance1 += 1;
			j2 = 1;
		}
		else if (j1 == 1 && j2 == 0)
		{
			distance1 += 1;
		}
	}
	for (int b = 0; b < nb_joueur; b++)
	{
		if (joueurs[b]->getName() == joueur2 && j1 == 1 && j2 == 0)
		{
			distance1 += 1;
			j2 = 1;
		}
		else if (j1 == 1 && j2 == 0 && joueurs[b]->getStatut())
		{
			distance1 += 1;
		}
	}

	//Parcours droite
	j1 = 0;
	j2 = 0;
	for (int b = nb_joueur - 1; b > -1; b--)
	{
		if (joueurs[b]->getName() == joueur1)
		{
			j1 = 1;
		}
		else if (joueurs[b]->getName() == joueur2 && j1 == 1)
		{
			distance2 += 1;
			j2 = 1;
		}
		else if (j1 == 1 && j2 == 0)
		{
			distance2 += 1;
		}
	}
	for (int b = nb_joueur - 1; b > -1; b--)
	{
		if (joueurs[b]->getName() == joueur2 && j1 == 1 && j2 == 0)
		{
			distance2 += 1;
			j2 = 1;
		}
		else if (j1 == 1 && j2 == 0 && joueurs[b]->getStatut())
		{
			distance2 += 1;
		}
	}
	return min(distance1, distance2);
	return min(distance1, distance2);
}

list<string> defausse;

void piocheVide()
{
	int nb = 0;
	for (int i = 0; i < 25; i++)
	{
		if (pioche[i]->getNumber() != 0)
		{
			nb += 1;
		}
	}
	if (nb == 0)
	{
		cout << endl << u8"Pioche vide, les cartes de la défausse sont donc utilisées";
		for (const auto& element : defausse)
		{
			for (int i = 0; i < 25; i++)
			{
				if (pioche[i]->getName() == element)
				{
					pioche[i]->setNumber(pioche[i]->getNumber() + 1);
				}
			}
		}
		defausse.clear();
		this_thread::sleep_for(chrono::seconds(5));
	}
}

void pioche2Cartes(int i)
{
	for (int i = 0; i < 2; i++)
	{
		piocheCarte(i);
	}
}

void impactBushido(int i)
{
	if (joueurs[i]->getBushido())
	{
		cout << endl << u8"Impact du bushido :" << endl;
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, 24);
		int randomNumber = dis(gen);
		int random = randomNumber;
		int etat = 0;
		while (pioche[random]->getNumber() == 0)
		{
			int randomNumber = dis(gen);
			random = randomNumber;
		}
		pioche[random]->setNumber(pioche[random]->getNumber() - 1);
		defausse.push_back(pioche[random]->getName());
		cout << endl << u8"Voici la carte piochée : " << pioche[random]->getName() << endl;
		if (pioche[random]->getType() == "attaque")
		{
			for (const auto& carte : joueurs[i]->getDeck())
			{
				if (typeByName(carte) == "attaque")
				{
					int response;
					cout << endl << u8"Il s'agit d'une carte arme, 2 possibilités s'offre donc à vous : " << endl;
					cout << u8"1 : Défausser une arme et transférer la carte <Code du bushido> à votre voisin de gauche." << endl;
					cout << u8"2 : Perdre 1 point d'honneur et défausser la carte <Code du bushido>" << endl;
					cout << u8"Veuillez faire un choix (1/2) : ";
					cin >> response;
					while (response != 1 && response != 2)
					{ 
						cout << u8"Le choix n'est pas valide";
						cout << u8"Veuillez faire un choix (1/2) : ";
						cin >> response;
					}
					if (response == 1)
					{
						string name;
						cout << endl << u8"Voici votre deck :" << endl;
						deck(i);
						cout << endl << u8"Quelle carte souhaitez vous défausser ? :";
						cin >> name;
						while (not inDeck(i, name) || typeByName(name) != "attaque")
						{
							cout << endl << u8"Carte non valide";
							cout << endl << u8"Quelle carte souhaitez vous défausser ? : ";
							cin >> name;
						}
						defausse.push_back(name);
						joueurs[i]->removeCarte(name);
						for (const auto& joueur : joueurs)
						{
							if (joueur->getPosition() == joueurs[i]->getPosition() + 1)
							{
								joueur->setBushido(true);
								joueurs[i]->setBushido(false);
								cout << endl << joueur->getName() << u8" possède maintenant la carte <Code du Bushido> " << endl;
							}
						}
						if (joueurs[i]->getBushido() == true)
						{
							joueurs[0]->setBushido(true);
							joueurs[i]->setBushido(false);
							cout << endl << joueurs[0]->getName() << u8" possède maintenant la carte <Code du Bushido> " << endl;
						}
						etat = 1;
					}
					else
					{
						cout << endl << u8"Vous Perdez 1 point d'honneur et défausser la carte <Code du bushido>" << endl;
						joueurs[i]->setPointHonneur(joueurs[i]->getPointHonneur() - 1);
						joueurs[i]->setBushido(false);
						cout << endl << joueurs[i]->getName() << u8" vous possédez maintenant " << joueurs[i]->getPointHonneur() << u8" point(s) d'honneur(s)" << endl;
						etat = 1;
					}
					return;
				}
			}
			if (etat == 0)
			{
				cout << endl << u8"Vous ne possédez pas de cartes attaques dans votre deck donc , vous Perdez 1 point d'honneur et défausser la carte <Code du bushido>" << endl;
				joueurs[i]->setPointHonneur(joueurs[i]->getPointHonneur() - 1);
				joueurs[i]->setBushido(false);
				cout << endl << joueurs[i]->getName() << u8" vous possédez maintenant " << joueurs[i]->getPointHonneur() << u8" point(s) d'honneur(s)" << endl;
			}
		}
		else
		{
			cout << endl << u8"Vous transférez la carte <Code du bushido> à votre voisin de gauche. " << endl;
			for (const auto& joueur : joueurs)
			{
				if (joueur->getPosition() == joueurs[i]->getPosition() + 1)
				{
					joueur->setBushido(true);
					joueurs[i]->setBushido(false);
					cout << endl << joueur->getName() << u8" possède maintenant la carte <Code du Bushido> " << endl;
					break;
				}
			}
			if (joueurs[i]->getBushido() == true)
			{
				joueurs[0]->setBushido(true);// remplacer true par false
				joueurs[i]->setBushido(false);
				cout << endl << joueurs[0]->getName() << u8" possède maintenant la carte <Code du Bushido> " << endl;
			}
		}
	}
}

void detailByName(string name)
{
	for (const auto& carte : pioche)
	{
		if (carte->getName() == name)
		{
			if (carte->getType() == "attaque")
			{
				cout << endl << u8"Carte : " << name << endl << u8"Attaque : " << carte->getAttaque() << endl << u8"Portée : " << carte->getPortee() << endl;
			}
			else
			{
				cout << endl << u8"Carte : " << name << endl << u8"Description : " << carte->getCapacity() << endl;
			}
		}
	}
}

void affichePerma(int i)
{
	cout << endl << u8"Cartes permanentes de " << joueurs[i]->getName() << " : " << endl;
	if (joueurs[i]->getCartePerma().size() > 0)
	{
		for (const auto& perma : joueurs[i]->getCartePerma())
		{
			cout << endl << perma[0] << endl;
		}
	}
	if (joueurs[i]->getBushido())
	{
		cout << endl << u8"code_du_bushido" << endl;
	}
	else
	{
		cout << endl << u8"Vous n'avez aucune carte permanente en jeu" << endl;
	}
}

void tour(int nb_joueur)
{
	int  etat = 0;
	for (int i = 0; i < nb_joueur; i++)
	{
		if (joueurs[i]->getRole() == "shogun")
		{
			etat = 1;
		}
		if (etat == 1)
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			this_thread::sleep_for(chrono::seconds(3));
			//system("cls");
			cout << endl << u8"Tour de : " << joueurs[i]->getName() << endl << endl << endl;
			//Récupération
			recuperation(i);
			changeStatut(i);
			cout << endl << u8"Vous avez " << joueurs[i]->getHP() << " HP" << endl;
			//Pioche
			if (joueurs[i]->getPerso() == "Ieyasu")
			{
				string response;
				if (defausse.size() > 2)
				{
					string carte = defausse.back();
					cout << endl << u8"Voici la dernière carte de la défausse : " << endl;
					detailByName(carte);
					cout << endl << u8"Souhaitez-vous piocher cette carte ? (Y/N) : ";
					cin >> response;
					while (response != "Y" && response != "y" && response != "N" && response != "n")
					{
						cout << u8"Veuillez saisir une réponse valide : ";
						cin >> response;
					}
					if (response == "Y" || response == "y")
					{
						joueurs[i]->setCarte(carte);
						defausse.pop_back();
						piocheCarte(i);
					}
					else
					{
						//pioche2Cartes(i);
						piocheCarte(i);
						piocheCarte(i);
					}
				}
				else
				{
					//pioche2Cartes(i);
					piocheCarte(i); 
					piocheCarte(i);
				}
			}
			else
			{
				if (joueurs[i]->getPerso() == "Hideyoshi")
				{
					piocheCarte(i);
				}
				//pioche2Cartes(i);
				piocheCarte(i);
				piocheCarte(i);
				if (joueurs[i]->getPerso() == "Nobunaga")
				{
					if (joueurs[i]->getHP() > 1)
					{
						string response;
						cout << u8"Voulez vous piocher une carte suplémentaire contre 1 HP ? (Y/N) : ";
						cin >> response;
						while (response != "Y" && response != "y" && response != "N" && response != "n")
						{
							cout << u8"Veuillez saisir une réponse valide : ";
							cin >> response;
						}
						if (response == "Y" || response == "y")
						{
							piocheCarte(i);
							joueurs[i]->setHP(joueurs[i]->getHP() - 1);
							cout << endl << u8"Il vous reste maintenant " << joueurs[i]->getHP() << " HP" << endl;
						}
					}
				}
			}
			// Affichage des cartes permanentes en jeu
			affichePerma(i);
			//Jeu
			impactBushido(i);
			if (joueurs[i]->getStatut())
			{
				choixAttaque(i, nb_joueur);
				attaque(i, nb_joueur);
				changeStatut(i);
			}
			//Changement de statut 
			changeStatut(i);
			//Défausse
			phaseDefausse(i);
			//Vérifier si daimyo
			verifDaimyo(i);
		}
	}

	for (int i = 0; i < nb_joueur; i++)
	{

		if (joueurs[i]->getRole() == "shogun")
		{
			etat = 0;
		}
		if (etat == 1)
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			system("cls");
			this_thread::sleep_for(chrono::seconds(3));
			cout << endl << u8"Tour de : " << joueurs[i]->getName() << endl << endl << endl;
			//Récupération
			recuperation(i);
			changeStatut(i);
			cout << endl << u8"Vous avez " << joueurs[i]->getHP() << " HP" << endl;
			//Pioche
			if (joueurs[i]->getPerso() == "Ieyasu")
			{
				string response;
				if (defausse.size() > 2)
				{
					string carte = defausse.back();
					cout << endl << u8"Voici la dernière carte de la défausse : " << endl;
					detailByName(carte);
					cout << endl << u8"Souhaitez-vous picoher cette carte ? (Y/N) : ";
					cin >> response;
					while (response != "Y" && response != "y" && response != "N" && response != "n")
					{
						cout << u8"Veuillez saisir une réponse valide : ";
						cin >> response;
					}
					if (response == "Y" || response == "y")
					{
						joueurs[i]->setCarte(carte);
						defausse.pop_back();
						piocheCarte(i);
					}
					else
					{
						//pioche2Cartes(i);
						piocheCarte(i);
						piocheCarte(i);
					}
				}
				else
				{
					//pioche2Cartes(i);
					piocheCarte(i);
					piocheCarte(i);
				}
			}
			else
			{
				if (joueurs[i]->getPerso() == "Hideyoshi")
				{
					piocheCarte(i);
				}
				//pioche2Cartes(i);
				piocheCarte(i);
				piocheCarte(i);
				if (joueurs[i]->getPerso() == "Nobunaga")
				{
					if (joueurs[i]->getHP() > 1)
					{
						string response;
						cout << u8"Voulez vous piocher une carte contre 1 HP ? (Y/N) : ";
						cin >> response;
						while (response != "Y" && response != "y" && response != "N" && response != "n")
						{
							cout << u8"Veuillez saisir une réponse valide : ";
							cin >> response;
						}
						if (response == "Y" || response == "y")
						{
							piocheCarte(i);
							joueurs[i]->setHP(joueurs[i]->getHP() - 1);
							cout << endl << u8"Il vous reste maintenant " << joueurs[i]->getHP() << " HP" << endl;
						}
					}
				}
			}
			// Affichage des cartes permanentes en jeu
			affichePerma(i);
			//Jeu
			impactBushido(i);
			if (joueurs[i]->getStatut())
			{
				choixAttaque(i, nb_joueur);
				attaque(i, nb_joueur);
				changeStatut(i);
			}
			//Changement de statut 
			changeStatut(i);
			//Défausse
			phaseDefausse(i);
			//Vérifier si daimyo
			verifDaimyo(i);
		}
	}
}

bool inDeck(int i, string carte)
{
	for (string element : joueurs[i]->getDeck())
	{
		if (element == carte)
		{
			return true;
		}
	}
	return false;
}

string typeByName(string name)
{
	for (const auto& element : pioche)
	{
		if (element->getName() == name)
		{
			return element->getType();
		}
	}
}

bool attaqueIn(int i)
{
	int nb_concentration = 0;

	for (const auto& element : joueurs[i]->getCartePerma())
	{
		if (element[0] == "concentration")
		{
			nb_concentration += 1;
		}
	}
	if (joueurs[i]->getPerso() == "Goemon")
	{
		nb_concentration += 1;

	}
	if (joueurs[i]->getCarteAttaque().size() < 1 + nb_concentration)
	{
		return true;
	}
	else {
		return false;
	}
}

bool joueurInGame(string name)
{
	for (const auto& element : joueurs)
	{
		if (element->getName() == name)
		{
			return true;
		}
	}
	return false;
}

bool joueurCiblable(string name)
{
	for (const auto& element : joueurs)
	{
		if (element->getName() == name)
		{
			return element->getStatut();
		}
	}
}

int cibleValide(string cible, string carte)
{
	int statut = 1;
	if (not joueurInGame(cible))
	{
		cout << endl << u8"Le joueur n'est pas dans la partie." << endl;
		statut = 0;
	}
	if (not joueurCiblable(cible))
	{
		cout << endl << u8"Le joueur " << cible << u8" est à terre, il ne peut donc pas être la cible de votre carte d'attaque." << endl;
		statut = 0;
	}
	if (carte == "geisha" && cible == "jeu")
	{
		statut = 1;
	}
	return statut;
}

int verifBushido()
{
	int statut = 1;
	for (const auto& joueur : joueurs)
	{
		if (joueur->getBushido() == true)
		{
			statut = 0;
			cout << endl << u8"Une carte <Code du bushido> est déjà en jeu.";
		}
	}
	return statut;
}

int precisionByName(string name)
{
	for (const auto& element : pioche)
	{
		if (element->getName() == name)
		{
			return element->getPortee();
		}
	}
}

int attaqueByName(string name)
{
	for (const auto& element : pioche)
	{
		if (element->getName() == name)
		{
			return element->getAttaque();
		}
	}
}

void choixAttaque(int i, int nb_joueur)
{
	if (joueurs[i]->getStatut())
	{
		//Choix des cartes joué
		string rep = "Y";
		int statut = 1;
		string carte;
		string cible;
		cout << endl << u8"Voici votre deck : " << endl;
		deck(i);
		if (joueurs[i]->getDeck().size() < 1)
		{
			cout << endl << joueurs[i]->getName() << u8" ne possède plus de cartes dans son deck ! " << endl;
		}
		else
		{
			cout << endl << u8"Voulez vous ajouter une carte à votre attaque ? (Y/N) : ";
			cin >> rep;
			while (rep != "Y" && rep != "y" && rep != "N" && rep != "n")
			{
				cout << endl << u8"Réponse invalide";
				cout << endl << u8"Veuillez saisir une réponse valide : ";
				cin >> rep;
			}
			while (rep == "Y" || rep == "y")
			{
				cout << endl << u8"Saisir le nom de la carte : ";
				cin >> carte;
				if (inDeck(i, carte))
				{
					if (typeByName(carte) == "attaque")
					{
						if (not attaqueIn(i))
						{
							cout << endl << u8"Vous ne pouvez plus jouer de carte de type attaque." << endl;
							statut = 0;
						}
						else
						{
							cout << endl << u8"Voici les cibles attaquables : " << endl;
							int diff = 0;
							int dist = 0;
							int spe = 0;
							for (const auto& joueur : joueurs)
							{
								if (joueur->getName() != joueurs[i]->getName())
								{
									int difficulte = distance(nb_joueur, joueurs[i]->getName(), joueur->getName());
									for (const auto& carte : joueur->getCartePerma())
									{
										if (carte[0] == "armure")
										{
											difficulte += 1;
										}
									}
									if (joueur->getPerso() == "Benkei")
									{
										difficulte += 1;
									}
									diff = difficulte;
									dist = distance(nb_joueur, joueurs[i]->getName(), joueur->getName());
									if (joueur->getPerso() == "Kojiro")
									{
										spe = 1;
										cout << endl << joueur->getName();
									}
									if (precisionByName(carte) >= difficulte && cibleValide(joueur->getName(),carte))
									{
										cout << endl << joueur->getName() << endl;
									}
								}
							}
							cout << endl << u8"Saisir le nom de la cible :";
							cin >> cible;
							statut = cibleValide(cible, carte);
					
							if (statut == 1 && (precisionByName(carte) >= distance(nb_joueur, joueurs[i]->getName(), cible) || spe == 1))
							{
								joueurs[i]->getCarteAttaque().push_back({carte, cible});
								joueurs[i]->removeCarte(carte);
							}
							else
							{
								cout << u8"Cible invalide" << endl;
							}
						}
					}
					if (typeByName(carte) == "action")
					{
						if (carte == "diversion" || carte == "geisha" || carte == "méditation")
						{
							cout << endl << u8"Saisir le nom de la cible :";
							cin >> cible;
							statut = cibleValide(cible, carte);
							if (statut == 1)
							{
								joueurs[i]->getCarteAction().push_back({ carte, cible });
								joueurs[i]->removeCarte(carte);
							}
						}
						else
						{
							joueurs[i]->getCarteAction().push_back({ carte, cible });
							joueurs[i]->removeCarte(carte);
						}
					}
					if (typeByName(carte) == "permanente")
					{
						if (carte == "code_du_bushido")
						{
							cout << endl << u8"Saisir le nom de la cible :";
							cin >> cible;
							statut = cibleValide(cible, carte);
							if (statut == 1)
							{
								statut = verifBushido();
								if (statut == 1)
								{
									joueurs[i]->getCartePerma().push_back({ carte, cible });
									joueurs[i]->removeCarte(carte);
								}
							}
						}
						else
						{
							joueurs[i]->getCartePerma().push_back({ carte, ""});
							joueurs[i]->removeCarte(carte);
						}
					}
				}
				else
				{
					cout << u8"Le nom de la carte n'est pas valide" << endl;
				}
				cout << endl << u8"Voulez vous passez au tour suivant ? (Y/N) : ";
				cin >> rep;
				while (rep != "Y" && rep != "y" && rep != "N" && rep != "n")
				{
					cout << endl << u8"Réponse invalide";
					cout << endl << u8"Voulez vous passez au tour suivant ? (Y/N) : ";
					cin >> rep;
				}

				if (rep == "Y" || rep == "y")
				{
					return;
				}

				else
				{
					cout << endl << u8"Voulez vous ajouter une carte à votre attaque ? (Y/N) : ";
					cin >> rep;
					while (rep != "Y" && rep != "y" && rep != "N" && rep != "n")
					{
						cout << endl << u8"Réponse invalide";
						cout << endl << u8"Veuillez saisir une réponse valide : ";
						cin >> rep;
					}
				}

			}
		}
	}
}

void attBushido(string name)
{
	for (const auto& joueur : joueurs)
	{
		if (joueur->getName() == name)
		{
			joueur->setBushido(true);
		}
	}
}

void criDeGuerre(int i, int nb_joueur)
{
	for (const auto& joueur : joueurs)
	{
		int parade = 0;
		if (joueur->getName() != joueurs[i]->getName() && joueur->getStatut() != false && joueur->getPerso() != "Chiyome")
		{
			if (joueur->getPerso() == "Hanzo")
			{
				int nb_attaque = 0;
				for (const auto& cartes : joueur->getDeck())
				{
					if (typeByName(cartes) == "attaque")
					{
						nb_attaque += 1;
					}	
				}
				if (nb_attaque > 1)
				{
					string response;
					cout << endl << joueur->getName() << u8" souhaitez vous parrer l'attaque ? (Y/N) : ";
					cin >> response;
					while (response != "Y" && response != "N" && response != "y" && response != "n")
					{
						cout << endl << u8"Veuillez préciser une réponse valide" << endl;
						cin >> response;
					}
					if (response == "Y" || response == "y")
					{
						string carte;
						cout << endl << u8"Voici votre deck : " << endl;
						deck(getPosByName(joueur->getName(), nb_joueur));
						cout << endl << u8"Veuillez choisir la carte à utiliser : ";
						cin >> carte;
						if (inDeck(getPosByName(joueur->getName(),nb_joueur), carte) && typeByName(carte) == "attaque")
						{
							joueur->removeCarte(carte);
							defausse.push_back(carte);
							parade = 1;
						}
					}
				}
			}
			if (parade == 0)
			{
				bool etat = false;
				for (const auto& carte : joueurs[i]->getDeck())
				{
					string rep;
					if (carte == "parade" && etat == false)
					{
						cout << endl << joueur->getName() << u8" souhaitez-vous utiliser votre carte parade ? (Y/N) : ";
						cin >> rep;
						etat = true;
						if (rep != "N" && rep != "n")
						{
							defausse.push_back(carte);
							joueurs[i]->removeCarte(carte);
						}
						else
						{
							joueur->setHP(joueur->getHP() - 1);
							cout << endl << joueur->getName() << u8" vous perdez 1 HP" << endl;

							if (joueur->getHP() < 1 && joueur->getStatut())
							{
								cout << endl << joueurs[i]->getName() << u8" à vaincu " << joueur->getName() << u8" ! " << endl;
								changeStatut(getPosByName(joueur->getName(), nb_joueur));
								joueur->setPointHonneur(joueur->getPointHonneur() - 1);
								cout << joueur->getName() << u8" perd 1 point d'honneur";
								cout << endl << joueur->getName() << u8" possède maintenant " << joueur->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
								joueurs[i]->setPointHonneur(joueurs[i]->getPointHonneur() + 1);
								cout << endl << joueurs[i]->getName() << u8" gagne 1 point d'honneur";
								cout << endl << joueurs[i]->getName() << u8" possède maintenant " << joueurs[i]->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
								victoireEpe(joueurs[i]->getName(), joueur->getName(), nb_joueur);
								finGame(joueurs[i]->getName(), joueur->getName(), nb_joueur);
							}
						}
					}
				}
				if (etat == false)
				{
					joueur->setHP(joueur->getHP() - 1);
					cout << endl << joueur->getName() << u8" vous ne possédez pas de carte <Parade> donc vous perdez 1 HP" << endl;

					if (joueur->getHP() < 1 && joueur->getStatut())
					{
						cout << endl << joueurs[i]->getName() << u8" à vaincu " << joueur->getName() << u8" ! " << endl;
						changeStatut(getPosByName(joueur->getName(), nb_joueur));
						joueur->setPointHonneur(joueur->getPointHonneur() - 1);
						cout << joueur->getName() << endl << u8" perd 1 point d'honneur";
						cout << endl << joueur->getName() << u8" possède maintenant " << joueur->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
						joueurs[i]->setPointHonneur(joueurs[i]->getPointHonneur() + 1);
						cout << joueurs[i]->getName() << u8" gagne 1 point d'honneur";
						cout << endl << joueurs[i]->getName() << u8" possède maintenant " << joueurs[i]->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
						victoireEpe(joueurs[i]->getName(), joueur->getName(), nb_joueur);
						finGame(joueurs[i]->getName(), joueur->getName(), nb_joueur);
					}
					cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				}
			}
		}
	}
}

void daimyo(int i)
{
	pioche2Cartes(i);
}

void diversion(int i, string cible, int nb_joueur)
{
	int position = getPosByName(cible, nb_joueur);
	if (joueurs[position]->getDeck().size() > 0)
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, joueurs[position]->getDeck().size());
		int randomNumber = dis(gen);
		int random = randomNumber;
		string carte = joueurs[position]->getCarte(randomNumber);
		joueurs[i]->setCarte(carte);
		joueurs[position]->removeCarte(carte);
		cout << endl << joueurs[i]->getName() << u8" vous piochez " << carte << u8" du deck de " << joueurs[position]->getName();
	}
	else
	{
		cout << endl << u8"Le joueur ne possède plus de carte" << endl;
	}
	this_thread::sleep_for(chrono::seconds(3));
}

int getPosByName(string name, int nb_joueur)
{
	for (int i = 0; i < nb_joueur; i++)
	{
		if (joueurs[i]->getName() == name)
		{
			return i;
		}
	}
}

void geisha(int i, string cible, int nb_joueur)
{
	int position = getPosByName(cible, nb_joueur);
	int response;
	int statut = 0;
	cout << endl << u8"2 possibilités s'offre donc à vous : " << endl;
	cout << u8"1 : Défausser une carte permanente en jeu." << endl;
	cout << u8"2 : Défausser une carte au hasard dans la main de " << cible << "." << endl;
	cout << u8"Veuillez faire un choix (1/2) : ";
	cin >> response;
	while (response != 1 && response != 2)
	{
		cout << u8"Le choix n'est pas valide";
		cout << u8"Veuillez faire un choix (1/2) : ";
		cin >> response;
	}
	for (const auto& joueur : joueurs)
	{
		if (joueur->getCartePerma().size() > 0)
		{
			statut = 1;
		}
	}
	if (response == 1 && statut == 1)
	{
		position = getPosByName(cible, nb_joueur);
		while (joueurs[i]->getCartePerma().size() < 1 && joueurs[i]->getBushido() == false)
		{
			cout << endl << u8"Le joueur ne possède aucune carte permanente en jeux." << endl << "Veuillez saisir un nouveau nom : ";
			cin >> cible;
			while (not joueurInGame(cible))
			{
				cout << endl << u8"Veuillez saisir un nom de joueur valide : ";
				cin >> cible;
			}
			position = getPosByName(cible, nb_joueur);
		}
		if (joueurs[i]->getBushido())
		{
			joueurs[1]->setBushido(false);
			defausse.push_back("code_du_bushido");
		}
		else
		{
			defausse.push_back(joueurs[i]->getCartePerma().back()[0]);
			joueurs[i]->getCartePerma().pop_back();
		}

	}
	else
	{
		if (response == 1)
		{
			cout << endl << u8"Aucune carte permanente n'est en jeux, votre choix devient donc le 2.";
		}
		while (joueurs[position]->getDeck().size() < 1)
		{
			cout << endl << u8"La cible ne possède aucune carte dans son deck. " << endl;
			cout << endl << u8"Veuillez saisir un nouveau nom : ";
			cin >> cible;
			position = getPosByName(cible, nb_joueur);
		}
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, joueurs[position]->getDeck().size() - 1);
		int randomNumber = dis(gen);
		int random = randomNumber;
		string carte = joueurs[position]->getCarte(randomNumber);
		defausse.push_back(carte);
		joueurs[position]->removeCarte(carte);
		cout << endl << u8"Vous défaussez la carte " << carte << u8" du deck de " << joueurs[position]->getName();
		this_thread::sleep_for(chrono::seconds(3));

	}
}

void meditation(int i, string cible, int nb_joueur)
{
	joueurs[i]->setHP(joueurs[i]->getHpMax());
	int position = getPosByName(cible, nb_joueur);
	piocheCarte(position);
}

void ceremonie(int i, int nb_joueur)
{
	for (const auto& joueur : joueurs)
	{
		cout << endl << joueur->getName() << u8" pioche : ";
		if (joueur->getName() == joueurs[i]->getName())
		{
			for (int a = 0; a < 3; a++)
			{
				piocheCarte(a);
			}
		}
		else
		{
			int position = getPosByName(joueur->getName(), nb_joueur);
			piocheCarte(position);
		}
	}
	this_thread::sleep_for(chrono::seconds(3));
}

void jujitsu(int i, int nb_joueur)
{
	for (const auto& joueur : joueurs)
	{
		if (joueur->getName() != joueurs[i]->getName() && joueur->getPerso() != "Chiyome")
		{
			if (joueur->getStatut())
			{
				int arme = 0;
				for (const auto& carte : joueur->getDeck())
				{
					if (typeByName(carte) == "attaque")
					{
						arme = 1;
					}
				}
				if (arme == 1)
				{
					int response;
					system("cls");
					cout << endl << endl << joueur->getName() << u8" 2 possibilités s'offre donc à vous : " << endl;
					cout << u8"1 : Défausser une carte arme." << endl;
					cout << u8"2 : Perdre 1 HP" << endl;
					cout << u8"Veuillez faire un choix (1/2) : ";
					cin >> response;
					while (response != 1 && response != 2)
					{
						cout << u8"Le choix n'est pas valide";
						cout << u8"Veuillez faire un choix (1/2) : ";
						cin >> response;
					}
					if (response == 1)
					{
						string choix;
						cout << endl << joueur->getName() << u8" voici votre deck : " << endl;
						deck(getPosByName(joueur->getName(), nb_joueur));
						cout << endl << u8"Quelle arme voulez-vous défausser ? : ";
						cin >> choix;
						while (not inDeck(getPosByName(joueur->getName(), nb_joueur), choix) || typeByName(choix) != "attaque")
						{
							cout << u8"Choix non valide, veuillez choisir une carte :";
							cin >> choix;
						}
						joueur->removeCarte(choix);
						defausse.push_back(choix);
						cout << endl << u8"Carte défaussée : " << choix;
						this_thread::sleep_for(chrono::seconds(3));
					}
					else
					{
						joueur->setHP(joueur->getHP() - 1);
						cout << endl << joueur->getName() << u8" vous perdez 1 HP";
						this_thread::sleep_for(chrono::seconds(3));

						if (joueur->getHP() < 1 && joueur->getStatut())
						{
							cout << endl << joueurs[i]->getName() << u8" à vaincu " << joueur->getName() << u8" ! " << endl;
							changeStatut(getPosByName(joueur->getName(), nb_joueur));
							joueur->setPointHonneur(joueur->getPointHonneur() - 1);
							cout << joueur->getName() << endl << u8" perd 1 point d'honneur";
							cout << endl << joueur->getName() << u8" possède maintenant " << joueur->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
							joueurs[i]->setPointHonneur(joueurs[i]->getPointHonneur() + 1);
							cout << joueurs[i]->getName() << u8" gagne 1 point d'honneur";
							cout << endl << joueurs[i]->getName() << u8" possède maintenant " << joueurs[i]->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
							victoireEpe(joueurs[i]->getName(), joueur->getName(), nb_joueur);
							finGame(joueurs[i]->getName(), joueur->getName(), nb_joueur);
						}
					}
				}
				else
				{
					joueur->setHP(joueur->getHP() - 1);
					cout << endl << joueur->getName() << u8" vous perdez 1 HP";

					if (joueur->getHP() < 1 && joueur->getStatut())
					{
						cout << endl << joueurs[i]->getName() << u8" à vaincu " << joueur->getName() << u8" ! " << endl;
						changeStatut(getPosByName(joueur->getName(), nb_joueur));
						joueur->setPointHonneur(joueur->getPointHonneur() - 1);
						cout << joueur->getName() << endl << u8" perd 1 point d'honneur";
						cout << endl << joueur->getName() << u8" possède maintenant " << joueur->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
						joueurs[i]->setPointHonneur(joueurs[i]->getPointHonneur() + 1);
						cout << joueurs[i]->getName() << u8" gagne 1 point d'honneur";
						cout << endl << joueurs[i]->getName() << u8" possède maintenant " << joueurs[i]->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
						victoireEpe(joueurs[i]->getName(), joueur->getName(), nb_joueur);
						finGame(joueurs[i]->getName(), joueur->getName(), nb_joueur);
					}
				}
			}
		}
	}
}

void attaque(int i, int nb_joueur)
{
	//Cartes permanentes
	joueurs[i]->resetBonusAttaque();
	for (const auto& perma : joueurs[i]->getCartePerma())
	{
		if (perma[0] == "attaque_rapide")
		{
			joueurs[i]->moreBonusAttaque();
		}
		if (perma[0] == "code_du_bushido")
		{
			attBushido(perma[1]);
		}
	}
	if (joueurs[i]->getPerso() == "Musashi")
	{
		joueurs[i]->moreBonusAttaque();
	}
	for (const auto& action : joueurs[i]->getCarteAction())
	{
		if (action[0] == "cri_de_guerre")
		{
			criDeGuerre(i, nb_joueur);
		}
		if (action[0] == "daimyo")
		{
			daimyo(i);
		}
		if (action[0] == "diversion")
		{
			diversion(i, action[1], nb_joueur);
		}
		if (action[0] == "geisha")
		{
			geisha(i, action[1], nb_joueur);
		}
		if (action[0] == "méditation")
		{
			meditation(i, action[1], nb_joueur);
		}
		if (action[0] == "cérémonie_du_thé")
		{
			ceremonie(i, nb_joueur);
		}
		if (action[0] == "jujitsu")
		{
			jujitsu(i, nb_joueur);
		}
		if (action[1] != "")
		{
			int position = getPosByName(action[1], nb_joueur);
			if (joueurs[position]->getHP() < 1 && joueurs[position]->getStatut())
			{
				cout << endl << joueurs[i]->getName() << u8" a vaincu " << joueurs[position]->getName() << u8" ! " << endl;
				changeStatut(position);
				joueurs[position]->setPointHonneur(joueurs[position]->getPointHonneur() - 1);
				cout << joueurs[position]->getName() << u8" perd 1 points d'honneur" << endl;
				joueurs[i]->setPointHonneur(joueurs[i]->getPointHonneur() + 1);
				cout << joueurs[i]->getName() << u8" gagne 1 points d'honneur" << endl;
				victoireEpe(joueurs[i]->getName(), joueurs[position]->getName(), nb_joueur);
				finGame(joueurs[i]->getName(), joueurs[position]->getName(), nb_joueur);
			}
		}
	}
	joueurs[i]->getCarteAction().clear();
	for (const auto& attaque : joueurs[i]->getCarteAttaque())
	{
		string cible = attaque[1];
		int position = getPosByName(cible, nb_joueur);
		int parade = 0;

		if (joueurs[position]->getPerso() == "Hanzo")
		{
			int nb_attaque = 0;
			for (const auto& cartes : joueurs[position]->getDeck())
			{
				if (typeByName(cartes) == "attaque")
				{
					nb_attaque += 1;
				}
			}
			if (nb_attaque > 1)
			{
				string response;
				cout << endl << cible << u8" souhaitez vous parrer l'attaque à l'aide d'une carte d'arme ? (Y/N) : ";
				cin >> response;
				while (response != "Y" && response != "N" && response != "y" && response != "n")
				{
					cout << endl << u8"Veuillez préciser une réponse valide" << endl;
					cin >> response;
				}
				if (response == "Y" || response == "y")
				{
					string carte;
					cout << endl << u8"Voici votre deck : " << endl;
					deck(position);
					cout << endl << u8"Veuillez choisir la carte à utiliser : ";
					cin >> carte;
					while (not inDeck(position, carte) && typeByName(carte) != "attaque")
					{
						cout << endl << u8"Veuillez saisir une carte valide : ";
						cin >> carte;
					}
					if (inDeck(position, carte) && typeByName(carte) == "attaque")
					{
						joueurs[position]->removeCarte(carte);
						defausse.push_back(carte);
						parade = 1;
						cout << endl << joueurs[position]->getName() << u8" utilise parade ";
					}
				}
			}
		}

		if (inDeck(position, "parade") && parade == 0)
		{
			string response;
			cout << endl << cible << u8" : Voulez-vous utiliser votre carte <Parade> ? (Y/N) : ";
			cin >> response;
			while (response != "Y" && response != "N" && response != "y" && response != "n")
			{
				cout << endl << u8"Réponse non valide, veuillez répondre par Y(yes) ou par N(non) :";
				cin >> response;
			}
			if (response == "Y" || response == "y")
			{
				parade = 1;
				cout << endl << u8"Le joueur " << joueurs[position]->getName() << u8" utilise parade";
				joueurs[position]->removeCarte(attaque[0]);
				defausse.push_back(attaque[0]);
			}
		}
		
		if (parade == 0)
		{
			if (joueurs[position]->getPerso() != "Ginchiyo")
			{
				joueurs[position]->setHP(joueurs[position]->getHP() - joueurs[i]->getBonusAttaque() - attaqueByName(attaque[0]));
				cout << endl << attaque[0] << u8" inflige " << joueurs[i]->getBonusAttaque() + attaqueByName(attaque[0]) << u8" points de dégâts à " << joueurs[position]->getName();
				if (joueurs[i]->getPerso() == "Tomoe")
				{
					piocheCarte(i);
				}
				if (joueurs[position]->getPerso() == "Ushiwaka")
				{
					for (int k = 0; k < joueurs[i]->getBonusAttaque() - attaqueByName(attaque[0]); k++)
					{
						piocheCarte(position);
					}
				}
			}
			else if (joueurs[position]->getPerso() == "Ginchiyo" && attaqueByName(attaque[0]) > 1)
			{
				joueurs[position]->setHP(joueurs[position]->getHP() - joueurs[i]->getBonusAttaque() - attaqueByName(attaque[0]) + 1);

			}
			if (joueurs[position]->getHP() < 1 && joueurs[position]->getStatut())
			{
				cout << endl << joueurs[i]->getName() << u8" à vaincu " << joueurs[position]->getName() << u8" ! " << endl;
				changeStatut(position);
				joueurs[position]->setPointHonneur(joueurs[position]->getPointHonneur() - 1);
				cout << joueurs[position]->getName() << u8" perd 1 point d'honneur";
				cout << endl << joueurs[position]->getName() << u8" possède maintenant " << joueurs[position]->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
				joueurs[i]->setPointHonneur(joueurs[i]->getPointHonneur() + 1);
				cout << joueurs[i]->getName() << u8" gagne 1 point d'honneur";
				cout << endl << joueurs[i]->getName() << u8" possède maintenant " << joueurs[i]->getPointHonneur() << u8" point(s) d'honnneur(s) ! " << endl;
				victoireEpe(joueurs[i]->getName(), joueurs[position]->getName(), nb_joueur);
				finGame(joueurs[i]->getName(), joueurs[position]->getName(), nb_joueur);
			}
		}
	}
	joueurs[i]->getCarteAttaque().clear();
	this_thread::sleep_for(chrono::seconds(3));
}

void phaseDefausse(int i)
{
	if (joueurs[i]->getDeck().size() > 7)
	{
		system("cls");
		int nbDef = joueurs[i]->getDeck().size() - 7;
		cout << endl << joueurs[i]->getName() << u8" vous avez plus de 7 cartes, il faut donc défausser " << nbDef << " carte(s).";
		cout << endl << u8"Voici votre deck : " << endl;
		deck(i);
		string name;
		for (int nb = 0; nb < nbDef; nb++)
		{
			cout << endl << u8"Quelle carte souhaitez vous défausser ? : ";
			cin >> name;
			while (not inDeck(i, name))
			{
				cout << endl << u8"Carte non valide, veuillez saisir une carte : " << endl;
				cin >> name;
			}
			joueurs[i]->removeCarte(name);
			defausse.push_back(name);
			cout << endl << u8"Carte défaussée : " << name << endl;
		}
	}
}

void verifDaimyo(int i)
{
	int nbDaimyo = 0;
	for (const auto& carte : joueurs[i]->getCarteAction())
	{
		if (carte[0] == "daimyo")
		{
			nbDaimyo += 1;
		}
	}
	if (nbDaimyo != 0 && joueurs[i]->getRole() != "ronin")
	{
		joueurs[i]->setPointHonneur(joueurs[i]->getPointHonneur() + 1);
	}
}

void victoireEpe(string attaquant,string cible, int nb_joueur)
{
	int statut = 1;
	int nbDead = 0;
	for (const auto& joueur : joueurs)
	{
		if (joueur->getStatut() == false)
		{
			nbDead += 1;
		}
	}
	if (nbDead == nb_joueur - 1)
	{
		if (joueurs[getPosByName(attaquant, nb_joueur)]->getRole() != joueurs[getPosByName(cible, nb_joueur)]->getRole())
		{
			cout << endl << u8"L'équipe " << joueurs[getPosByName(attaquant, nb_joueur)]->getRole() << u8"à gagné la partie !!";
			exit(0);
		}
	}
}

void finGame(string attaquant, string cible, int nb_joueur)
{
	int csc = 0;
	bool traitre = false;
	int daimyo;
	int point;
	int pointMax = 0;
	string winner;
	int statut = 1;
	int ninja = -1;
	string ninjaName;
	if (joueurs[getPosByName(attaquant, nb_joueur)]->getRole() == joueurs[getPosByName(cible, nb_joueur)]->getRole())
	{
		traitre = true;
	}
	for (const auto& joueur : joueurs)
	{
		if (joueur->getPointHonneur() <= 0)
		{
			statut = 0;
		}
	}
	if (statut == 0)
	{
		// Attribution Etoiles
		for (const auto& joueur : joueurs)
		{
			if (joueur->getRole() == "ninja")
			{
				if (nb_joueur == 4)
				{
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<> dis(0, 2);
					int randomNumber = dis(gen);
					int random = randomNumber;
					while (randomNumber == ninja)
					{
						int randomNumber = dis(gen);
						int random = randomNumber;
					}
					if (randomNumber > ninja)
					{
						ninjaName = joueur->getName();
					}
				}
			}
		}
		// Calcul Points
		for (const auto& joueur : joueurs)
		{
			if (nb_joueur == 4)
			{
				if (joueur->getRole() == "shogun")
				{
					daimyo = 0;
					for (const auto& cartes: joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = joueur->getPointHonneur()+ daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << joueur->getPointHonneur() << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "samouraï")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = 2*(joueur->getPointHonneur()) + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}
				
				if (joueur->getRole() == "ninja")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (joueur->getName() == ninjaName)
					{
						if (traitre && joueur->getName() == cible)
						{
							csc = 3;
						}
						point = 2 * (joueur->getPointHonneur()) + daimyo - csc;
						csc = 0;
					}
					else
					{
						if (traitre && joueur->getName() == cible)
						{
							csc = 3;
						}
						point = (joueur->getPointHonneur()) + daimyo - csc;
						csc = 0;

					}
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}
			}

			if (nb_joueur == 5)
			{
				if (joueur->getRole() == "shogun")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = joueur->getPointHonneur() + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << joueur->getPointHonneur() << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "samouraï")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = joueur->getPointHonneur() + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "ninja")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = joueur->getPointHonneur() + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "ronin")
				{
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = 2*(joueur->getPointHonneur()) - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}
			}

			if (nb_joueur == 6)
			{
				if (joueur->getRole() == "shogun")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = joueur->getPointHonneur() + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << joueur->getPointHonneur() << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "samouraï")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = 2*(joueur->getPointHonneur()) + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "ninja")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = joueur->getPointHonneur() + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "ronin")
				{
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = 3 * (joueur->getPointHonneur()) - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}
			}

			if (nb_joueur == 7)
			{
				if (joueur->getRole() == "shogun")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = joueur->getPointHonneur() + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << joueur->getPointHonneur() << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "samouraï")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = joueur->getPointHonneur() + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "ninja")
				{
					daimyo = 0;
					for (const auto& cartes : joueur->getDeck())
					{
						if (cartes == "daimyo")
						{
							daimyo += 1;
						}
					}
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = joueur->getPointHonneur() + daimyo - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}

				if (joueur->getRole() == "ronin")
				{
					if (traitre && joueur->getName() == cible)
					{
						csc = 3;
					}
					point = 3 * (joueur->getPointHonneur()) - csc;
					csc = 0;
					cout << endl << joueur->getName() << u8" vous avez " << point << u8" points." << endl;
					if (point > pointMax)
					{
						pointMax = point;
						winner = joueur->getRole();
					}
				}
			}
		}
		cout << endl << u8"L'équipe gagnante est " << winner << endl;
		exit(0);
	}
}

// defausser parade dans cri de guerre // Déjà fais
// mettre le nom du joueur dans cri de guerre dans le cout des 2 possibiltés // Déjà fais
