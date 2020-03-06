//
// Created by karol on 05/03/2020.
//

#include <stdbool.h>
#include <string.h>
#ifndef SMALLPROJECT_AVL_TREE_H
#define SMALLPROJECT_AVL_TREE_H

struct Node;

typedef struct Node* avlTree;
#define Node struct Node

// Add new node to tree with value = key
void insert(avlTree *tree, char *key);

// Print all values in tree
void printAll(avlTree tree);

// Checks if tree contains node with value = key
bool contains(avlTree tree, char *key);

// Removes node with name = key
// void remove(avlTree tree, char *key);

// Delete avlTree
void removeAll(avlTree tree);

#endif //SMALLPROJECT_AVL_TREE_H
