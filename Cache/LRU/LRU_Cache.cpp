//
// Created by parallels on 2/23/25.
//

#include "LRU_Cache.h"

void LRU_Cache::put(size_t tag)
{
    //if tag is already in cache
    if (cacheMap.find(tag) != cacheMap.end())
    {
        Node* oldNode = cacheMap[tag]; //grab a copy of it
        removeNode(oldNode); //remove it from cache
        delete oldNode; //delete it from memor
    }

    //then add the new node to the cache regardless
    Node* newNode = new Node(tag);
    cacheMap[tag] = newNode; //log it in the cachemap
    addNode(newNode);

    //if tag is not present and cache is full, LRU to remove least recently used and
    //put tag value after head
    if (cacheMap.size() > cache_size)
    {
        Node *delNode = tail->prev;
        //remove lowest priority node from cache
        removeNode(delNode);

        //remove lowest priority node from cachemap
        cacheMap.erase(delNode->tag);

        //delete node
        delete delNode;
    }
}

bool LRU_Cache::get(size_t tag)
{
    //if tag is present,
    if (cacheMap.find(tag) != cacheMap.end())
    {
        // remove and re-add node to the cache
        Node* oldNode = cacheMap[tag];
        removeNode(oldNode);
        addNode(oldNode);
        return true;
    }
    else
    {
        //else return false
        return false;
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

