#ifndef NODE_H
#define	NODE_H

#include <cstdlib>
#include <fstream>
#include <map>
#include <iomanip>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <curl/curl.h>

using namespace std;

class Node {
    private:
        long int skill_id;
        string skill_name;
        int str;
        int dex;
        int intel;
        vector<string> skill_effect;
        vector<long int> connected_nodes;
    public:
        Node(long int _skill_id, string _skill_name, int _str, int _dex, int _intel, vector<string> _skill_effect, vector<long int> _connected_nodes) : skill_id(_skill_id), skill_name(_skill_name), str(_str), dex(_dex), intel(_intel), skill_effect(_skill_effect), connected_nodes(_connected_nodes) {
        }

        Node(){
        }

        int get_str(){
            return this->str;
        }

        int get_dex(){
            return this->dex;
        }

        int get_intel(){
            return this->intel;
        }

        void add_skill_effect(string _effect);

        void add_connected_node(long int _node);

        void set_skill_id(long int _skill_id){
            this->skill_id = _skill_id;
        }

        void set_skil_name(string _skill_name){
            this->skill_name = _skill_name;
        }

        void set_skill_effect(vector<string> _skill_effect);

        void set_connected_nodes(vector<long int> _connected_nodes);

        string get_skill_name(){
          return this->skill_name;
        }

        long int get_skill_id(){
          return this->skill_id;
        }

        vector<string> get_skill_effect(){
          return this->skill_effect;
        }

        vector<long int> get_connected_nodes(){
          return this->connected_nodes;
        }

        void set_str(int _str){
            this->str = _str;
        }

        void set_dex(int _dex){
            this->dex = _dex;
        }

        void set_intel(int _intel){
            this->intel = _intel;
        }
};

#endif
