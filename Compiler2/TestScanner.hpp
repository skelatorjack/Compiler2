/*
//  Jack Pettit
//  CS 4280
//  TestScanner.hpp
//  Compiler2
//  October 11, 2017
*/

#ifndef TESTSCANNER_HPP
#define TESTSCANNER_HPP

#include "Scanner.hpp"
#include "TestScanner.hpp"

class TestScanner {
private:
    // private members
    Scanner m_scanner;
    string m_fileName;
    
    // private methods
    void printToken(const Token);
    void clearString();
    
public:
    void testScanner();
    void setFileName(string);
    string getFileName();
    TestScanner(string="");
    ~TestScanner();
};

#endif /* TestScanner_hpp */
