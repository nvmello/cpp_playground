//
// Created by parallels on 2/23/25.
//

#include "LRU_Cache.h"

void LRU_Cache::put(int key, int value)
{
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
    if (cacheMap.size() > capacity)
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
    if (cacheMap.find(key) != cacheMap.end())
    {
        // remove and re-add node to the cache
        Node* oldNode = cacheMap[key];
        removeNode(oldNode);
        addNode(oldNode);
        return oldNode->value;
    }
    else
    {
        //else return -1
        return -1;
    }
}

void LRU_Cache::addNode(Node *node)
{
    //insert the new node after head
    Node *nextNode = head->next;
    head->next = node;
    node->prev = head;
    node->next = nextNode;
    nextNode->prev = node;
}

void LRU_Cache::removeNode(Node *node)
{
    Node *prevNode = node->prev;
    Node *nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
}

