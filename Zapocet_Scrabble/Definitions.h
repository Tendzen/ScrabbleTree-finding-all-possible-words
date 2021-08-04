#pragma once
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
public:
    ScrabbleTree(void);
    ~ScrabbleTree(void);
    void insertWordToTree(string &s, int &index);
    void searchAllCombinationsOfWords(string &userInputForAlgo);
    void runSerialization(string &linksFileName, string &dataFileName);
    void runDeserialization(string &linksFileName, string &dataFileName);
    void readTheDataFromFileAndPutIntoTree(string &dataFileName);
};

string subtractStrings(string &userInput, string &sub);
void cinIgnore();
char asciiToLower(char &letter);

string makeStringAlphabeticalAndLowerCase(string &s);

string promtUserToEnterFileName(string &messageForUser, int index);

string promtUserForEnterTenLetters(string &userMessage);


void startProgram();

Node *newNode(Data d);

void deallocateNode(Node* node);



