#include "pioche.h"
#include <string>
#include <iostream>

Pioche::Pioche(string name, int number, int attaque, int portee, string capacity, string type)
{
	this->name = name;
	this->number = number;
	this->attaque = attaque;
	this->portee = portee;
	this->capacity = capacity;
	this->type = type;
}

void Pioche::setNumber(int number)
{
	this->number = number;
}

string Pioche::getName()
{
	return this->name;
}

int Pioche::getNumber()
{
	return this->number;
}

int Pioche::getAttaque()
{
	return this->attaque;
}

int Pioche::getPortee()
{
	return this->portee;
}

string Pioche::getCapacity()
{
	return this->capacity;
}

string Pioche::getType()
{
	return this->type;
}




