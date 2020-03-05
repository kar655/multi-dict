#include <stdio.h>
#include <stdlib.h>
#include "Avl_Tree_lib/avl_tree.h"

int main() {

    avlTree t = NULL;
    char str[100];
    while (scanf("%s", str) == 1) {
        insert(&t, &str[0]);
    }
    printAll(t);
    removeAll(t);

    return 0;
}
