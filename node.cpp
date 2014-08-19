#include "node.h"

Node::Node(int id, string nodeName, vector<string> skills, vector<int> node)
{
	this->nodeID = id;
	this->name = nodeName;
	this->skillsEffect = skills;
	this->connectedNodes = node;
}

int Node::getNodeID()
{
	return nodeID;
}

string Node::getName()
{
	return name;
}

vector<string> Node::getSkillsEffect()
{
	return skillsEffect;
}

vector<int> Node::getConnectedNodes()
{
	return connectedNodes;
}

void Node::toString(){
	cout << "Node ID " << nodeID << endl;
	if (skillsEffect.size() == 0) return;
	for (unsigned int i = 0; i < skillsEffect.size(); ++i)
	{
		cout << skillsEffect.at(i) << endl;
	}
	cout << "--------------------" << endl;
}