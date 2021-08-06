//
//  Scrabble.h
//  Zapocet_Scrabble
//
//  Created by Paul Ekishev on 06/08/2021.
//
#pragma once
#ifndef Scrabble_h
#define Scrabble_h

#include "ScrabbleTree.h"



class Scrabble {
private:
    ScrabbleTree *tree;
    string promtUserToEnterFileName(string &messageForUser, int index);
    string promtUserForEnterTenLetters(string &userMessage);
    
public:
    void startGame();
};












#endif /* Scrabble_h */
