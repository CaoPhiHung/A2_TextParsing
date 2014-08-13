#ifndef CHARACTER_H
#define	CHARACTER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Character
{
private:
    string char_name;
    long int char_id;
    int str;
    int dex;
    int intel;
    vector<long int> connected_nodes;

public:
    Character(){}

    Character(string _char_name, long int _char_id, vector<long int> _connected_nodes) : char_name(_char_name), char_id(_char_id), connected_nodes(_connected_nodes){}

    string get_char_name(){
        return this->char_name;
    }

    long int get_char_id(){
        return this->char_id;
    }

    vector<long int> get_connected_nodes(){
        return this->connected_nodes;
    }

    void set_char_name(string _char_name);

    void set_char_id(long int _char_id);

    void set_connected_nodes(vector<long int> _connected_nodes);

    virtual ~Character (){}
};

#endif
