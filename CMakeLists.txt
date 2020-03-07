cmake_minimum_required(VERSION 3.15)
project(smallProject C)

set(CMAKE_C_STANDARD 99)

add_executable(smallProject main.c Avl_Tree_lib/avl_tree.c Avl_Tree_lib/avl_tree.h Input_Processing/processing.c Input_Processing/processing.h Input_Preprocessing/preprocessing.c Input_Preprocessing/preprocessing.h)