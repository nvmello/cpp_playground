//
// Created by parallels on 2/23/25.
//

#ifndef LRU_CACHE_H
#define LRU_CACHE_H
#include <bits/stdc++.h>
using namespace std;

struct Node{
  int key;
  int value;
  Node* next;
  Node* prev;
  Node(int k, int v)
  {
    key = k;
    value = v;
    next = nullptr;
    prev = nullptr;
  }
  };

class LRU_Cache {

  private:
    int capacity; //size of cache
    unordered_map<int, Node *> cacheMap;
    Node* head;
    Node* tail;

    //add a node to most recent spot
    void addNode(Node *node);

    //remove a node from the list
    void removeNode(Node *node);

  public:
    //constructor
    explicit LRU_Cache(int capacity = 2)
    {
      this->capacity = capacity;
      head = new Node(-1,-1);
      tail = new Node(-1,-1);
      head->next = tail;
      tail->prev = head;
    }


    //function to put key-value pair into the cache
    void put(int key, int value);

    //function to get the value of a pair
    int get(int key);





};



#endif //LRU_CACHE_H
