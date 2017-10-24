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

// Add a character to the token instance
void Token::appendChar(char newChar) {
    m_tokenInstance.append(1, newChar);
}

// Print token information
void Token::toString() const {
    cout << "ID: " << getTokenId() << ", ";
    cout << "Instance: " << getTokenInstance() << ", ";
    cout << "Line Number: " << getTokenLineNumber() << endl;
}

// Clear the next token and set its line number to new_LineNumber
void Token::setUpNextToken(int new_LineNumber) {
    setTokenInstance("");
    setTokenId(EOF_tk);
    setTokenLineNumber(new_LineNumber);
}

// DON'T NEED THIS
char Token::getLastCharOfInstance() {
    return getTokenInstance().back();
}
