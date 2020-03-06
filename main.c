#include <stdio.h>
#include <stdlib.h>
#include "Avl_Tree_lib/avl_tree.h"

int main() {

    AvlTree LASY = NULL;
//    char str[100];
//    while (scanf("%s", str) == 1) {
//        insert(&LASY, &str[0]);
//    }
//    printAll(LASY);

    insert(&LASY, "b");
    insert(&LASY, "puszcza");
    insert(&LASY, "qn");
    AvlTree *las = getDict(LASY, "puszcza");
    insert(las, "brzoza");
    insert(las, "zorza");
    insert(las, "koza");

    insert(&LASY, "kon");
    removeAll(LASY);
    return 0;
}
