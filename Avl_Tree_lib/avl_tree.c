//
// Created by karol on 05/03/2020.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "avl_tree.h"


Node {
    char *name;
    AvlTree dict;
    int height;
    AvlTree left, right;
};


// Helpers
// ----------------------------------------------------------------------------

// returns bigger int
int max(int a, int b);

// returns pointer to copied string
char *stringCopy(char *key);

// creates new node
AvlTree newNode(char *key);

// returns tree's height
int getHeight(AvlTree tree);

// updates height
void correctHeight(AvlTree tree);

// returns balance factor of node *tree
int balanceFactor(AvlTree tree);

// rotates left
void rotateLeft(AvlTree *tree);

// rotates right
void rotateRight(AvlTree *tree);

// keeps logarithmic height
void balance(AvlTree *tree, char *key);


// Implementation
// ----------------------------------------------------------------------------

int max(int a, int b) {
    return (a >= b) ? a : b;
}


char *stringCopy(char *key) {
    char *copied = malloc(strlen(key) + 1);
    strcpy(copied, key);
    return copied;
}

AvlTree newNode(char *key) {
    AvlTree tree = malloc(sizeof(Node));
    *tree = (Node) {stringCopy(key), NULL, 1, NULL, NULL};
    return tree;
}


int getHeight(AvlTree tree) {
    return (tree == NULL) ? 0 : tree->height;
}


void correctHeight(AvlTree tree) {
    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
}


int balanceFactor(AvlTree tree) {
    if (tree == NULL)
        return 0;
    else
        return getHeight(tree->left) - getHeight(tree->right);
}


void rotateLeft(AvlTree *tree) {
    AvlTree rightTree = (*tree)->right;
    (*tree)->right = rightTree->left;
    rightTree->left = *tree;
    correctHeight(*tree);
    correctHeight(rightTree);
    *tree = rightTree;
}


void rotateRight(AvlTree *tree) {
    AvlTree leftTree = (*tree)->left;
    (*tree)->left = leftTree->right;
    leftTree->right = *tree;
    correctHeight(*tree);
    correctHeight(leftTree);
    *tree = leftTree;
}


void balance(AvlTree *tree, char *key) {
    int comparison;
    int bFactor = balanceFactor(*tree);

    if (bFactor > 1) {
        comparison = strcmp((*tree)->left->name, key);
        if (comparison > 0) // left left
            rotateRight(tree);
        else { // left right
            rotateLeft(&(*tree)->left);
            rotateRight(tree);
        }
    }
    else if (bFactor < -1) {
        comparison = strcmp((*tree)->right->name, key);
        if (comparison > 0) { // right left
            rotateRight(&(*tree)->right);
            rotateLeft(tree);
        }
        else // right right
            rotateLeft(tree);
    }
}


void insert(AvlTree *tree, char *key) {
    if ((*tree) == NULL) {
        *tree = newNode(key);
        return;
    }
    int comparison = strcmp((*tree)->name, key);
    if (comparison == 0)
        return;

    if (comparison < 0) {
        insert(&((*tree)->right), key);
    }
    else if (comparison > 0) {
        insert(&((*tree)->left), key);
    }

    correctHeight(*tree);
    balance(tree, key);
}


void printAll(AvlTree tree) {
    if (tree != NULL) {
        printAll(tree->left);
        printf("%s\n", tree->name);
        printAll(tree->right);
    }
}

AvlTree *getDict(AvlTree tree, char *key) {
    if (tree == NULL)
        return NULL;

    int comparison = strcmp(tree->name, key);
    if (comparison == 0)
        // wydaje mi sie ze powinien bys wskaznik do tego jeszcze
        return &tree->dict;
    else if (comparison < 0)
        return getDict(tree->right, key);
    else // comparison > 0
        return getDict(tree->left, key);
}


bool contains(AvlTree tree, char *key) {
    return getDict(tree, key) != NULL;
}


void removeAll(AvlTree tree) {
    if (tree != NULL) {
        removeAll(tree->left);
        removeAll(tree->right);
        removeAll(tree->dict);
        free(tree->name);
        free(tree);
    }
}