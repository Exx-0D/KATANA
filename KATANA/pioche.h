#include <string>
#include <iostream>

using namespace std;

#ifndef PIOCHE_H
#define PIOCHE_H

class Pioche {

public:

	Pioche(string name, int number, int attaque, int portee, string capacity, string type);

	void setNumber(int number);

	string getName();
	int getNumber();
	int getAttaque();
	int getPortee();
	string getCapacity();
	string getType();


private:
	string name;
	int number;
	int attaque;
	int portee;
	string capacity;
	string type;
};

#endif