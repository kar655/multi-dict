//
// Created by karol on 07/03/2020.
//

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "output.h"
#include "../Avl_Tree_lib/avl_tree.h"

// Global data
AvlTree data;

// Give dict connected to data with names of subDict names[]
static AvlTree *giveDict(char *names[], int len);

// Performs add
static void add(char *commands[], int len);

// Performs del
static void del(char *commands[], int len);

// Performs print
static void print(char *commands[], int len);

// Prints YES / NO
static void checkPrinter(bool present);

// Performs check
static void check(char *commands[], int len);

//----------------------------------------------------------------------------

static AvlTree *giveDict(char *names[], int len) {

    AvlTree *output = &data;
    for (int i = 0; i < len; ++i)
        if (output == NULL)
            return NULL;
        else
            output = getDict(*output, names[i]);

    return output;
}


static void add(char *commands[], int len) {

    if (len == 0) {
        fprintf(stderr, "ERROR\n");
        return;
    }

    if (len >= 1)
        insert(&data, commands[0]);
    if (len >= 2)
        insert(getDict(data, commands[0]), commands[1]);
    if (len == 3)
        insert(getDict(*getDict(data, commands[0]),
                       commands[1]), commands[2]);

    printf("OK\n");
}


static void del(char *commands[], int len) {

    if (len == 0) {
        resetAll();
        printf("OK\n");
        return;
    }

    AvlTree *dict = giveDict(commands, len - 1);
    if (dict == NULL) {
        printf("OK\n");
        return;
    }

    *giveDict(commands, len - 1) = deleteNode(*dict, commands[len - 1], false);

    printf("OK\n");
}


static void print(char *commands[], int len) {

    if (len >= 3) {
        fprintf(stderr, "ERROR\n");
        return;
    }

    AvlTree *toPrint = giveDict(commands, len);
    if (toPrint != NULL)
        printAll(*toPrint);
}


static void checkPrinter(bool present) {
    if (present)
        printf("YES\n");
    else
        printf("NO\n");
}


static void check(char *commands[], int len) {

    // empty || last char is '*'
    if (len == 0 || strcmp(commands[len - 1], "*") == 0)
        fprintf(stderr, "ERROR\n");
    else
        checkPrinter(iterateOverAllNodes(data, commands, 0, len));
}


void resetAll() {
    removeAll(data);
    data = NULL;
}


void perform(char *operation, char *commands[], int len) {

    if (strcmp(operation, "ADD") == 0)
        add(commands, len);
    else if (strcmp(operation, "DEL") == 0)
        del(commands, len);
    else if (strcmp(operation, "PRINT") == 0)
        print(commands, len);
    else if (strcmp(operation, "CHECK") == 0)
        check(commands, len);
    else
        fprintf(stderr, "ERROR\n");
}
