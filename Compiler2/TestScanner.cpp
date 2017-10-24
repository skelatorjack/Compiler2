/*
//  Jack Pettit
//  CS 4280
//  TestScanner.cpp
//  Compiler2
//  October 11, 2017
*/

#include "TestScanner.hpp"

TestScanner::TestScanner(string file_Name) {
    setFileName(file_Name);
}

TestScanner::~TestScanner() {
    clearString();
}

// Test run the scanner
void TestScanner::testScanner() {
    Token token;
    
    m_scanner.setFileForPreprocss(getFileName());
    m_scanner.preprocessInput();
    m_scanner.setupForBuildToken();
    
    do {
        token = m_scanner.buildToken();
        printToken(token);
    } while (token.getTokenId() != EOF_tk);
    
    m_scanner.deinit();
}

void TestScanner::setFileName(string file_Name) {
    m_fileName = file_Name;
}

string TestScanner::getFileName() {
    return m_fileName;
}
// private methods

void TestScanner::printToken(const Token TOKEN) {
    TOKEN.toString();
}

void TestScanner::clearString() {
    setFileName("");
}
