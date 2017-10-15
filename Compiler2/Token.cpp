//
//  Token.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "Token.hpp"

Token::Token(TokenId id, string token_Instance, int token_LineNumber) {
    setTokenId(id);
    setTokenInstance(token_Instance);
    setTokenLineNumber(token_LineNumber);
    setUpMaps();
}

Token::~Token() {
    setTokenId(EOF_tk);
    setTokenInstance("");
    setTokenLineNumber(-1);
}

void Token::setTokenId(TokenId id) {
    m_tokenId = id;
}

void Token::setTokenInstance(string instance) {
    m_tokenInstance = instance;
}

void Token::setTokenLineNumber(int lineNumber) {
    m_tokenLineNumber = lineNumber;
}

TokenId Token::getTokenId() const {
    return m_tokenId;
}

string Token::getTokenInstance() const {
    return m_tokenInstance;
}

int Token::getTokenLineNumber() const {
    return m_tokenLineNumber;
}

void Token::incrementLineNumber() {
    setTokenLineNumber(getTokenLineNumber() + 1);
}

void Token::appendChar(char newChar) {
    m_tokenInstance.append(1, newChar);
}

void Token::checkTokenInstance() {
    if (checkDoesTokenMatchNumber() && !getTokenInstance().empty()) {
        setTokenId(Num_tk);
    }
    else if (checkDoesTokenMatchKeyWord()) {
        setTokenId(getValueWithKey(getTokenInstance(), 'k'));
    }
    else if (checkDoesTokenMatchDelimiter()) {
        setTokenId(getValueWithKey(getTokenInstance(), 'd'));
    }
    else if (checkDoesTokenMatchOperator()) {
        setTokenId(getValueWithKey(getTokenInstance(), 'o'));
    }
    else if (getTokenInstance().empty()) {
        setTokenId(EOF_tk);
    }
    else {
        setTokenId(Ident_tk);
    }
}

bool Token::checkDoesTokenMatchNumber() {
    const string TOK_INST = getTokenInstance();
    
    for (int i = 0; i < TOK_INST.size(); i++) {
        if (!isdigit(TOK_INST.at(i))) {
            return false;
        }
    }
    return true;
}

bool Token::checkDoesTokenMatchKeyWord() {
    return m_keyWords.find(getTokenInstance().c_str()) != m_keyWords.end();
}

bool Token::checkDoesTokenMatchIdentifier() {
    return isalpha(atoi(getTokenInstance().c_str()));
}

bool Token::checkDoesTokenMatchOperator() {
    return m_operators.find(getTokenInstance().c_str()) != m_operators.end();
}

bool Token::checkDoesTokenMatchDelimiter() {
    return m_delims.find(getTokenInstance().c_str()) != m_delims.end();
}
void Token::setUpMaps() {
    setUpKeyWords();
    setUpOps();
    setUpDelims();
}
void Token::setUpKeyWords() {
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

void Token::setUpOps() {
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

void Token::setUpDelims() {
    insertValue("(", LParan_tk, 'd');
    insertValue(")", RParan_tk, 'd');
    insertValue("[", LBracket_tk, 'd');
    insertValue("]", RBracket_tk, 'd');
    insertValue("{", LBrace_tk, 'd');
    insertValue("}", RBrace_tk, 'd');
}

void Token::insertValue(string key, TokenId id, const char WHICH_MAP) {
    switch (WHICH_MAP) {
        case 'k': m_keyWords.insert(pair<string, TokenId>(key, id));
            break;
        case 'd': m_delims.insert(pair<string, TokenId>(key, id));
            break;
        case 'o': m_operators.insert(pair<string, TokenId>(key, id));
            break;
    }
}

TokenId Token::getValueWithKey(string key, const char WHICH_MAP) {
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

void Token::toString() const {
    cout << "ID: " << getTokenId() << " ";
    cout << "Instance: " << getTokenInstance() << " ";
    cout << "Line Number: " << getTokenLineNumber() << endl;
}

void Token::setUpNextToken(int new_LineNumber) {
    setTokenInstance("");
    setTokenId(EOF_tk);
    setTokenLineNumber(new_LineNumber);
}

char Token::getLastCharOfInstance() {
    return getTokenInstance().back();
}
