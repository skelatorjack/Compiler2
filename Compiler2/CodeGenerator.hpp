//
//  CodeGenerator.hpp
//  Compiler2
//
//  Created by Jack Pettit on 11/26/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include "Includes.hpp"
#include "ParseNode.hpp"

class CodeGenerator {
private:
    vector<string> m_list_of_vars;
    ofstream m_output_file;
    string m_full_file_name;
    
    string buildFullFileName(const string, const string);
    void addVarToList(const ParseNode);
    void deinit();
    
    // Nonterminals
    void generateProgram(const ParseNode);
    void generateVars(const ParseNode);
    void generateMvars(const ParseNode);
    void generateBlock(const ParseNode);
    void generateExpr(const ParseNode);
    void generateM(const ParseNode);
    void generateR(const ParseNode);
    void generateIn(const ParseNode);
    void generateIf(const ParseNode);
    void generateLoop(const ParseNode);
    void generateAssign(const ParseNode);
    void generateRO(const ParseNode);
    
    void writeStop();
    void writeNewLine();
    void writeVars();
    void writePush();
    void writePop();
public:
    CodeGenerator(string, string);
    ~CodeGenerator();
    void generateCode(const ParseNode);
    void popVars(const int);
    string getFullFileName() const;
    void setFullFileName(const string);
    void closeFile();
    void openFile();
};

#endif /* CODEGENERATOR_HPP */
