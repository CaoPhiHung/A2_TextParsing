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