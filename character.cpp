#include "character.h"

void Character::set_char_name(string _char_name){
    this->char_name = _char_name;
}

void Character::set_char_id(long int _char_id){
    this->char_id = _char_id;
}

void Character::set_connected_nodes(vector<long int> _connected_nodes){
    this->connected_nodes = _connected_nodes;
}
