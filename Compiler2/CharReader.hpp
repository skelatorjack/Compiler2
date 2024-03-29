//
//  CharReader.hpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef CHARREADER_HPP
#define CHARREADER_HPP

#include "Includes.hpp"

class CharReader {
public:
    bool isCharNewLine(char);
    bool isCharWhiteSpace(char);
    bool isCharLetter(char);
    bool isCharDigit(char);
    // Get chars from the file
    virtual deque<char> getCharsFromFile() = 0;
    // Get a character from a file or deque
    virtual char getChar() = 0;
};

#endif /* CharReader_hpp */
