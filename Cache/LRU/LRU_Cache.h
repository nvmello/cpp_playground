//
// Created by parallels on 2/23/25.
//

#ifndef LRU_CACHE_H
#define LRU_CACHE_H
#include <bits/stdc++.h>
using namespace std;

struct Node{
  size_t tag;
  Node* next;
  Node* prev;
  Node(size_t t)
  {
    tag = t;
    next = nullptr;
    prev = nullptr;
  }
  };

class LRU_Cache {

  private:
    size_t cache_size; //size of cache
    unordered_map<size_t, Node *> cacheMap;
    Node* head;
    Node* tail;

    //add a node to most recent spot
    void addNode(Node *node);

    //remove a node from the list
    void removeNode(Node *node);

  public:
    //constructor
    explicit LRU_Cache(size_t capacity = 2)
    {
      this->cache_size = capacity;
      head = new Node(-1);
      tail = new Node(-1);
      head->next = tail;
      tail->prev = head;
    }


    //function to put tag-value pair size_to the cache
    void put(size_t tag);

    //function to get the value of a pair
    bool get(size_t tag);

};
#endif //LRU_CACHE_H
