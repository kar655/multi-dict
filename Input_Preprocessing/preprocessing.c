//
// Created by karol on 07/03/2020.
//

#include "preprocessing.h"
#include "../Avl_Tree_lib/avl_tree.h"
#include "../Input_Processing/processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRST_SIZE 10

//size_t inputSize;
//char *instructions;
//char *array[4];


//void init() {
//    inputSize = FIRST_SIZE;
//    instructions = malloc(inputSize * sizeof(char));
//}
//
//void doubleMem() {
//    inputSize *= 2;
//    instructions = realloc(instructions, inputSize * sizeof(char));
//}
//
//void clear(int i) {
//
//    inputSize = FIRST_SIZE;
//    free(instructions);
//    for (int j = 0; j < i - 1; j++)
//        free(array[j]);
//}


bool processLine() {
    // ------------------------------------------------------------------------------------------------------------------
//    init();

    size_t inputSize = 10;
    char *instructions = malloc(inputSize * sizeof(char));
    char *array[4];

    //jaki ssssize xd?
    size_t read = getline(&instructions, &inputSize, stdin);
    if (read == -1) {
        free(instructions);
        return false;
    }

    char *p = strtok(instructions, " \t\v\f\r\n");
    if (strcmp(p, "#") == 0) {
        // free(instructions);
        free(p);
        return read != -1;
    }

    int i = 0;
    while (p != NULL) {
        if (i >= 4) {
            printf("ERROR\n");
            free(instructions);
            free(p);
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

    // ------------------------------------------------------------------------------------------------------------------
//
//    char *comm[3] = {"a", "b", "c"};
//    perform("ADD", comm, 3);
//
//    comm[1] = "d";
//    comm[2] = "e";
//    perform("ADD", comm, 3);
//
//    perform("PRINT", NULL, 0);
//    return false;
}