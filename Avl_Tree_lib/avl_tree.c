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


void balance(avlTree tree);

char *stringCopy(char *key) {
    char *cptr = malloc(INPUT_LENGTH);
    strcpy(cptr, key);
    return cptr;
}

// Add new node to tree with value = key
void insert(avlTree *tree, char *key) {
    if ((*tree) == NULL) {
        *tree = malloc(sizeof(Node));
        **tree = (Node) {stringCopy(key), NULL, 1, NULL, NULL};
        return;
    }
    int comparison = strcmp((*tree)->name, key);
    if (comparison == 0)
        return;

    (*tree)->height++;
    if (comparison < 0) {
        // w prawo
        insert(&((*tree)->right), key);
    }
    else if (comparison > 0) {
        // w lewo
        insert(&((*tree)->left), key);
    }

    // TU MOZE BYC PRZYPS
    // balance(*tree);
}

// Print all values in tree
void printAll(avlTree tree) {
    if (tree != NULL) {
        printAll(tree->left);
        printf("%s\n", tree->name);
        printAll(tree->right);
    }
}

// Checks if tree contains node with value = key
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

// Delete avlTree
void removeAll(avlTree tree) {
    if (tree != NULL) {
        removeAll(tree->left);
        removeAll(tree->right);
        free(tree->name);
        free(tree);
    }
}

int getHeight(avlTree tree) {
    if (tree == NULL)
        return 0;
    else
        return tree->height;
}

//void rotateLeft(avlTree tree) {
//    return;
//}
//
//void rotateRight(avlTree tree) {
//    return;
//}

void balance(avlTree tree) {
    if (getHeight(tree) < 1)
        return;
    else if (abs(getHeight(tree->left) - getHeight(tree->right)) <= 1)
        return;
//    else if (getHeight(tree->left) > getHeight(tree->right))
//        rotateRight(tree);
//    else // getHeight(tree->left) < getHeight(tree->right)
//        rotateLeft(tree);
}

// strcmp() -- porownuje stringi