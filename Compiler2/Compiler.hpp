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

class Compiler {
private:
    string m_inputFileName;
    const string m_EXTENSION;
    string m_inputFileName_w_Extension;
    string m_redirectedFile;
    Parser m_parser;
    ParseTree m_parseTree;
    
    string buildFullFile();
    bool wasInputRedirected();
    void setPreprocessorFile(const string);
    
public:
    Compiler(string="", string=".fs17", string="");
    ~Compiler();
    void setInputFileName(string);
    string getInputFileName() const;
    void runCompiler();
    void runFrontEnd();
    void runBackEnd();
    string getFullFileName() const;
    void setFullFileName(string);
    string getFileExtension() const;
    void setRedirectedFile(string);
    string getRedirectedFile() const;
    void setParseTree(ParseTree);
    ParseTree getParseTree() const;
};

#endif /* Compiler_hpp */
