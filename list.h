#ifndef LIST_H
#define LIST_H

#include "iterator.h"
#include "node.h"
#include <iostream>

using namespace std;

template <typename T> class List {
private:
  Node<T> *start;
  int nodes;

public:
  List() {
    this->start = nullptr;
    this->nodes = 0;
  }
  T front() {
    if (this->size()) {
      return this->start->data;
    }
  }
  T back() {
    if (this->size()) {
      return this->start->prev->data;
    }
  }

  void push_front(T value) {
    Node<T> *node = new Node<T>;
    node->data = value;

    if (this->size()) {

      node->next = this->start;
      node->prev = this->start->prev;

      node->next->prev = node;
      node->prev->next = node;

    } else {
      node->prev = node;
      node->next = node;
    }
    (this->nodes)++;
    this->start = node;
  }
  void push_back(T value) {
    Node<T> *node = new Node<T>;
    node->data = value;

    if (this->size()) {

      node->next = this->start;
      node->prev = this->start->prev;

      node->next->prev = node;
      node->prev->next = node;

    } else {
      node->prev = node;
      node->next = node;
      this->start = node;
    }

    (this->nodes)++;
  }
  void pop_front() {

    if (this->size() > 1) {
      this->start->prev->next = this->start->next;
      this->start->next->prev = this->start->prev;

      Node<T> *node = this->start;
      this->start = this->start->next;
      (this->nodes)--;

      delete node;
    } else if (this->size() == 1) {
      // TODO: check if this erases the pointer to a node, it has to be nullptr;
      delete this->start;
      (this->nodes)--;
    } else {
      cout << "Segmentation Fault, list is already empty. \n";
    }
  }
  void pop_back() {

    if (this->size() > 1) {
      Node<T> *node = this->start->prev;

      this->start->prev->prev->next = this->start;
      this->start->prev = this->start->prev->prev;

      (this->nodes)--;
      delete node;

    } else if (this->size() == 1) {
      // check if this erases the pointer to a node, it has to be nullptr;

      delete this->start;
      this->start = nullptr;

      (this->nodes)--;

    } else {
      cout << "Segmentation Fault, list is already empty. \n";
    }
  }

  T get(int position) {
    int size_of_list = this->size();
    if (size_of_list) {
      position = (position % size_of_list);
      Node<T> *node = this->start;
      if (position < size_of_list / 2) {
        while (position--) {
          node = node->next;
        }
      } else {
        while (position++ != size_of_list) {
          node = node->prev;
        }
      }

      return node->data;
    }
  }
  void concat(List<T> &other) {
    Iterator<T> it;
    for (it = other->begin(); it != other->end(); it++) {
      this->push_back(*it);
    }
  }
  bool empty() { return !nodes; }
  int size() { return nodes; }
  void clear() {
    this->start->killSelf();
    this->start = nullptr;
    this->nodes = 0;
  }

  Iterator<T> begin() { return Iterator<T>(this->start); }
  Iterator<T> end() { return Iterator<T>(this->start->prev); }

  ~List() { this->clear(); }
};

#endif
