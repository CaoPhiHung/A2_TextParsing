#ifndef SKILLTREE_H
#define SKILLTREE_H
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

#include "node.h"
#include "skills.h"
#include "character.h"

class SkillTree
{
	private:
	string data;
	public:
	//SkillTree(arguments);
	//~SkillTree();
	void AssignSkillsData();
	void AssignCharacterData();
	char checkInput();
	void switchOption(char);
	void printMenu();
	void executeSkillTree();
	void connectToWebsite();
	void readFromTextFile();
	/* data */
};

#endif