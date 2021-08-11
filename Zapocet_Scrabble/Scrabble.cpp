//
//  Scrabble.cpp
//  Zapocet_Scrabble
//
//  Created by Paul Ekishev on 06/08/2021.
//

#include "Scrabble.h"



string messageForUserAskingWhereDictionaryIsStored = "Enter the file name where the dictionary text is stored: ";
string messageForUserAskingWhereLinksSaveTo = "Enter the file name to witch you want write links: ";
string messageForUserAskingWhereDataSaveTo = "Enter the file name to witch you want write data: ";
string messageForUserAskingTenLetters = "Enter any 10 letters you want: ";



void Scrabble::cinIgnore() {
    cin.clear();
    cin.ignore(433443, '\n');
    cout << "Error, please enter again" << endl;
}


string Scrabble::promtUserForEnterTenLetters(string &userMessage){
    string tenLetters;
    while(true){
        cout << userMessage;
        cin >> tenLetters;
        makeStringAlphabeticalAndLowerCase(tenLetters);
        if(tenLetters.size() != 10){
            cinIgnore();
            continue;
        }
        break;
    }
    return tenLetters;
}

string Scrabble::promtUserToEnterFileName(string &messageForUser, int index){ // index = 0 - for reading, index = 1 - for writing
    fstream file;
    string fileName;
    while(!file.is_open()){
        cout << messageForUser;
        cin >> fileName;
        switch (index) {
            case 0:
                file.open(fileName, fstream::in);
                break;
            case 1:
                file.open(fileName, fstream::out);
                break;
                
            default:
                cout << "Error, file could not be opened" << endl;
                break;
        }
        if(file.is_open()){
            file.close();
            break;
        }else{
            cinIgnore();
        }
    }
    return fileName;
}


void Scrabble::startGame(){
    
    string dictionaryFileName = promtUserToEnterFileName(messageForUserAskingWhereDictionaryIsStored, 0);
    ScrabbleTree *scrabbleTree = new ScrabbleTree;
    scrabbleTree->readTheDataFromFileAndPutIntoTree(dictionaryFileName);
    string tenLettersForAlgo = promtUserForEnterTenLetters(messageForUserAskingTenLetters);
    cout << "Yours input: " << tenLettersForAlgo << endl;
    scrabbleTree->searchAllCombinationsOfWords(tenLettersForAlgo);
    
    string linksFileName = promtUserToEnterFileName(messageForUserAskingWhereLinksSaveTo, 1);
    string dataFileName = promtUserToEnterFileName(messageForUserAskingWhereDataSaveTo, 1);
    scrabbleTree->runSerialization(linksFileName, dataFileName);
    
    ScrabbleTree *scrabbleTreeDeserialization = new ScrabbleTree;
    scrabbleTreeDeserialization->runDeserialization(linksFileName, dataFileName);
    cout << "Yours input: " << tenLettersForAlgo << endl;
    scrabbleTreeDeserialization->searchAllCombinationsOfWords(tenLettersForAlgo);
    
    delete scrabbleTree;
    delete scrabbleTreeDeserialization;
    
}





