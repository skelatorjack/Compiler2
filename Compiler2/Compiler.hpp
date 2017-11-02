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
#include "Parser.hpp"
#include "TestScanner.hpp"

class Compiler {
private:
    string m_inputFileName;
    const string m_EXTENSION;
    string m_inputFileName_w_Extension;
    Parser m_parser;
    TestScanner m_testScanner;
    
    string buildFullFile();
    
public:
    Compiler(string="", string=".fs17", bool = false);
    ~Compiler();
    void setInputFileName(string);
    string getInputFileName() const;
    void runScanner();
    void runCompiler();
    string getFullFileName() const;
    void setFullFileName(string);
    string getFileExtension() const;
};

#endif /* Compiler_hpp */
