//
//  Scanner.hpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "Preprocessor.hpp"
#include "CharReader.hpp"
#include "Token.hpp"

class Scanner : public CharReader {
private:
    Preprocessor m_preprocessor;
    vector< vector<int> > m_stateTable;
    deque<char> m_chars_From_File;
    map<char, int> columns;
    
    void popChar();
    void putBackChar(const char);
    bool dontAppendChar(const char, const int);
    int getColumnNumber(const char);
    int getNextState(const int, const char);
    bool shouldPopChar(const char);
    bool isExitState(const int);
    void generateToken();
    void buildTable(vector< vector<int> >&);
    bool isErrorState(const int);
    void reportError(const int);
    virtual char getChar();
    virtual bool isCharOperator(char);
    bool isCharsFromFileEmpty();
    void setUpColumns();
    void insertIntoColumns(const char, const int);
    int getState(const int, const int);
    int getColumn(const char);
    vector<char> getChars();
    void testScanner(Token);
    bool isCharEndOfFile(const char);
    bool doesCurCharEqualLastCharOfToken(const char, Token);
    
public:
    Scanner();
    ~Scanner();
    void setCharsFromFile(deque<char>);
    virtual deque<char> getCharsFromFile();
    void setFileForPreprocss(string);
    void preprocessInput();
    void buildToken();
    void setupForBuildToken();
};

#endif /* Scanner_hpp */
