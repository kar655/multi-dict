#include <stdio.h>
#include <stdlib.h>
#include "Avl_Tree_lib/avl_tree.h"

void testGG() {
    AvlTree root = NULL;

    /* Constructing tree given in the above figure */
    insert(&root, "9");
    insert(&root, "5");
    insert(&root, "10");
    insert(&root, "0");
    insert(&root, "6");
    insert(&root, "11");
    insert(&root, "-1");
    insert(&root, "1");
    insert(&root, "2");

    /* The constructed AVL Tree would be
            9
           /  \
          1    10
        /  \     \
       0    5     11
      /    /  \
     -1   2    6
    */

    printAll(root);

    // cos tu nie pyka
    root = deleteNode(root, "10");

    /* The AVL Tree after deletion of 10
            1
           /  \
          0    9
        /     /  \
       -1    5     11
           /  \
          2    6
    */

    printf("\n\n\n");
    printAll(root);

    removeAll(root);
}

void simpleDelTest() {
    AvlTree tree = NULL;
    insert(&tree, "a");
    insert(&tree, "aa");
    insert(&tree, "aaa");
    printAll(tree);
    printf("\n\n");

    tree = deleteNode(tree, "aa");
    printAll(tree);
    printf("\n\n");

    insert(&tree, "aa");
    tree = deleteNode(tree, "a");
    printAll(tree);
    printf("\n\n");

    insert(&tree, "a");
    tree = deleteNode(tree, "aaa");
    printAll(tree);
    printf("\n\n");

    insert(&tree, "aaa");
    printAll(tree);
    printf("\n\n");

    tree = deleteNode(tree, "a");
    tree = deleteNode(tree, "aa");
    tree = deleteNode(tree, "aaa");
    printf("Empty: ");
    printAll(tree);

    //removeAll(tree);
}

void dictDelTest(char str[]) {
    AvlTree tree = NULL;
    insert(&tree, "a");
    insert(&tree, "aa");
    insert(&tree, "aaa");
    printf("contains t/a: %d\n", contains(tree, "a"));
    printf("contains t/aaa: %d\n", contains(tree, "aaa"));

    insert(getDict(tree, "a"), "bbb");
    insert(getDict(tree, "a"), "bb");
    insert(getDict(tree, "a"), "b");
    printAll(*getDict(tree, "a"));

    printf("contains t/a/%s: %d\n", str, contains(*getDict(tree, "a"), str));

    deleteNode(*getDict(tree, "a"), str);

    printf("contains t/a/%s: %d\n", str, contains(*getDict(tree, "a"), str));
    printf("contains t/b: %d\n", contains(tree, "b"));

    removeAll(tree);
}

int main() {

//    AvlTree LASY = NULL;
//    char str[100];
//    while (scanf("%s", str) == 1) {
//        insert(&LASY, &str[0]);
//    }
//    printAll(LASY);


    // ------------------------------------------------------------------------
//    testGG();
//    simpleDelTest();
//    dictDelTest("b");
//    printf("\n\n");
//    dictDelTest("bb");
//    printf("\n\n");
//    dictDelTest("bbb");
//    printf("\n\n");
//    dictDelTest("c");
//    printf("\n\n");
    // ------------------------------------------------------------------------

    return 0;
}
