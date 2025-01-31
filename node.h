#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    void killSelf(){
        if (this->prev) {
            this->prev = nullptr;
            this->next->killSelf();
            delete this;

        }

    }
    void print_next();
};

#endif
