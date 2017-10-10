//
//  Scanner.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "Scanner.hpp"

#include "Scanner.hpp"

// public methods

Scanner::Scanner() {
    buildTable(m_stateTable);
    setUpColumns();
}

Scanner::~Scanner() {
    m_stateTable.clear();
    columns.clear();
}

void Scanner::setCharsFromFile(deque<char> chars) {
    this->m_chars_From_File = chars;
}

deque<char> Scanner::getCharsFromFile() {
    return this->m_chars_From_File;
}
void Scanner::setFileForPreprocss(string inputName) {
    m_preprocessor.setFileName(inputName);
}

// private methods

bool Scanner::dontAppendChar(const char cur_Char, const int CUR_STATE) {
    return isCharNewLine(cur_Char) ||
    isCharWhiteSpace(cur_Char) || isExitState(CUR_STATE);
}

bool Scanner::isCharEndOfFile(const char CUR_CHAR) {
    return CUR_CHAR == '\xff';
}

int Scanner::getColumnNumber(char currentChar) {
    int column_Number = -1;
    
    column_Number = getColumn(currentChar);
    
    if (column_Number == -1) {
        reportError(-3);
        exit(-3);
    }
    
    return column_Number;
}

int Scanner::getColumn(const char KEY) {
    int column = -1;
    map<char, int>::const_iterator it;
    
    if (columns.find(KEY) != columns.end()) {
        it = columns.find(KEY);
        return it->second;
    }
    
    return column;
}

int Scanner::getNextState(const int CUR_STATE, const char CUR_CHAR) {
    char mapToKey = '\0';
    
    if (isCharLetter(CUR_CHAR)) {
        mapToKey = 'a';
    }
    else if (isCharDigit(CUR_CHAR)) {
        mapToKey = 'b';
    }
    else if (isCharWhiteSpace(CUR_CHAR)){
        mapToKey = 'w';
    }
    else if (isCharEndOfFile(CUR_CHAR)) {
        mapToKey = 'e';
    }
    else {
        mapToKey = CUR_CHAR;
    }
    
    const int NEW_COLUMN_NUM = getColumnNumber(mapToKey);
    
    try {
        return getState(CUR_STATE, NEW_COLUMN_NUM);
    }
    catch (const out_of_range &r) {
        cout << "Invalid table access at " << CUR_STATE << " , " << NEW_COLUMN_NUM << endl;
        exit(2);
    }
}

int Scanner::getState(const int ROW, const int COL) {
    return m_stateTable.at(ROW).at(COL);
}

void Scanner::popChar() {
    m_chars_From_File.pop_front();
}
bool Scanner::shouldPopChar(const char CUR_CHAR) {
    return isCharWhiteSpace(CUR_CHAR) || isCharNewLine(CUR_CHAR);
}

bool Scanner::isExitState(const int CUR_STATE) {
    return CUR_STATE >= 1000;
}

bool Scanner::isErrorState(const int CUR_STATE) {
    return CUR_STATE < 0;
}

void Scanner::preprocessInput() {
    m_preprocessor.preprocessInput();
}

void Scanner::reportError(const int ERROR_STATE) {
    
}
char Scanner::getChar() {
    return m_chars_From_File.front();
}

void Scanner::buildTable(vector < vector<int> > &table) {
    ifstream table_data;
    
    const int ROW_SIZE = 25;
    const int COL_SIZE = 27;
    
    vector<int> row;
    
    int data;
    
    table_data.open("tabledata.txt", fstream::in);
    
    for (int i = 0; i < COL_SIZE; i++) {
        for (int j = 0; j < ROW_SIZE; j++) {
            table_data >> data;
            row.push_back(data);
        }
        table.push_back(row);
        row.clear();
    }
    
    table_data.close();
}

bool Scanner::isCharOperator(char current_Char) {
    return true;
}

void Scanner::buildToken() {
    static Token current_Token;
    
    char current_Char = '\0';
    
    int current_State = 0;
    int next_State = 0;
    
    while (!isCharsFromFileEmpty()) {
        current_Char = getChar();
        
        popChar();
        
        next_State = getNextState(current_State, current_Char);
        current_State = next_State;
        
        if (isErrorState(current_State)) {
            reportError(current_State);
            exit(current_State);
        }
        else if (isExitState(current_State)) {
            current_Token.checkTokenInstance();
            testScanner(current_Token);
            current_Token.setUpNextToken();
            next_State = current_State = 0;
        }
        
        if (!dontAppendChar(current_Char, current_State)) {
            current_Token.appendChar(current_Char);
        }
        
        if (isCharNewLine(current_Char)) {
            current_Token.incrementLineNumber();
        }
        
        if (!shouldPopChar(current_Char) && isExitState(current_State)) {
            putBackChar(current_Char);
        }
    }
}

void Scanner::setupForBuildToken() {
    setCharsFromFile(m_preprocessor.getCharsFromFile());
}

bool Scanner::isCharsFromFileEmpty() {
    return m_chars_From_File.empty();
}

void Scanner::setUpColumns() {
    vector<char> chars = getChars();
    
    for (int i = 0; i < chars.size(); i++) {
        insertIntoColumns(chars.at(i), i);
    }
}

void Scanner::insertIntoColumns(const char KEY, const int VALUE) {
    columns.insert(pair<char, int>(KEY, VALUE));
}

vector<char> Scanner::getChars() {
    vector<char> chars;
    
    chars.push_back('a');
    chars.push_back('b');
    chars.push_back('<');
    chars.push_back('>');
    chars.push_back('=');
    chars.push_back('!');
    chars.push_back(':');
    chars.push_back('+');
    chars.push_back('-');
    chars.push_back('*');
    chars.push_back('/');
    chars.push_back('&');
    chars.push_back('%');
    chars.push_back('.');
    chars.push_back('(');
    chars.push_back(')');
    chars.push_back(',');
    chars.push_back('{');
    chars.push_back('}');
    chars.push_back(';');
    chars.push_back('[');
    chars.push_back(']');
    chars.push_back('e');
    chars.push_back('w');
    chars.push_back('\n');
    
    return chars;
}

void Scanner::testScanner(Token token) {
    token.toString();
}

bool Scanner::doesCurCharEqualLastCharOfToken(const char CUR_CHAR, Token current_Token) {
    
    return CUR_CHAR == current_Token.getLastCharOfInstance();
}

void Scanner::putBackChar(const char CUR_CHAR) {
    m_chars_From_File.push_front(CUR_CHAR);
}
