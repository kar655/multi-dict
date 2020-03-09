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

// keeps logarithmic height
void balanceAfterDel(AvlTree *tree);

// returns Node with minimal key value
// of non-empty tree
AvlTree minValueNode(AvlTree tree);


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
    AvlTree tree = (AvlTree) malloc(sizeof(Node));
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

// TODO cos z balnacami zeby skrocic
void balanceAfterDel(AvlTree *tree) {
    int bFactor = balanceFactor(*tree);

    if (bFactor > 1) {
        if (balanceFactor((*tree)->left) >= 0) // left left
            rotateRight(tree);
        else { // left right
            rotateLeft(&(*tree)->left);
            rotateRight(tree);
        }
    }
    else if (bFactor < -1) {
        if (balanceFactor((*tree)->right) <= 0) // right right
            rotateLeft(tree);
        else { // right left
            rotateRight(&(*tree)->right);
            rotateLeft(tree);
        }
    }
}

AvlTree minValueNode(AvlTree tree) {
    AvlTree current = tree;

    while (current->left != NULL)
        current = current->left;

    return current;
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

AvlTree getNode(AvlTree tree, char *key) {
    if (tree == NULL)
        return NULL;

    int comparison = strcmp(tree->name, key);
    if (comparison == 0) // found
        return tree;
    else if (comparison < 0) // look right
        return getNode(tree->right, key);
    else // comparison > 0 // look left
        return getNode(tree->left, key);
}


AvlTree *getDict(AvlTree tree, char *key) {
    if (tree == NULL)
        return NULL;

    int comparison = strcmp(tree->name, key);
    if (comparison == 0) // found
        return &tree->dict;
    else if (comparison < 0) // look right
        return getDict(tree->right, key);
    else // comparison > 0 // look left
        return getDict(tree->left, key);
}


bool contains(AvlTree tree, char *key) {
//    return getDict(tree, key) != NULL;
    if (tree == NULL)
        return false;

    int comparison = strcmp(tree->name, key);
    if (comparison == 0) // found
        return true;
    else if (comparison < 0) // look right
        return contains(tree->right, key);
    else // comparison > 0 // look left
        return contains(tree->left, key);
}


AvlTree deleteNode(AvlTree tree, char *key) {
    if (tree == NULL)
        return NULL;

    int comparison = strcmp(tree->name, key);

    if (comparison < 0)
        tree->right = deleteNode(tree->right, key);
    else if (comparison > 0)
        tree->left = deleteNode(tree->left, key);
    else {
        if (tree->left == NULL || tree->right == NULL) {
            AvlTree temp = tree->left ? tree->left : tree->right;
            // No child case
            if (temp == NULL)
            {
                temp = tree;
                removeAll(tree->dict);
                free(tree->name);
                tree = NULL;
            }
            else { // One child case
                removeAll(tree->dict); // ???
                free(tree->name);
                *tree = *temp; // Copy the contents
            }
            // the non-empty child
            free(temp);
        }
        else {
            // node with two children
            AvlTree temp = minValueNode(tree->right);

            free(tree->name);
            tree->name = stringCopy(temp->name);
            removeAll(tree->dict); // ???
            tree->dict = temp->dict;

            // Delete copied
            tree->right = deleteNode(tree->right, temp->name);
        }
    }

    if (tree == NULL)
        return tree;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    correctHeight(tree);
    balanceAfterDel(&tree);

    return tree;
}

// iterates over tree
//void iterate(AvlTree tree, int depth, void (*f)()) {
//    if (tree != NULL) {
//        iterate(tree->left, depth - 1, f);
//    }
//}

bool iterateOverAllNodes(AvlTree tree, char *commands[], int i, int len) {
    if (i >= len)
        return true;
    if (tree == NULL) {
        return false;
    }

    if (strcmp(commands[i], "*") != 0) {

        AvlTree found = getNode(tree, commands[i]);
        if (found == NULL)
            return false;
        return iterateOverAllNodes(found->dict, commands, i + 1, len);
    }

    return iterateOverAllNodes(tree->dict, commands, i + 1, len) ||
        iterateOverAllNodes(tree->left, commands, i, len) ||
        iterateOverAllNodes(tree->right, commands, i, len);

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