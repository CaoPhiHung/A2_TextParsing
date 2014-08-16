#include "skills.h"

Skills::Skills(int id,string skillName,string effect,vector<int> node)
{
	this->nodeID = id;
	this->name = skillName;
	this->skillsEffect = effect;
	this->connectedNodes = node;
}

string Skills::getSkillsEffect()
{
	return skillsEffect;
}