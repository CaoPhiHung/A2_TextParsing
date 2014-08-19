#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node
{
    private:
    int nodeID;
    string name;
    vector<string> skillsEffect;
    vector<int> connectedNodes;
   
	public:
	//Node();
    //virtual ~Node();
	Node(int id, string name, vector<string> skillsEffect, vector<int> node);
    int getNodeID();
    string getName();
    vector<string> getSkillsEffect();
    vector<int> getConnectedNodes();
    void toString();

};

#endif