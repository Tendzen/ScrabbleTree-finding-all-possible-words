#pragma once
#ifndef ScrabbleTree_h
#define ScrabbleTree_h

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <stack>
#include <map>
#include <queue>
#include <unordered_map>
using namespace std;


typedef char Data;
typedef struct Node* pNode;
const int alphabet_size = 26;

extern string messageForUserAskingWhereDictionaryIsStored;
extern string messageForUserAskingTenLetters;
extern string messageForUserAskingWhereLinksSaveTo;
extern string messageForUserAskingWhereDataSaveTo;


struct Node
{
    Data data;
    bool endWord;
    int index;
    string prefix;
    Node *children[alphabet_size];
    Node *parent;
};

class ScrabbleTree
{
private:
    Node * root;
    string subtractStrings(string &userInput, string &sub);
    Node *newNode(Data d);
    void deallocateNode(Node* node);
public:
    ScrabbleTree(void);
    ~ScrabbleTree(void);
    void insertWordToTree(string &s, int &index);
    void searchAllCombinationsOfWords(string &userInputForAlgo);
    void runSerialization(string &linksFileName, string &dataFileName);
    void runDeserialization(string &linksFileName, string &dataFileName);
    void readTheDataFromFileAndPutIntoTree(string &dataFileName);
};



#endif /* ScrabbleTree_h */