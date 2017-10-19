//
//  Scanner.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "Scanner.hpp"

// public methods

Scanner::Scanner() {
    buildTable(m_stateTable);
    setUpColumns();
    setUpMaps();
}

Scanner::~Scanner() {

}

void Scanner::deinit() {
    m_stateTable.clear();
    columns.clear();
    m_chars_From_File.clear();
    m_keyWords.clear();
    m_delims.clear();
    m_operators.clear();
    m_preprocessor.deinit();
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
        cout << "Invalid column number " << column_Number << endl;
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
    return isCharWhiteSpace(CUR_CHAR) || isCharNewLine(CUR_CHAR) || isCharEndOfFile(CUR_CHAR);
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

void Scanner::reportError(const int ERROR_STATE, const Token INVALID_TOK) {
    cout << "Error invalid token " << INVALID_TOK.getTokenInstance() << " The state is " << ERROR_STATE << endl;
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

Token Scanner::buildToken() {
    static Token current_Token;
    static int saved_LineNumber = 1;
    
    char current_Char = '\0';
    
    current_Token.setUpNextToken(saved_LineNumber);
    
    int current_State = 0;
    int next_State = 0;
    
    while (!isCharsFromFileEmpty()) {
        current_Char = getChar();
        
        popChar();
        
        next_State = getNextState(current_State, current_Char);
        current_State = next_State;
        
        if (isCharNewLine(current_Char)) {
            //current_Token.incrementLineNumber();
            saved_LineNumber++;
        }
        
        if (isErrorState(current_State)) {
            reportError(current_State, current_Token);
            exit(current_State);
        }
        else if (isExitState(current_State)) {
            checkTokenInstance(current_Token);
            
            if (!shouldPopChar(current_Char)) {
                putBackChar(current_Char);
            }
            if (current_Token.getTokenInstance().empty()) {
                current_Token.setUpNextToken(saved_LineNumber);
                current_State = next_State = 0;
                continue;
            }
            else {
               break;
            }
        }
        
        if (!dontAppendChar(current_Char, current_State)) {
            current_Token.appendChar(current_Char);
        }
        
        if (!shouldPopChar(current_Char) && isExitState(current_State)) {
            putBackChar(current_Char);
        }
    }
    return current_Token;
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

bool Scanner::checkDoesTokenMatchNumber(const Token TOKEN) {
    const string TOK_INST = TOKEN.getTokenInstance();
    
    for (int i = 0; i < TOK_INST.size(); i++) {
        if (!isdigit(TOK_INST.at(i))) {
            return false;
        }
    }
    return true;
}

bool Scanner::checkDoesTokenMatchKeyWord(const Token TOKEN) {
    return m_keyWords.find(TOKEN.getTokenInstance().c_str()) != m_keyWords.end();
}

bool Scanner::checkDoesTokenMatchIdentifier(const Token TOKEN) {
    return isalpha(atoi(TOKEN.getTokenInstance().c_str()));
}

bool Scanner::checkDoesTokenMatchOperator(const Token TOKEN) {
    return m_operators.find(TOKEN.getTokenInstance().c_str()) != m_operators.end();
}

bool Scanner::checkDoesTokenMatchDelimiter(const Token TOKEN) {
    return m_delims.find(TOKEN.getTokenInstance().c_str()) != m_delims.end();
}

void Scanner::checkTokenInstance(Token &token) {
    if (checkDoesTokenMatchNumber(token) && !token.getTokenInstance().empty()) {
        token.setTokenId(Num_tk);
    }
    else if (checkDoesTokenMatchKeyWord(token)) {
        token.setTokenId(getValueWithKey(token.getTokenInstance(), 'k'));
    }
    else if (checkDoesTokenMatchDelimiter(token)) {
        token.setTokenId(getValueWithKey(token.getTokenInstance(), 'd'));
    }
    else if (checkDoesTokenMatchOperator(token)) {
        token.setTokenId(getValueWithKey(token.getTokenInstance(), 'o'));
    }
    else if (token.getTokenInstance().empty()) {
        token.setTokenId(EOF_tk);
    }
    else {
        token.setTokenId(Ident_tk);
    }
}
void Scanner::setUpMaps() {
    setUpKeyWords();
    setUpOps();
    setUpDelims();
}
void Scanner::setUpKeyWords() {
    insertValue("Begin", Begin_tk, 'k');
    insertValue("End", End_tk, 'k');
    insertValue("Check", Check_tk, 'k');
    insertValue("Loop", Loop_tk, 'k');
    insertValue("Void", Void_tk, 'k');
    insertValue("Var", Var_tk, 'k');
    insertValue("Return", Return_tk, 'k');
    insertValue("Input", Input_tk, 'k');
    insertValue("Output", Output_tk, 'k');
    insertValue("Program", Program_tk, 'k');
}

void Scanner::setUpOps() {
    insertValue("=", Equal_tk,'o');
    insertValue("<", LT_tk, 'o');
    insertValue("<=", LTE_tk, 'o');
    insertValue(">", GT_tk, 'o');
    insertValue(">=", GTE_tk, 'o');
    insertValue("!=", ExclEqual_tk, 'o');
    insertValue("==", DoubleEqual_tk, 'o');
    insertValue(":", Colon_tk, 'o');
    insertValue("+", Plus_tk, 'o');
    insertValue("-", Minus_tk, 'o');
    insertValue("*", Star_tk, 'o');
    insertValue("/", Slash_tk, 'o');
    insertValue("&", Amp_tk, 'o');
    insertValue(".", Dot_tk, 'o');
    insertValue(";", Semicolon_tk, 'o');
}

void Scanner::setUpDelims() {
    insertValue("(", LParan_tk, 'd');
    insertValue(")", RParan_tk, 'd');
    insertValue("[", LBracket_tk, 'd');
    insertValue("]", RBracket_tk, 'd');
    insertValue("{", LBrace_tk, 'd');
    insertValue("}", RBrace_tk, 'd');
}

void Scanner::insertValue(string key, TokenId id, const char WHICH_MAP) {
    switch (WHICH_MAP) {
        case 'k': m_keyWords.insert(pair<string, TokenId>(key, id));
            break;
        case 'd': m_delims.insert(pair<string, TokenId>(key, id));
            break;
        case 'o': m_operators.insert(pair<string, TokenId>(key, id));
            break;
    }
}

TokenId Scanner::getValueWithKey(string key, const char WHICH_MAP) {
    TokenId id = EOF_tk;
    map<string, TokenId>::const_iterator it;
    
    switch(WHICH_MAP) {
        case 'k': it = m_keyWords.find(key);
            break;
        case 'o': it = m_operators.find(key);
            break;
        case 'd': it = m_delims.find(key);
            break;
    }
    id = it->second;
    return id;
}
