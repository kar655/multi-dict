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

void copySingleNode(AvlTree copyTo, AvlTree copyFrom) {
    // strcpy?
    copyTo->dict = copyFrom->dict;
    strcpy(copyTo->name, copyFrom->name);
    free(copyFrom->name);
    free(copyFrom);
    // left and right must be null bcs it has to be balanced

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
            else {// One child case
                //copySingleNode(tree, temp);
                free(tree->name);
                *tree = *temp; // Copy the contents of
            }

            // the non-empty child
            // TODO a nie powinno byc removeAll? chyba tak bo moze laczyc inne subDicts
            // temp->left = temp->right = NULL;
//            free(temp->name);
//            free(temp->dict);
            ///
            free(temp);
            // removeAll(temp);
        }
        else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            AvlTree temp = minValueNode(tree->right);

            // Copy the inorder successor's
            // data to this node
            // ------------
            free(tree->name);
            tree->name = stringCopy(temp->name);
            // ------------

            tree->dict = temp->dict;

            // Delete the inorder successor
            tree->right = deleteNode(tree->right, temp->name);
        }
    }

    // If the tree had only one node
    // then return
    if (tree == NULL)
        return tree;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    correctHeight(tree);
    // tree->height = 1 + max(height(root->left), height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = balanceFactor(tree);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 && balanceFactor(tree->left) >= 0) {
        rotateRight(&tree);
        return tree;
    }

    // Left Right Case
    if (balance > 1 && balanceFactor(tree->left) < 0)
    {
        rotateLeft(&tree->left);
        rotateRight(&tree);
        return tree;
    }

    // Right Right Case
    if (balance < -1 && balanceFactor(tree->right) <= 0) {
        rotateLeft(&tree);
        return tree;
    }
    // Right Left Case
    if (balance < -1 && balanceFactor(tree->right) > 0)
    {
        rotateRight(&tree->right);
        rotateLeft(&tree);
        return tree;
    }

    return tree;
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