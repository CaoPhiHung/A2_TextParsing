#ifndef SKILLS_H
#define	SKILLS_H

#include "node.h"

using namespace std;

class Skills : public Node
{
    private:
    int nodeID;
    string name;
    string skillsEffect;
    vector<int> connectedNodes;

public:
    //Skills();
    //virtual ~Skills();
    Skills(int nodeID,string name,string skillsEffect,vector<int> connectedNodes);
    string getSkillsEffect();
};

#endif