//
// Created by karol on 05/03/2020.
//

#include <stdbool.h>
#include <string.h>
#ifndef SMALLPROJECT_AVL_TREE_H
#define SMALLPROJECT_AVL_TREE_H

struct Node;

typedef struct Node* AvlTree;
#define Node struct Node

// Add new node to tree with name = key
void insert(AvlTree *tree, char *key);

// Print all names in tree
void printAll(AvlTree tree);

// Returns dictionary connected to tree with name = key
AvlTree *getDict(AvlTree tree, char *key);

// Checks if tree contains node with name = key
bool contains(AvlTree tree, char *key);

// Removes node with name = key
AvlTree deleteNode(AvlTree tree, char *key);

// Delete AvlTree
void removeAll(AvlTree tree);

#endif //SMALLPROJECT_AVL_TREE_H
