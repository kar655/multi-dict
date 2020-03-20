//
// Created by karol on 05/03/2020.
//


#ifndef SMALLPROJECT_AVL_TREE_H
#define SMALLPROJECT_AVL_TREE_H

#include <stdbool.h>
#include <string.h>

struct Node;

typedef struct Node Node;

typedef Node* AvlTree;

// returns pointer to copied string
char *stringCopy(char *key);

// Add new node to tree with name = key
void insert(AvlTree *tree, char *key);

// Print all names in tree
void printAll(AvlTree tree);

// Returns dictionary connected to tree with name = key
AvlTree *getDict(AvlTree tree, char *key);

// Removes node with name = key
AvlTree deleteNode(AvlTree tree, char *key, bool dictCopied);

// Looks for specific node
// when '*' passed looks in all nodes
bool iterateOverAllNodes(AvlTree tree, char *commands[], int i, int len);

// Delete AvlTree
void removeAll(AvlTree tree);

#endif //SMALLPROJECT_AVL_TREE_H
