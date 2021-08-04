#include "Definitions.h"

Node *newNode(Data d){
    Node *newNode = new Node;
    newNode->data = d;
    newNode->endWord = false;
    newNode->prefix = "";
    newNode->parent = nullptr;
    for(int i =0; i<alphabet_size; i++){
        newNode->children[i] = nullptr;
    }
    return newNode;
}

void deallocateNode(Node* node){
    for(int i = 0; i<alphabet_size; i++){
        if(node->children[i] != nullptr){
            deallocateNode(node->children[i]);
        }else{
            continue;
        }
    }
    node = NULL;
    delete node;
}

