#include "role.h"

using namespace std;

Role::Role(string role)
{
	this->role = role;
}

string Role::getRole()
{
	return this->role;
}
