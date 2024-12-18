#include "dsa.h"

typedef struct Treenode{
    int keys[2];
    struct Treenode* children[3];
    int keycount;
}Treenode;

Treenode createNode(int key){
    Treenode* newNode = (Treenode*)malloc(sizeof(Treenode));
    newNode->keys[0] = key;
    newNode->keycount = 1;
    for (int i = 0; i < 3; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

Treenode* insert(Treenode* root, int key){};

void insertNonFull(Treenode* node, int key){};

