#include "skilltree.h"

const char maximizeIntelligenceOption = 'I';
const char maximizeDeterityOption = 'D';
const char maximizeStrengthOption = 'S';
const char printMenuOption = 'M';
const char shortestPathOption = 'P';
const char quitOption = 'Q';

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
			cout << "shortestPathOption";
			cout << "\n";
			break;

		case maximizeIntelligenceOption :  
			cout << "Intelligence";
			cout << "\n";
			break;

		case maximizeDeterityOption :  
			cout << "Deterity";
			cout << "\n";
			break;

		case maximizeStrengthOption :  
			cout << "Strength";
			cout << "\n";
			break;

		case printMenuOption:  
			printMenu();
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
	cout << "\tOption d: 	Maximize Deterity\n";
	cout << "\tOption s: 	Maximize Strength\n";
	cout << "\tOption m:	Show menu\n";
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



	char userInput;
	cout << "\n\tWELLCOME TO THE SKILL TREE OPTIMIZATION PROGRAM\n\n";
	cout << "\tCHOOSE YOUR COMMAND FROM THE MENU BELOW \n\n";
	printMenu();
	cout << "Enter your command: \n\n";
	
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
	CURLcode result; // store result of of CURL's webpage retrieval => error checking
	string source;
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.pathofexile.com/passive-skill-tree");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &source);
	result = curl_easy_perform(curl);
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

void SkillTree::AssignCharacterData()
{
	Document document;
	if ( document.Parse<0>( data.c_str() ).HasParseError() ) {
    	cout << "Error parsing" << std::endl;
	} else {

    	const Value& a = document["nodes"];
	   	
	   	if(a.IsArray()){
	   		cout << "True\n";
	   	}   
        //on1 json object in array
        for (SizeType i = 0; i < a.Size(); ++i)
        {
        	StringBuffer sb;
        	Writer<rapidjson::StringBuffer> writer( sb );
	        document[ "nodes" ][i].Accept( writer );
	        //std::cout << sb.GetString() << std::endl;
	        Document skills;
	        if ( skills.Parse<0>( sb.GetString() ).HasParseError() ) {
	    		cout << "Error parsing" << std::endl;
			} else {
				cout << skills["id"].GetInt() << " connect to ";
				const Value& b = skills["out"];
				 for (SizeType i = 0; i < b.Size(); ++i)
        		{
        			cout << b[i].GetInt() << " " <<"\n";
        		}
				
			}
		}
	}
}

void SkillTree::AssignSkillsData()
{
	Document document;
	if ( document.Parse<0>( data.c_str() ).HasParseError() ) {
    	cout << "Error parsing" << std::endl;
	} else {

    	const Value& a = document["nodes"];
	   	
	   	if(a.IsArray()){
	   		cout << "True\n";
	   	}   
        //on1 json object in array
        for (SizeType i = 0; i < a.Size(); ++i)
        {
        	StringBuffer sb;
        	Writer<rapidjson::StringBuffer> writer( sb );
	        document[ "nodes" ][i].Accept( writer );
	        //std::cout << sb.GetString() << std::endl;
	        Document skills;
	        if ( skills.Parse<0>( sb.GetString() ).HasParseError() ) {
	    		cout << "Error parsing" << std::endl;
			} else {
				cout << skills["id"].GetInt() << " connect to ";
				const Value& b = skills["out"];
				 for (SizeType i = 0; i < b.Size(); ++i)
        		{
        			cout << b[i].GetInt() << " " <<"\n";
        		}
				
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