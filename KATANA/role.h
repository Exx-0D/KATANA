#include <string>
#include <iostream>

using namespace std;

#ifndef ROLE_H
#define ROLE_H

class Role {

public:
	Role(string role);
	string getRole();

private:
	string role;


};

#endif