#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Node
{
    private:
    int nodeID;
    string name;
    vector<int> connectedNodes;

public:
    Node();
    virtual ~Node();
};

#endif