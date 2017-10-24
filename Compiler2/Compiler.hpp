/*
//  Jack Pettit
//  CS 4280
//  Compiler.hpp
//  Compiler2
//  October 10, 2017
*/

#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "Includes.hpp"
#include "TestScanner.hpp"

class Compiler {
private:
    string m_inputFileName;
    TestScanner m_testScanner;
    
public:
    Compiler(string="");
    ~Compiler();
    void setInputFileName(string);
    string getInputFileName();
    void runScanner();
};

#endif /* Compiler_hpp */
