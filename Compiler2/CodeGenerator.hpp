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
#include "ParseTree.hpp"
#include "StaticSem.hpp"

enum BranchType {
  BR, BRNEG, BRPOS,
  BRZERO, BRZNEG, BRZPOS
};

class CodeGenerator {
private:
    vector<string> m_list_of_vars;
    vector<string> m_listOfLabels;
    vector<string> m_listOfTempVars;
    
    ofstream m_output_file;
    
    string m_full_file_name;
    
    StaticSem m_staticSemantics;
    ParseTree m_parseTree;
    
    string buildFullFileName(const string, const string);
    void addVarToList(const string);
    void addVarToTempList(const string);
    void deinit();
    
    // Nonterminals
    void generateProgram(const shared_ptr<ParseNode>);
    void generateVarsOrMvars(const shared_ptr<ParseNode>);
    void generateBlock(const int);
    void generateExpr(const shared_ptr<ParseNode>);
    void generateM(const shared_ptr<ParseNode>);
    void generateR(const shared_ptr<ParseNode>);
    void generateIn(const shared_ptr<ParseNode>);
    void generateIf(const shared_ptr<ParseNode>);
    void generateLoop(const shared_ptr<ParseNode>);
    void generateAssign(const shared_ptr<ParseNode>);
    void generateRO(const shared_ptr<ParseNode>);
    void generateOut(const shared_ptr<ParseNode>);
    void generateF(const shared_ptr<ParseNode>);
    
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
    
    bool isVarsOrMvars(const shared_ptr<ParseNode>);
    
    string createLabel();
    string createTempVariable();
    
    void popVars(const int);
    
    void exprTraversal(const shared_ptr<ParseNode>, bool&);
    void ifTraversal(const shared_ptr<ParseNode>, bool&);
    void loopTraversal(const shared_ptr<ParseNode>, bool&);
    void rTraversal(const shared_ptr<ParseNode>, bool&);
    void mTraversal(const shared_ptr<ParseNode>, bool&);
    void fTraversal(const shared_ptr<ParseNode>, bool&);
    void outTraversal(const shared_ptr<ParseNode>, bool&);
    void assignTraversal(const shared_ptr<ParseNode>, bool&);
    string getTempVariable(const int);
    void traverseTree(const shared_ptr<ParseNode>);
    void codeGen(const shared_ptr<ParseNode>);
    
public:
    CodeGenerator(string, string, int=-2);
    ~CodeGenerator();
    void generateCode();
    string getFullFileName() const;
    void setFullFileName(const string);
    void closeFile();
    void openFile();
    void removeFile();
    int getPosition() const;
    void setPosition(const int);
    void setParseTree(const ParseTree);
};

#endif /* CODEGENERATOR_HPP */
