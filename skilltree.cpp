#include "skilltree.h"
#include <fstream>
#include <sstream>
#include <iomanip>


const char maximizeIntelligenceOption = 'I';
const char maximizeDeterityOption = 'D';
const char maximizeStrengthOption = 'S';
const char printMenuOption = 'M';
const char shortestPathOption = 'P';
const char quitOption = 'Q';
const char saveOption = 'C';
const char loadOption = 'L';

vector<Node> nodesVector;


int** adjMatrix;
int* predecessor;
int* distanceAray;
bool* mark; //keep track of visited node
int source;
int numOfVertices;
int endPosition;
string path="";

#define INFINITY 999

//checking the user input 
char SkillTree::checkInput()
{
	string userInput;
	cin >> userInput;
	if(userInput.size() > 1){
		return 'x';
	}else{
		return toupper(userInput.at(0));
	}
}

//switch option
void SkillTree::switchOption(char option)
{
	switch(option)
	{  
		case shortestPathOption :  
			executeShortestPath();
			cout << "\n";
			break;

		case maximizeIntelligenceOption :  
			optimizeStrategy(1);
			cout << "\n";
			break;

		case maximizeDeterityOption :  
			optimizeStrategy(2);
			cout << "\n";
			break;

		case maximizeStrengthOption :  
			optimizeStrategy(3);
			cout << "\n";
			break;

		case printMenuOption:  
			printMenu();
			cout << "\n";
			break;

		case saveOption:  
			savePath();
			cout << "\n";
			break;

		case loadOption:  
			loadPath();
			cout << "\n";
			break;

		case quitOption:  
			cout << "\tThe Skill Tree Optimization Program is shutting down\n\n";
			break;

		default: cerr << "\tWrong input option!!! Enter m for showing menu again\n";
			break;

	}
}

void SkillTree::printMenu()
{
	cout << "\t\t---------------SKILL TREE OPTIMIZATION---------------\n";
	cout << "\tOption p:	Shortest path\n";
	cout << "\tOption i: 	Maximize Intelligence\n";
	cout << "\tOption d: 	Maximize Dexterity\n";
	cout << "\tOption s: 	Maximize Strength\n";
	cout << "\tOption m:	Show menu\n";
	cout << "\tOption c:	Save Path\n";
	cout << "\tOption l:	Load Path\n";
	cout << "\tOption q:	Quit the program\n\n";
	cout << "\tEnter your option: ";
}

void SkillTree::executeSkillTree()
{
	cout << "\n\tCONNECTING TO PATH OF EXILE WEBSITE.......\n";
	//check if the file exist => read from the file => add to data
	if(fstream("passive_skill_tree.txt"))
	{
		readFromTextFile();
	}else{
		//if file not exist => connect to website and download infor
		connectToWebsite();
	}

	assignData();
	create2dArrayForBigMap(nodesVector);

	char userInput;
	cout << "\n\tWELLCOME TO THE SKILL TREE OPTIMIZATION PROGRAM\n\n";
	cout << "\tCHOOSE YOUR COMMAND FROM THE MENU BELOW \n\n";
	printMenu();
	cout << "\n";
	do
	{
		cout << "> \t" ;
		userInput = checkInput();
		switchOption(userInput);		

	} while (!(userInput == quitOption)) ;
}

// function return how many size the program handled
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void SkillTree::connectToWebsite()
{
	CURL *curl;
	string source;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.pathofexile.com/passive-skill-tree");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &source);
	curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	size_t start = source.find("var passiveSkillTreeData = ");
	size_t end = source.find("0.3835]}");
	data = source.substr(start+27,end-start - 19);
	
	//to make the program run faster we just need to connect to the website 1 time then we write the ritrival webpage to text file
	//then next time run the program we just need read from the text file => much faster
	
	//write to file
	ofstream myfile;
	myfile.open ("passive_skill_tree.txt");
	myfile << data;
	myfile.close();
}

void SkillTree::assignData()
{
	Document document;

	if ( document.Parse<0>( data.c_str() ).HasParseError() ) {
    	cout << "Error parsing" << std::endl;
	} else {

		const Value& node = document["nodes"];
        for (SizeType i = 0; i < node.Size(); ++i)
        {
        	
        	StringBuffer sb;
        	Writer<StringBuffer> writer( sb );
	        document[ "nodes" ][i].Accept( writer );
	        
	        Document skills;
	        
	        if ( skills.Parse<0>( sb.GetString() ).HasParseError() ) {
	    		cout << "Error parsing" << std::endl;
			} else {
				vector<int> connectedNode;
				vector<string> skillsEffect;
			
				//connected nodes
				const Value& cnode = skills["out"];
				for (SizeType i = 0; i < cnode.Size(); ++i)
        		{
        			connectedNode.push_back(cnode[i].GetInt());
        		}

        		//if(cnode.Size() == 0){ connectedNode.push_back(0); };

        		//skills effect
				const Value& effect = skills["sd"];
				for (SizeType i = 0; i < effect.Size(); ++i)
        		{
        			skillsEffect.push_back(effect[i].GetString());
        		}

        		//if(effect.Size() == 0){ skillsEffect.push_back("No Effect"); };      		

        		Node n = Node(skills["id"].GetInt(),skills["dn"].GetString(),skillsEffect,connectedNode);
				nodesVector.push_back(n);
			}
		}
	}	
}

void SkillTree::readFromTextFile()
{
	//read from file => add to data
	ifstream myfile ("passive_skill_tree.txt");
  	if (myfile.is_open())
  	{
    	getline (myfile,data);
    	myfile.close();
  	}else{ cout << "Unable to open file"; }
	
}

int SkillTree::chooseCharacterMenu()
{
	/*
	0 	-	Scion		- node 58833 ( can be) 
1	-	Marauder	- node 47175
			2	-	Ranger	- node 50459
			3 	-	Witch		- node 54447
			4 	-	Duelist	- node 50986
			5	-	Templar	- node 61525
			6	-	Shadow	- node 44683
	*/
	int charID;		
	cout << "\n\tChoose your character\n";
	cout << "\t1 -  Marauder\n";
	cout << "\t2 -  Ranger\n";
	cout << "\t3 -  Witch\n";
	cout << "\t4 -  Duelist\n";
	cout << "\t5 -  Templar\n";
	cout << "\t6 -  Shadow\n";
	cout << "\t0 -  Scion\n";
	cout << "\tEnter your choice: ";
	cout << "\n> \t";
	cin >> charID;
	int characterID[7] = {58833,47175,50459,54447,50986,61525,44683};
	int startPosition = characterID[charID];
	return startPosition;
}

void SkillTree::executeShortestPath()
{
	int start =  chooseCharacterMenu();	
	cout << "\tEnter destination ID: ";
	cout << "\n> \t";
	int endP;
	cin >> endP;
	// 47175 -> 31628 -> 9511 -> 23881 -> 26523
	cout << "\n\t Shortest Path: \n";
	path =	findShortestPath(nodesVector,start,endP);
	cout << path;
	//read();
}
void SkillTree::create2dArrayForBigMap(vector<Node> v)
{
	int size = v.size();
	
	adjMatrix = new int*[size];
	predecessor = new int [size];
	distanceAray = new int [size];
	mark = new bool [size]; 

	for (int i = 0; i < size; ++i)
	{
		adjMatrix[i] = new int[size];
	}

		/* Initilize 2d array */
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		for (unsigned int j = 0; j < v.size(); ++j)
		{
			adjMatrix[i][j] = INFINITY;
		}
	}

	//cout << "Read from vector " << v.size() << endl;
	for (unsigned int i = 0; i <  v.size() ; i++){
		Node currNode = v.at(i);
		std::vector<int> connectedNodes = currNode.getConnectedNodes();

		for (unsigned int j = 0; j < connectedNodes.size(); ++j)
		{
			// cout << "\t" << connectedNodes.at(j) << endl; 
			int indexI = getIndexFromNodeID(currNode.getNodeID());
			int indexJ = getIndexFromNodeID(connectedNodes.at(j));

			if (indexI == indexJ){
				adjMatrix[indexI][indexJ] = 0;	
			}
			adjMatrix[indexI][indexJ] = 1;
			adjMatrix[indexJ][indexI] = 1;

		}
	}
}

string SkillTree::findShortestPath(vector<Node> v, int start,int end){
	//source = getIndexFromNodeID(start);
	
	endPosition = end;
	numOfVertices = v.size();
	source = getIndexFromNodeID(start);
	//cout << "Start Index: " << source << "\n";
	//cout << "End Index: " << getIndexFromNodeID(endPosition) << "\n";
	

	/* Initilize 2d array */
	/*
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		for (unsigned int j = 0; j < v.size(); ++j)
		{
			adjMatrix[i][j] = INFINITY;
		}
	}

	//cout << "Read from vector " << v.size() << endl;
	for (unsigned int i = 0; i <  v.size() ; i++){
		Node currNode = v.at(i);
		std::vector<int> connectedNodes = currNode.getConnectedNodes();

		for (unsigned int j = 0; j < connectedNodes.size(); ++j)
		{
			// cout << "\t" << connectedNodes.at(j) << endl; 
			int indexI = getIndexFromNodeID(currNode.getNodeID());
			int indexJ = getIndexFromNodeID(connectedNodes.at(j));

			if (indexI == indexJ){
				adjMatrix[indexI][indexJ] = 0;	
			}
			adjMatrix[indexI][indexJ] = 1;
			adjMatrix[indexJ][indexI] = 1;

		}

		
	}
	*/

	
	// for (int i = 0; i < 5; ++i)
 //    {
 //    	for (int j = 0; j < 5; ++j)
 //    	{
 //    		cout << getNodeIDFromIndex(i) << " - " << getNodeIDFromIndex(j) << endl;
 //    		cout << adjMatrix[i][j] << endl;
    		
 //    	}
 //    	cout << endl;
 //    }


    calculateDistance();
	return output();
}


int SkillTree::getIndexFromNodeID(int nodeID){
	for (unsigned int i = 0; i < nodesVector.size(); ++i)
	{
		if ( nodesVector.at(i).getNodeID() == nodeID ){
			return i;
		}

	}
	return -1;
}

int SkillTree::getNodeIDFromIndex(int index){
	return nodesVector.at(index).getNodeID();
}

void SkillTree::initialize(){
    for(int i=0;i<numOfVertices;i++) {
        mark[i] = false;
        predecessor[i] = -1;
        distanceAray[i] = INFINITY;
    }
    distanceAray[source]= 0;
}
 
 
int SkillTree::getClosestUnmarkedNode(){
    int minDistance = INFINITY;
    int closestUnmarkedNode;

    for(int i=0; i < numOfVertices; i++) {
        if((!mark[i]) && ( minDistance >= distanceAray[i])) {
            minDistance = distanceAray[i];
            closestUnmarkedNode = i;
        }
    }
    /*
        for(int i = numOfVertices; i > 0; i--) {
        if((!mark[i]) && ( minDistance >= distanceAray[i])) {
            minDistance = distanceAray[i];
            closestUnmarkedNode = i;
        }
    }
    */
    return closestUnmarkedNode;
}
 
 
void SkillTree::calculateDistance(){
	//cout << "calculateDistance" << endl;
    initialize();
    int closestUnmarkedNode;
    int count = 0;
    while(count < numOfVertices) {
        closestUnmarkedNode = getClosestUnmarkedNode();
        mark[closestUnmarkedNode] = true;
        for(int i=0;i< numOfVertices;i++) {
            if((!mark[i]) && (adjMatrix[closestUnmarkedNode][i] > 0 ) ) {
                if(distanceAray[i] > distanceAray[closestUnmarkedNode]+ adjMatrix[closestUnmarkedNode][i]) {
                    distanceAray[i] = distanceAray[closestUnmarkedNode]+ adjMatrix[closestUnmarkedNode][i];
                    predecessor[i] = closestUnmarkedNode;
                }else{
                	// cout << "closestUnmarkedNode " << getNodeIDFromIndex(closestUnmarkedNode) << endl;
                	// cout << "Distance " << adjMatrix[closestUnmarkedNode][i] << endl;
                	// cout << "------------" << endl;
                }
            }
        }
        count++;
    }
    //cout << "End calculateDistance" << endl;
}
 
 
string SkillTree::printPath(int desIndex){

	ostringstream ost;

    if(desIndex == source)
    	ost << getNodeIDFromIndex(desIndex) <<"..";
        //cout<< getNodeIDFromIndex(desIndex) <<"..";
    else if(predecessor[desIndex] == -1){
    	ost << "Node with no predecessor" << getNodeIDFromIndex(desIndex) << endl;
        ost<<"No path from "<< getNodeIDFromIndex(source) << " to "<< getNodeIDFromIndex(desIndex) <<endl;
    }
    else {
        ost << printPath(predecessor[desIndex]);
        ost << getNodeIDFromIndex(desIndex) <<"..";
    }
    string s = ost.str();
    return s;
}
 
 
string SkillTree::output(){

    int desIndex = getIndexFromNodeID(endPosition);
    //printPath(desIndex);
    //cout<<"->"<<distanceAray[desIndex]<<endl;
    ostringstream ost;
	ost << printPath(desIndex) << "\n";
	string s = ost.str();
    return s;
}

void SkillTree::savePath()
{
	//write to file

	ofstream myfile;
	myfile.open ("path.txt");
	myfile << path;
	myfile.close();
	cout << "Current Path has been saved!"<<"\n";

}

void SkillTree::loadPath()
{
	//read from file => add to data
	ifstream myfile ("path.txt");
  	if (myfile.is_open())
  	{
    	getline (myfile,path);
    	myfile.close();
  	}else{ cout << "Unable to open file"; }
  	cout << "Old Path: " << path <<"\n";
}

void SkillTree::optimizeStrategy(int type){
	int start = chooseCharacterMenu();

	std::vector<int> v;
	if (type == 1)
	{
		cout << "\n\tOptimization max Intelligence\n";
		for (unsigned int i = 0; i < nodesVector.size(); ++i)
		{
			Node currNode = nodesVector.at(i);
			std::vector<string> effects = currNode.getSkillsEffect();
			

			for (unsigned int j = 0; j < effects.size(); ++j)
			{
				
				string e = effects.at(j);
				if (e.find("to Intelligence") != string::npos){
					cout << "Node ID: " << currNode.getNodeID() << "\n";
					cout << "Effect: " << effects.at(j) << "\n";
					cout << "---------------" << "\n";
					v.push_back(currNode.getNodeID());
				}

			}
		}
	}else if(type == 2){
		cout << "\n\tOptimization max Dexterity\n";
		for (unsigned int i = 0; i < nodesVector.size(); ++i)
		{
			Node currNode = nodesVector.at(i);
			std::vector<string> effects = currNode.getSkillsEffect();
			

			for (unsigned int j = 0; j < effects.size(); ++j)
			{
				
				string e = effects.at(j);
				if (e.find("to Dexterity") != string::npos){
					cout << "Node ID: " << currNode.getNodeID() << "\n";
					cout << "Effect: " << effects.at(j) << "\n";
					cout << "---------------" << "\n";
					v.push_back(currNode.getNodeID());
				}

			}
		}		
	}else{
		cout << "\n\tOptimization max Strength\n";
		for (unsigned int i = 0; i < nodesVector.size(); ++i)
		{
			Node currNode = nodesVector.at(i);
			std::vector<string> effects = currNode.getSkillsEffect();
			

			for (unsigned int j = 0; j < effects.size(); ++j)
			{
				
				string e = effects.at(j);
				if (e.find("to Strength") != string::npos){
					cout << "Node ID: " << currNode.getNodeID() << "\n";
					cout << "Effect: " << effects.at(j) << "\n";
					cout << "---------------" << "\n";
					v.push_back(currNode.getNodeID());
				}

			}
		}			
	}
	
	cout << "\n";
	path = findShortestPath(nodesVector,start, v.at(0));
	cout << path;
	cout << "";
	for (unsigned int i = 0; i < v.size() - 1; i++)
	{
		int nextNode = i + 1;
		path += findShortestPath(nodesVector,v.at(i), v.at(nextNode));
		cout << path;

	}
	
}