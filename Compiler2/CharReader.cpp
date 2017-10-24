/*
    Jack Pettit
    CS 4280
    CharReader.cpp
    Compiler2
    10/10/17
*/

#include "CharReader.hpp"

bool CharReader::isCharNewLine(char cur_char) {
    return cur_char == '\n';
}

bool CharReader::isCharWhiteSpace(char cur_char) {
    return cur_char == ' ';
}

// The function isalpha returns zero if the character is not a letter
bool CharReader::isCharLetter(char cur_Char) {
    return isalpha((int)cur_Char) != 0;
}

// The function isdigit returns zero if the character is not a digit
bool CharReader::isCharDigit(char cur_Char) {
    return isdigit((int)cur_Char) != 0;
}
