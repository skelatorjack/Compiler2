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

enum BranchType {
  BR, BRNEG, BRPOS,
  BRZERO, BRZNEG, BRZPOS
};

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
    void generateVarsOrMvars(const ParseNode);
    void generateBlock(const ParseNode);
    void generateExpr(const ParseNode);
    void generateM(const ParseNode);
    void generateR(const ParseNode, const int);
    void generateIn(const ParseNode, const int);
    void generateIf(const ParseNode);
    void generateLoop(const ParseNode);
    void generateAssign(const ParseNode, const int);
    void generateRO(const ParseNode);
    
    void writeStop();
    void writeNewLine();
    void writeVars();
    void writePush();
    void writePop();
    void writeLoad(const string);
    void writeWrite(const string);
    void writeAdd(const string);
    void writeStore(const string);
    void writeSub(const string);
    void writeDiv(const string);
    void writeMult(const string);
    void writeBranch(const string, const BranchType);
    void writeStackR(const int);
    void writeStackW(const int);
    void writeRead(const string);
    void writeCopy();
    bool isVarsOrMvars(const ParseNode);
public:
    CodeGenerator(string, string);
    ~CodeGenerator();
    void generateCode(const ParseNode);
    void popVars(const int);
    string getFullFileName() const;
    void setFullFileName(const string);
    void closeFile();
    void openFile();
    void removeFile();
};

#endif /* CODEGENERATOR_HPP */
