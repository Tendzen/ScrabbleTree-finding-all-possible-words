//
//  helpFunction.cpp
//  Zapocet_Scrabble
//
//  Created by Paul Ekishev on 31/05/2021.
//

#include "helpFunction.h"


void cinIgnore() {
    cin.clear();
    cin.ignore(433443, '\n');
    cout << "Error, please enter again" << endl;
}


char asciiToLower(char &symbol){
    if (symbol <= 'Z' && symbol >= 'A'){
        symbol += 32;
        return symbol;
    }
    return symbol;
}



string makeStringAlphabeticalAndLowerCase(string &s){
    int stringSize = s.size();
    int i;
    for(i = 0; i<stringSize; i++){
        asciiToLower(s[i]);
        if(s[i] < 96 || s[i] >123){
            s.erase(s.begin() + i);
            stringSize = s.size();
            i--;
        }
    }
    return s;
}



