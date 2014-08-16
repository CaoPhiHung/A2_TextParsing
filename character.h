#ifndef CHARACTER_H
#define	CHARACTER_H
#include "node.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Character : public Node
{
	private:
	char characterID;
	int nodeID;
    string name;
    int str;
    int dex;
    int intel;
    vector<int> connectedNodes;
public:
    //Character();
    //virtual ~Character();
    Character(char characterID,int nodeID,string name,int str,int dex,int intel,vector<int> connectedNodes);
   	char getCharacterID();
   	int getStr();
   	int getDex();
   	int getIntel();
};

#endif
