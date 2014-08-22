#ifndef SKILLTREE_H
#define SKILLTREE_H
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "node.h"

using namespace std;
using namespace rapidjson;

class SkillTree
{
	private:
	string data;
	public:
	//SkillTree(arguments);
	//~SkillTree();
	void assignData();
	char checkInput();
	void switchOption(char);
	void printMenu();
	void executeSkillTree();
	void connectToWebsite();
	void readFromTextFile();
	void executeShortestPath();
	string findShortestPath(std::vector<Node>, int,int);
	void initialize();
	int getClosestUnmarkedNode();
	void calculateDistance();
	string output();
    string printPath(int);
    int getNodeIDFromIndex(int);
    int getIndexFromNodeID(int);
    void optimizeStrategy(int);
    int chooseCharacterMenu();
    void create2dArrayForBigMap(vector<Node>);
    void savePath();
    void loadPath();


	/* data */
};

#endif