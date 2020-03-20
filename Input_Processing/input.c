//
// Created by karol on 07/03/2020.
//

#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "input.h"
#include "../Avl_Tree_lib/avl_tree.h"
#include "../Output_Processing/output.h"


// clear memory
static void clear(char *comm, char *array[], int words) {
    for (int i = 0; i < words; i++)
        free(array[i]);

    free(comm);
}


// checks if chars are >= 33
static bool inputInRange(char *str, ssize_t len) {
    for (int i = 0; i < len; i++) {
        unsigned int c = (unsigned int) str[i];

        if (c < 33 && isspace(c) == 0) {
            return false;
        }
    }

    return true;
}


// tokenize input and call actions
static void tokenize(char *p) {

    char *array[3];
    int words = 0;
    char *comm = stringCopy(p);
    p = strtok(NULL, " \t\v\f\r\n");

    while (p != NULL) {
        if (words >= 3) {
            fprintf(stderr, "ERROR\n");
            clear(comm, array, words);
            return;
        }
        else
            array[words++] = stringCopy(p);

        p = strtok(NULL, " \t\v\f\r\n");
    }

    perform(comm, array, words);
    clear(comm, array, words);
    free(p);
}


// free str
static bool quit(char *str) {
    free(str);
    return true;
}


// not enough memory
static void memoryFail(char *str) {
    if (str == NULL)
        exit(1);
}


bool processLine() {

    size_t inputSize = 0;
    char *instructions = NULL;

    ssize_t read = getline(&instructions, &inputSize, stdin);
    memoryFail(instructions);

    if (read == -1) {
        free(instructions);
        return false;
    }

    if (!inputInRange(instructions, read)) {
        fprintf(stderr, "ERROR\n");
        return quit(instructions);
    }

    if (instructions == NULL || instructions[0] == '#') {
        return quit(instructions);
    }

    char *p = strtok(instructions, " \t\v\f\r\n");
    if (p == NULL)
        return quit(instructions);


    tokenize(p);

    return quit(instructions);
}
