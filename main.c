#include <stdio.h>
#include "Avl_Tree_lib/avl_tree.h"
#include "Output_Processing/output.h"
#include "Input_Processing/input.h"

int main() {

    resetAll();
    while (processLine())
        fflush(stdout);
    resetAll();

    return 0;
}
