//
// Created by karol on 07/03/2020.
//

#include "preprocessing.h"
#include <stdio.h>
#include <stdlib.h>

size_t inputSize = 10;
char *instructions;


void init() {
    instructions = malloc(inputSize * sizeof(char));
}

void doubleMem() {
    inputSize *= 2;
    instructions = realloc(instructions, inputSize * sizeof(char));
}

bool processLine() {

    init();

    char *array[4];
    ssize_t read = 0;
    size_t n = 0;

    int i = 0;

    while (getline(&instructions, &inputSize, stdin) != -1) {
        ++n;
        if (n >= inputSize)
            doubleMem();
        char *p = strtok(instructions, " \n");

        i = 0;
        while (p != NULL) {
            if (i >= 4) {
                printf("BAD INPUT\n");
                i = 0;
                break;
            }
            array[i++] = stringCopy(p);
            // printf("Added to array: %s\n", p);
            p = strtok(NULL, " \n");
        }

//            printf("Array data: \n");
//            for (int j = 0; j < i; j++) {
//                printf("%s\n", array[j]);
//            }
//            printf("end of data\n");

        char *ope = array[0];
        // = {array[1], array[2], array[3]}
        char *comm[3];
        for (int j = 0; j < i - 1; ++j) {
            comm[j] = array[j + 1];
        }

        perform(ope, comm, i - 1);

        fflush(stdout);

    }

    free(instructions);

    for (int j = 0; j < i; j++)
        free(array[j]);
}