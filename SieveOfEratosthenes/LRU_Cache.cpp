//
// Created by parallels on 2/23/25.
//

#include "LRU_Cache.h"

void LRU_Cache::put(int key, int value)
{
    //if key is not present and if cache is not full
    //put key value after head

    //if key is already in cache
    if (cacheMap.find(key) != cacheMap.end())
    {
        Node* oldNode = cacheMap[key]; //grab a copy of it
        removeNode(oldNode); //remove it from cache
        delete oldNode; //delete it from memory
    }

    //then add the new node to the cache regardless
    Node* newNode = new Node(key, value);
    cacheMap[key] = newNode; //log it in the cachemap
    addNode(newNode);

    //if key is not present and cache is full, LRU to remove least recently used and
    //put key value after head
    if (cacheMap.size() >= capacity)
    {
        Node *delNode = tail->prev;
        //remove lowest priority node from cache
        removeNode(delNode);

        //remove lowest priority node from cachemap
        cacheMap.erase(delNode->key);

        //delete node
        delete delNode;

    }

}

int LRU_Cache::get(int key)
{
    //if key is present,
    // return value and update to highest priority
    //else return -1
    return 0;
}

void LRU_Cache::addNode(Node *node)
{

    head->next = node;

}

void LRU_Cache::removeNode(Node *node)
{
    Node *prevNode = node->prev;
    Node *nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
}

