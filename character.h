#ifndef CHARACTER_H
#define	CHARACTER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Character
{
	private:
	int id;
    string name;
    int str;
    int dex;
    int intel;
    vector<long int> connected_nodes;

public:
    Character(){}
    virtual ~Character (){}
};

#endif
