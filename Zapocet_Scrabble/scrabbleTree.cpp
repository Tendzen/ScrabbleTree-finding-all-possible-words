#include "ScrabbleTree.h"


ScrabbleTree::ScrabbleTree(void)
{
    root = newNode('/');
    root->index = 0;
}


ScrabbleTree::~ScrabbleTree(void)
{
    deallocateNode(root);
}


Node *ScrabbleTree::newNode(Data d){
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

void ScrabbleTree::deallocateNode(Node* node){
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


void ScrabbleTree::readTheDataFromFileAndPutIntoTree(string &dataFileName){
    ifstream dictionaryFile;
    dictionaryFile.open(dataFileName);
    if(dictionaryFile.is_open()){
        string s;
        int index = 0;
        while (!dictionaryFile.eof()) {
            dictionaryFile >> s;
            makeStringAlphabeticalAndLowerCase(s);
            insertWordToTree(s, index);
        }
    }
    else{
        cout << "Error, file could not be opened" << endl;
    }
    dictionaryFile.close();
}



void ScrabbleTree::insertWordToTree(string &s, int &index){
    Node* temp = root;
    int alphabetIndex;
    for(int i = 0; i<s.length(); i++){
        alphabetIndex = s[i] - 'a';
        if(!temp->children[alphabetIndex]){
            temp->children[alphabetIndex] = newNode(s[i]);
            temp->children[alphabetIndex]->parent = temp;
            temp->children[alphabetIndex]->prefix = temp->prefix + temp->children[alphabetIndex]->data;
            index++;
            temp->children[alphabetIndex]->index = index;
        }
        temp = temp->children[alphabetIndex];
    }
    if(temp != root){
    temp->endWord = true;
    }
}


void ScrabbleTree::runSerialization(string &fileNameWithLinks, string &fileNameWithData){
    map<pNode, bool> visited;
    ofstream linksFile;
    ofstream dataFile;
    queue<pNode>QNodes;
    visited[root] = true;
    QNodes.push(root);
    linksFile.open(fileNameWithLinks);
    dataFile.open(fileNameWithData);
    while(QNodes.size() != 0){
        Node* curr = QNodes.front();
        QNodes.pop();
        if(curr != nullptr){
            dataFile << curr->index << " " << curr->data << " ";
            dataFile << ((curr->endWord == true) ? 1 : 0);
            linksFile << curr->index;
        }
        for(int i =0; i<26; i++){
            if(curr->children[i] && !visited[curr->children[i]]){
                visited[curr->children[i]] = true;
                linksFile << " ";
                linksFile << curr->children[i]->index;
                QNodes.push(curr->children[i]);
            }
        }
        if(QNodes.size() > 0){
            dataFile << "\n";
            linksFile << "\n";
        }
    }
    dataFile.close();
    linksFile.close();
}

void ScrabbleTree::runDeserialization(string &linksFileName, string &dataFileName){
    unordered_map<int, pNode>mapOfNodes;
    ifstream fileWithLinks;
    ifstream fileWithData;
    fileWithData.open(dataFileName);
    string delimetr = " ";
    if(fileWithData.is_open()){
        int posOfDelimetr, previousPos, indexInt, endWordInt;
        string line, index, endWord, letter;
        while(!fileWithData.eof()){
            previousPos = 0;
            posOfDelimetr = 0;
            getline(fileWithData,line);
            for(int i= 0; i<3; i++){
                posOfDelimetr = line.find(delimetr, posOfDelimetr+1);
                switch(i){
                    case 0:
                        index = line.substr(previousPos, posOfDelimetr);
                        indexInt = stoi(index);
                        previousPos = posOfDelimetr+1;
                        break;
                    case 1:
                        letter = line[previousPos];
                        previousPos = posOfDelimetr+1;
                        break;
                    case 2:
                        endWord = line[previousPos];
                        endWordInt = stoi(endWord);
                        previousPos = posOfDelimetr+1;
                        break;
                }
            }
            Node *node = newNode(letter[0]);
            node->index = indexInt; 
            node->endWord = (endWordInt == 1) ? true : false;
            mapOfNodes[node->index] = node;
        }
    }
    fileWithData.close();
    fileWithLinks.open(linksFileName);
    if(fileWithLinks.is_open()){
        queue<int>nodeIndexes;
        queue<int>indexesOfNodeAndHisChildren;
        Node* curr;
        Node* children;
        Node* candidateForNode;
        int indexOfNode, alphabetIndex;
        string line;
        while(getline(fileWithLinks,line)){
            istringstream iss(line);
            while(iss >> indexOfNode){
                indexesOfNodeAndHisChildren.push(indexOfNode);
            }
            
            indexOfNode = indexesOfNodeAndHisChildren.front();
            indexesOfNodeAndHisChildren.pop();
            if(indexOfNode == 0){
                curr = mapOfNodes[indexOfNode];
                root = curr;
            }else{
                candidateForNode = mapOfNodes[indexOfNode];
                curr = candidateForNode;
            }
            if(indexesOfNodeAndHisChildren.size() > 0){
                for(int i =0; indexesOfNodeAndHisChildren.size() !=0; i++){
                    indexOfNode = indexesOfNodeAndHisChildren.front();
                    indexesOfNodeAndHisChildren.pop();
                    children = mapOfNodes[indexOfNode];
                    alphabetIndex = children->data - 'a';
                    curr->children[alphabetIndex] = children;
                    children->parent = curr;
                    children->prefix = children->parent->prefix + children->data;
                }
            }
        }
    }
}


string ScrabbleTree::subtractStrings(string &userInput, string& sub){
    if(sub == ""){
        return userInput;
    }
    int pos;
    for(int i =0; i<sub.size(); i++){
        pos = userInput.find(sub[i]);
        if(pos >0){
        userInput.erase(userInput.begin() + pos);
        }
    }
    return userInput;
}


void ScrabbleTree::searchAllCombinationsOfWords(string &userInputForAlgo){
    map<pNode, bool> visited;
    stack<pNode>SNodes;
    vector<string>listOfWords;
    string workingCopy = userInputForAlgo;
    visited[root] = true;
    SNodes.push(root);
    int index;
    while(!SNodes.empty()){
        Node* curr = SNodes.top();
        workingCopy = userInputForAlgo;
        workingCopy = subtractStrings(workingCopy, curr->prefix);
        SNodes.pop();
        if(curr->endWord == true){
            listOfWords.push_back(curr->prefix);
        }
        for(int i =0; i<workingCopy.size(); i++){
            index = workingCopy[i] - 'a';
            if(curr->children[index] && !visited[curr->children[index]]){
                visited[curr->children[index]] = true;
                SNodes.push(curr->children[index]);
            }
        }
    }
    if(listOfWords.size() > 0){
        cout << "Words generated from your input:" << endl;
        for(int j = 0; j<listOfWords.size(); j++){
            cout << listOfWords[j] << endl;
        }
    }else{
        cout << "Nothing can be made up of these letters" << endl;
    }
}

    

