#include "character.h"

Character::Character(char charID,int id,string charName,int strength,int dexterity,int intelligence,vector<int> node)
{
	this->characterID = charID;
	this->nodeID = id;
	this->name = charName;
	this->str = strength;
	this->dex = dexterity;
	this->intel = intelligence;
	this->connectedNodes = node;
}

char Character::getCharacterID()
{
	return characterID;
}

int Character::getStr()
{
	return str;
}

int Character::getDex()
{
	return dex;
}

int Character::getIntel()
{
	return intel;
}

