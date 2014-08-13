#include "route.h"

int Route::get_total_str(){
    stack<Node> temp = this->get_stack_nodes();
    int total = 0;

    while (!temp.empty()){
        Node node = temp.top();
        total += node.get_str();
        temp.pop();
    }
    return total;
}

int Route::get_total_dex(){
    stack<Node> temp = this->get_stack_nodes();
    int total = 0;

    while (!temp.empty()){
        Node node = temp.top();
        total += node.get_dex();
        temp.pop();
    }
    return total;
}

int Route::get_total_intel(){
    stack<Node> temp = this->get_stack_nodes();
    int total = 0;

    while (!temp.empty()){
        Node node = temp.top();
        total += node.get_intel();
        temp.pop();
    }
    return total;
}
