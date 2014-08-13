#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

string data;

// function return how many size the program handled
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{	
	//check if the file exist => read from the file => add to data
	if(fstream("passive_skill_tree.txt"))
	{
		//read from file => add to data
		ifstream myfile ("passive_skill_tree.txt");
  		if (myfile.is_open())
  		{
    		while ( getline (myfile,data) )
    		{
      			//cout << data << '\n';
    		}
    		myfile.close();
  		}else{ cout << "Unable to open file"; }

  		Document document;
		if ( document.Parse<0>( data.c_str() ).HasParseError() ) {
    		std::cout << "Error parsing" << std::endl;
		} else {
    		if ( document[ "characterData" ].IsObject() ) {
        		rapidjson::StringBuffer sb;
        		rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
        		document[ "characterData" ].Accept( writer );
        		std::cout << sb.GetString() << std::endl;
    		}
		}
	}else{
		//if file not exist => connect to website and download infor
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
		
	    //write to file
		ofstream myfile;
	  	myfile.open ("passive_skill_tree.txt");
	  	myfile << data;
	  	myfile.close();

	}

  return 0;
}