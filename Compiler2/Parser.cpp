//
//  Parser.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/31/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "Parser.hpp"

Parser::Parser(string file_name, bool has_seen_comment, bool was_file_redirected) : m_scanner(file_name, has_seen_comment, was_file_redirected), m_parseTree(nullptr) {
    
}

Parser::~Parser() {
    deinit();
}

void Parser::runParser() {
    
}

void Parser::setCurrentToken(const Token NEW_TOKEN) {
    m_currentToken = NEW_TOKEN;
}

Token Parser::getCurrentToken() const {
    return m_currentToken;
}

ParseTree Parser::getParseTree() const {
    return m_parseTree;
}

void Parser::setParseTree(const ParseTree NEW_PARSE_TREE) {
    m_parseTree = NEW_PARSE_TREE;
}

// private methods

void Parser::getTokenFromScanner() {
    setCurrentToken(m_scanner.buildToken());
}

void Parser::deinit() {

}

void Parser::program() {
    
}

void Parser::block() {
    
}

void Parser::vars() {
    
}

void Parser::mvars() {
    
}

void Parser::expr() {
    
}

void Parser::M() {
    
}

void Parser::F() {
    
}

void Parser::T() {
    
}

void Parser::R() {
    
}

void Parser::stats() {
    
}

void Parser::mStat() {
    
}

void Parser::in() {
    
}

void Parser::out() {
    
}

void Parser::If() {
    
}

void Parser::loop() {
    
}

void Parser::assign() {
    
}

void Parser::RO() {
    
}
