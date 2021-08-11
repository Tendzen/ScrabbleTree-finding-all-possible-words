//
//  main.cpp
//  Zapocet_Scrabble
//
//  Created by Paul Ekishev on 25/05/2021.
//

#include "Scrabble.h"




int main() {
    
    Scrabble *scrabble = new Scrabble;
    scrabble->startGame();
    delete scrabble;
    return 0;
}

