//
// Created by karol on 07/03/2020.
//

#define _XOPEN_SOURCE 700
#include "preprocessing.h"
#include "../Avl_Tree_lib/avl_tree.h"
#include "../Input_Processing/processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 10


bool processLine() {

    size_t inputSize = INPUT_SIZE;
    char *instructions = malloc(inputSize * sizeof(char));
    char *array[4];

    //jaki ssssize xd?
    ssize_t read = getline(&instructions, &inputSize, stdin);
    if (read == -1) {
        free(instructions);
        return false;
    }

    if (instructions == NULL || instructions[0] == '#') {
        free(instructions);
        // free(p);
        return read != -1;
    }
    char *p = strtok(instructions, " \t\v\f\r\n");
    if (p == NULL) {
        free(instructions);
        return read != -1;
    }

    int i = 0;
    while (p != NULL) {
        if (i >= 4) {
            fprintf(stderr, "ERROR\n");
            free(instructions);
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
//            clear(3);
            return true;
        }
        array[i++] = stringCopy(p);

        p = strtok(NULL, " \t\v\f\r\n");
    }

    char *comm[3];
    for (int j = 0; j < i - 1; ++j)
        comm[j] = array[j + 1];


    perform(array[0], comm, i - 1);


//    for (int j = 0; j < 3; j++) {
//        free(comm[j]);
//    }

// MUSI byc
    for (int j = 0; j < i; j++) {
        free(array[j]);
    }
    free(instructions);
    free(p);

//    for (int j = 0; j < i - 1; ++j)
//        free(comm[j]);


//    clear(i);
    return true;
}