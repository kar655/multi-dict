#include <stdio.h>
#include <stdlib.h>
#include "Avl_Tree_lib/avl_tree.h"
#include "Input_Processing/processing.h"
#include "Input_Preprocessing/preprocessing.h"

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

void dictDelTest(char str1[], char str2[]) {
    AvlTree tree = NULL;
    insert(&tree, "a");
    insert(&tree, "aa");
    insert(&tree, "aaa");
//    printf("contains t/a: %d\n", contains(tree, "a"));
//    printf("contains t/aaa: %d\n", contains(tree, "aaa"));

    insert(getDict(tree, str1), "bbb");
    insert(getDict(tree, str1), "bb");
    insert(getDict(tree, str1), "b");
    printAll(*getDict(tree, str1));

    printf("contains tree/%s/%s: %d\n", str1, str2, contains(*getDict(tree, str1), str2));

    deleteNode(*getDict(tree, str1), str2);

    printf("contains tree/%s/%s: %d\n", str1, str2, contains(*getDict(tree, str1), str2));
    printf("contains tree/b: %d\n", contains(tree, "b"));

    removeAll(tree);
}

void multiTest() {
    testGG();

    simpleDelTest();

    dictDelTest("a", "b");
    printf("\n\n");
    dictDelTest("a", "bb");
    printf("\n\n");
    dictDelTest("a", "bbb");
    printf("\n\n");

    dictDelTest("a", "c");
    printf("\n\n");

    dictDelTest("aa", "b");
    printf("\n\n");
    dictDelTest("aa", "bb");
    printf("\n\n");
    dictDelTest("aa", "bbb");
    printf("\n\n");

    dictDelTest("aaa", "b");
    printf("\n\n");
    dictDelTest("aaa", "bb");
    printf("\n\n");
    dictDelTest("aaa", "bbb");
    printf("\n\n");
}

void jakiesZczytywanie() {
    size_t words, n, inputSize = 10;
    char *instructions = malloc(inputSize * sizeof(char));
    char *ptr;

    words = n = 0;
    // fgets(instructions, inputSize, stdin) != NULL
    // scanf("%s", instructions) == 1
    while (fgets(instructions, inputSize, stdin) != NULL) {
        // allocates new memory ---------------------------------------------------
        ++n;
        if (n >= inputSize) {
            inputSize *= 2;
            instructions = realloc(instructions, inputSize * sizeof(char));
        }
        // ------------------------------------------------------------------------

        ptr = strtok(instructions, " ");
        while (ptr) {
            words++;
            // puts(ptr);
            ptr = strtok(NULL, " ");
        }
        printf("%zu\n", words);
    }

    free(instructions);
}

void nibyDzialaAleNieWypisujeOdRazu() {

}

int main() {


    // ------------------------------------------------------------------------
    //multiTest();
    // ------------------------------------------------------------------------

//    char *line = NULL;
//    size_t len = 0;
//    ssize_t read = 0;
//    while (read != -1) {
//        puts("enter a line");
//        read = getline(&line, &len, stdin);
//        printf("line = %s", line);
//        printf("line length = %zu\n", read);
//        fflush(stdout);
//    }
//    free(line);

    resetAll();
    while (processLine());


    // nibyDzialaAleNieWypisujeOdRazu();


    // resetAll();
    // perform(array);

    return 0;
}
