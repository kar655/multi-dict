//
// Created by karol on 05/03/2020.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "avl_tree.h"

#define INPUT_LENGTH 100

Node {
    // number of bottom-avl-trees
    // int degree;
    char *name;
    avlTree value;
    int height;
    avlTree left, right;
};


// Helpers
// ----------------------------------------------------------------------------

// returns bigger int
int max(int a, int b);

// returns pointer to copied string
char *stringCopy(char *key);

// returns tree's height
int getHeight(avlTree tree);

// updates height
void correctHeight(avlTree tree);

// rotates left
void rotateLeft(avlTree *tree);

// rotates right
void rotateRight(avlTree *tree);

// keeps logarithmic height
void balance(avlTree *tree);


// Implementation
// ----------------------------------------------------------------------------

int max(int a, int b) {
    if (a >= b)
        return a;
    else
        return b;
}


char *stringCopy(char *key) {
    char *copied = malloc(strlen(key) + 1);
    strcpy(copied, key);
    return copied;
}


int getHeight(avlTree tree) {
    if (tree == NULL)
        return 0;
    else
        return tree->height;
}


void correctHeight(avlTree tree) {
    // tree->left->height = max(getHeight(tree->left->left), getHeight(tree->left->right)) + 1;
    // tree->right->height = max(getHeight(tree->right->left), getHeight(tree->right->right)) + 1;
    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
}


void rotateLeft(avlTree *tree) {
    avlTree rightTree = (*tree)->right;
    (*tree)->right = rightTree->left;
    rightTree->left = *tree;
    correctHeight(*tree);
    correctHeight(rightTree);
    *tree = rightTree;
}


void rotateRight(avlTree *tree) {
    avlTree leftTree = (*tree)->left;
    (*tree)->left = leftTree->right;
    leftTree->right = *tree;
    correctHeight(*tree);
    correctHeight(leftTree);
    *tree = leftTree;
}


void balance(avlTree *tree) {
    if (getHeight(*tree) <= 2 || abs(getHeight((*tree)->left) - getHeight((*tree)->right)) <= 1)
        return;
    else if (getHeight((*tree)->left) > getHeight((*tree)->right)) {
        rotateRight(tree);
    }
    else { // getHeight(tree->left) < getHeight(tree->right)
        rotateLeft(tree);
    }
    // TODO Correct ballancing
}


void insert(avlTree *tree, char *key) {
    if ((*tree) == NULL) {
        *tree = malloc(sizeof(Node) + strlen(key));
        **tree = (Node) {stringCopy(key), NULL, 1, NULL, NULL};
        return;
    }
    int comparison = strcmp((*tree)->name, key);
    if (comparison == 0)
        return;

    (*tree)->height++;
    if (comparison < 0) {
        insert(&((*tree)->right), key);
    }
    else if (comparison > 0) {
        insert(&((*tree)->left), key);
    }

    balance(tree);
}


void printAll(avlTree tree) {
    if (tree != NULL) {
        printAll(tree->left);
        printf("%s\n", tree->name);
        printAll(tree->right);
    }
}


bool contains(avlTree tree, char *key) {
    if (tree == NULL)
        return false;

    int comparison = strcmp(tree->name, key);
    if (comparison == 0)
        return true;
    else if (comparison < 0)
        return contains(tree->right, key);
    else // comparison > 0
        return contains(tree->left, key);
}


void removeAll(avlTree tree) {
    if (tree != NULL) {
        removeAll(tree->left);
        removeAll(tree->right);
        removeAll(tree->value);
        free(tree->name);
        free(tree);
    }
}