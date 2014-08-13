#include "node.h"


void Node::set_skill_effect(vector<string> _skill_effect){
    this->skill_effect = _skill_effect;
}

void Node::set_connected_nodes(vector<long int> _connected_nodes){
    this->connected_nodes = _connected_nodes;
}

void Node::add_skill_effect(string _effect){
    this->skill_effect.push_back(_effect);
}

void Node::add_connected_node(long int _node){
    this->connected_nodes.push_back(_node);
}
