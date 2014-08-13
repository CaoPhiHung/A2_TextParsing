#ifndef ROUTE_H
#define	ROUTE_H

#include <stack>

#include "node.h"


using namespace std;

class Route 
{
    private:
        int num_steps;
        stack<Node> nodes;
    public:
        Route(){
        }

        Route(stack<Node> _nodes) : nodes(_nodes){
            this->num_steps = this->nodes.size() - 1;
        }

        stack<Node> get_stack_nodes(){
            return this->nodes;
        }

        int get_num_steps(){
            return this->num_steps;
        }

        int get_total_str();
        int get_total_dex();
        int get_total_intel();

};

#endif
