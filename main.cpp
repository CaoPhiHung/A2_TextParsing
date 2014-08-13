#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>

using namespace std;

// function return how many size the program handled
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
	CURL *curl;
	CURLcode result; // store result of of CURL's webpage retrieval => error checking
	string source;
	string data;
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



  return 0;
}