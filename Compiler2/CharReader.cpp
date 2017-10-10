//
//  CharReader.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "CharReader.hpp"

#include "CharReader.hpp"

bool CharReader::isCharNewLine(char cur_char) {
    return cur_char == '\n';
}

bool CharReader::isCharWhiteSpace(char cur_char) {
    return cur_char == ' ';
}

bool CharReader::isCharLetter(char cur_Char) {
    return isalpha((int)cur_Char) != 0;
}

bool CharReader::isCharDigit(char cur_Char) {
    return isdigit((int)cur_Char) != 0;
}
