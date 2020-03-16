//
// Created by karol on 07/03/2020.
//

#define _XOPEN_SOURCE 700

#include "input.h"
#include "../Avl_Tree_lib/avl_tree.h"
#include "../Output_Processing/output.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_SIZE 10

static void clear(char *comm, char *array[], int words) {
    for (int i = 0; i < words; i++)
        free(array[i]);

    free(comm);
}


static bool inputInRange(char *str) {
    // less then 33 but not 32, 9, 11, 12, 13, 10
    for (unsigned int i = 0; i < strlen(str); i++)
        if (str[i] < 33 && str[i] != 32 && str[i] != 9 &&
            str[i] != 11 && str[i] != 12 && str[i] != 13 && str[i] != 10)
            return false;

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


static void memoryFail(char *str) {
    if (str == NULL)
        exit(1);
}


bool processLine() {

    size_t inputSize = 0;//= INPUT_SIZE;
    char *instructions = NULL;//malloc(inputSize * sizeof(char));
    //(instructions);

    ssize_t read = getline(&instructions, &inputSize, stdin);
    memoryFail(instructions);

    // na hb
//    if (read == -1 && instructions != NULL) {//&& instructions && *instructions && instructions[strlen(instructions) - 1] != '\n') {
//        fprintf(stderr, "ERROR\n");
//        free(instructions);
//        return false;
//    }
    // koniec
    // printf("ERROR:\t%s", instructions);
    if (read == -1) {
        // printf("ERROR:\t%s", instructions);
        free(instructions);
        return false;
    }

    if (instructions == NULL || instructions[0] == '#')
        return quit(instructions);

//    if (!inputInRange(instructions)) {
//        fprintf(stderr, "ERROR\n");
//        return quit(instructions);
//    }

    char *p = strtok(instructions, " \t\v\f\r\n");
    if (p == NULL)
        return quit(instructions);


    tokenize(p);

    return quit(instructions);
}