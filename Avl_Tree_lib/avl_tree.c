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


// returns bigger int
static int max(int a, int b);

// returns pointer to copied string
char *stringCopy(char *key);

// creates new node
static AvlTree newNode(char *key);

// returns tree's height
static int getHeight(AvlTree tree);

// updates height
static void correctHeight(AvlTree tree);

// returns balance factor of node *tree
static int balanceFactor(AvlTree tree);

// rotates left
static void rotateLeft(AvlTree *tree);

// rotates right
static void rotateRight(AvlTree *tree);

// keeps logarithmic height
static void balance(AvlTree *tree, char *key);

// keeps logarithmic height
static void balanceAfterDel(AvlTree *tree);

// returns Node with minimal key value
// of non-empty tree
static AvlTree minValueNode(AvlTree tree);

static void delNodeHelper(AvlTree *tree, bool dictCopied);


// Implementation
// ----------------------------------------------------------------------------

static int max(int a, int b) {
    return (a >= b) ? a : b;
}


char *stringCopy(char *key) {
    char *copied = (char *) malloc((strlen(key) + 1) * sizeof(char));
    if (copied == NULL)
        exit(1);
    strcpy(copied, key);
    return copied;
}


static AvlTree newNode(char *key) {
    AvlTree tree = (AvlTree) malloc(sizeof(Node));
    if (tree == NULL)
        exit(1);
    *tree = (Node) {stringCopy(key), NULL, 1, NULL, NULL};
    return tree;
}


static int getHeight(AvlTree tree) {
    return (tree == NULL) ? 0 : tree->height;
}


static void correctHeight(AvlTree tree) {
    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
}


static int balanceFactor(AvlTree tree) {
    if (tree == NULL)
        return 0;
    else
        return getHeight(tree->left) - getHeight(tree->right);
}


static void rotateLeft(AvlTree *tree) {
    AvlTree rightTree = (*tree)->right;
    (*tree)->right = rightTree->left;
    rightTree->left = *tree;
    correctHeight(*tree);
    correctHeight(rightTree);
    *tree = rightTree;
}


static void rotateRight(AvlTree *tree) {
    AvlTree leftTree = (*tree)->left;
    (*tree)->left = leftTree->right;
    leftTree->right = *tree;
    correctHeight(*tree);
    correctHeight(leftTree);
    *tree = leftTree;
}


static void balance(AvlTree *tree, char *key) {
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


static void balanceAfterDel(AvlTree *tree) {
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


static AvlTree minValueNode(AvlTree tree) {
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

    if (comparison < 0)
        insert(&((*tree)->right), key);
    else if (comparison > 0)
        insert(&((*tree)->left), key);

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

    AvlTree output = getNode(tree, key);
    if (output == NULL)
        return NULL;
    else
        return &output->dict;
}


bool contains(AvlTree tree, char *key) {
    return getNode(tree, key) != NULL;
}

static void delNodeHelper(AvlTree *tree, bool dictCopied) {
    if ((*tree)->left == NULL || (*tree)->right == NULL) {
        // not Null child
        AvlTree temp = (*tree)->left ? (*tree)->left : (*tree)->right;

        if (temp == NULL) { // No child case
            if (!dictCopied) {
                removeAll((*tree)->dict);
            }
            free((*tree)->name);
            free(*tree);
            *tree = NULL;
        }
        else { // One child case
            if (!dictCopied) {
                removeAll((*tree)->dict); // TODO chyba nie potrzebne
            }
            free((*tree)->name);
            **tree = *temp;
        }
        // the non-empty child
        free(temp);
    }
    else {
        // node with two children
        AvlTree temp = minValueNode((*tree)->right);

        free((*tree)->name);
        (*tree)->name = NULL;
        (*tree)->name = stringCopy(temp->name);

        removeAll((*tree)->dict);
        (*tree)->dict = NULL;
        (*tree)->dict = temp->dict;

        // Delete copied
        /// usunac ale nie usuwac dict bo skopiowalem
        (*tree)->right = deleteNode((*tree)->right, temp->name, true);
    }
}


AvlTree deleteNode(AvlTree tree, char *key, bool dictCopied) {
    if (tree == NULL)
        return NULL;

    int comparison = strcmp(tree->name, key);

    if (comparison < 0)
        tree->right = deleteNode(tree->right, key, dictCopied);
    else if (comparison > 0)
        tree->left = deleteNode(tree->left, key, dictCopied);
    else { // comparison == 0
        delNodeHelper(&tree, dictCopied);
    }

    if (tree == NULL)
        return tree;

    // update height
    correctHeight(tree);
    balanceAfterDel(&tree);

    return tree;
}


bool iterateOverAllNodes(AvlTree tree, char *commands[], int i, int len) {
    if (i >= len)   // mozna usunac?
        return true;
    if (tree == NULL)
        return false;

    if (strcmp(commands[i], "*") != 0) {
        AvlTree found = getNode(tree, commands[i]);

        if (found == NULL)
            return false;
        else if (i + 1 >= len)
            return true;
        else if (found->dict == NULL)
            return false;
        else
            return iterateOverAllNodes(found->dict, commands, i + 1, len);
    }
    // '*'
    return iterateOverAllNodes(tree->dict, commands, i + 1, len) ||
           iterateOverAllNodes(tree->left, commands, i, len) ||
           iterateOverAllNodes(tree->right, commands, i, len);

}


void removeAll(AvlTree tree) {
    if (tree != NULL) {
        removeAll(tree->left);
        tree->left = NULL;
        removeAll(tree->right);
        tree->right = NULL;
        removeAll(tree->dict);
        tree->dict = NULL;
        free(tree->name);
        tree->name = NULL;
        free(tree);
        tree = NULL;
    }
}
