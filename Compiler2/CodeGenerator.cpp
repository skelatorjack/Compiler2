//
//  CodeGenerator.cpp
//  Compiler2
//
//  Created by Jack Pettit on 11/26/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "CodeGenerator.hpp"

CodeGenerator::CodeGenerator(string basename, string extension, int position): m_list_of_vars(), m_output_file(), m_full_file_name(""), m_staticSemantics(), m_parseTree() {
    
    setFullFileName(buildFullFileName(basename, extension));
}

CodeGenerator::~CodeGenerator() {
    deinit();
}


void CodeGenerator::generateCode() {
    traverseTree(m_parseTree.getRoot());
}

void CodeGenerator::codeGen(const shared_ptr<ParseNode> CUR_NODE) {
    if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "expr")) {
        exprTraversal(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "if")) {
        ifTraversal(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "M")) {
        mTraversal(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "Loop")) {
        loopTraversal(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "block")) {
        m_staticSemantics.addNewScope();
    }
    else if (m_parseTree.doesNodeDeclareVars(CUR_NODE) && m_parseTree.doesNodeHoldToken(CUR_NODE)) {
        m_staticSemantics.addVarToCurrentScope(CUR_NODE->getStoredToken());
        generateVarsOrMvars(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "out")) {
        generateOut(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "assign")) {
        generateAssign(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "R")) {
        generateR(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "F")) {
        generateF(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "RO")) {
        generateRO(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "in")) {
        generateIn(CUR_NODE);
    }
    else {
        traverseTree(CUR_NODE->getChild(firstChild));
        traverseTree(CUR_NODE->getChild(secondChild));
        traverseTree(CUR_NODE->getChild(thirdChild));
        traverseTree(CUR_NODE->getChild(fourthChild));
    }
}
void CodeGenerator::traverseTree(const shared_ptr<ParseNode> CUR_NODE) {
    if (m_parseTree.isNodeNull(CUR_NODE)) {
        return;
    }
    
    codeGen(CUR_NODE);
    
    if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "block")) {
        const int TIMES_TO_POP = m_staticSemantics.getVarsInScope();
        m_staticSemantics.removeCurrentScope();
        popVars(TIMES_TO_POP);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "program")) {
        generateProgram(CUR_NODE);
    }
}
void CodeGenerator::exprTraversal(const shared_ptr<ParseNode> CURRENT_NODE) {
    if (CURRENT_NODE->getStoredToken().doesTokenMatchId(Plus_tk) || CURRENT_NODE->getStoredToken().doesTokenMatchId(Minus_tk)) {
        generateExpr(CURRENT_NODE);
    }
}
void CodeGenerator::popVars(const int NUM_OF_VARS) {
    for (int i = 0; i < NUM_OF_VARS; i++) {
        writePop();
    }
}

void CodeGenerator::setParseTree(const ParseTree newTree) {
    m_parseTree = newTree;
}

string CodeGenerator::getFullFileName() const {
    return m_full_file_name;
}

void CodeGenerator::setFullFileName(const string full_file_name) {
    m_full_file_name = full_file_name;
}

void CodeGenerator::openFile() {
    m_output_file.open(getFullFileName().c_str());
}

void CodeGenerator::closeFile() {
    if (m_output_file.is_open()) {
        m_output_file.close();
    }
}

void CodeGenerator::removeFile() {
    closeFile();
    remove(m_full_file_name.c_str());
}
// Private methods

string CodeGenerator::buildFullFileName(const string basename, const string extension) {
    stringstream str;
    
    str << basename << extension;
    
    return str.str();
}

void CodeGenerator::addVarToList(const shared_ptr<ParseNode> CUR_NODE) {
    m_list_of_vars.push_back(CUR_NODE->getStoredToken().getTokenInstance());
}

void CodeGenerator::deinit() {
    m_list_of_vars.clear();
    m_full_file_name.clear();
}

void CodeGenerator::generateProgram(const shared_ptr<ParseNode> CUR_NODE) {
    writeStop();
    writeVars();
}

void CodeGenerator::generateVarsOrMvars(const shared_ptr<ParseNode> CUR_NODE) {
    writePush();
    addVarToList(CUR_NODE);
}

string CodeGenerator::createLabel() {
    return "";
}

string CodeGenerator::createTempVariable() {
    string temp_var = "";
    const string UNDER_SCORE = "_";
    const string SIZE = to_string(m_listOfLabels.size());
    
    temp_var.append(UNDER_SCORE);
    temp_var.append(SIZE);
    
    return temp_var;
}

string CodeGenerator::getTempVariable(const int INDEX) {
    if (INDEX > m_listOfTempVars.size()) {
        return m_listOfTempVars.back();
    }
    else if (INDEX < 0) {
        return m_listOfTempVars.front();
    }
    
    return m_listOfTempVars.at(INDEX);
}

void CodeGenerator::generateBlock(const int NUM_VARS) {
    popVars(NUM_VARS);
}

void CodeGenerator::generateExpr(const shared_ptr<ParseNode> CUR_NODE) {
    
}

void CodeGenerator::generateM(const shared_ptr<ParseNode> CUR_NODE) {
    
}

void CodeGenerator::generateR(const shared_ptr<ParseNode> CUR_NODE) {
    
}

void CodeGenerator::generateIn(const shared_ptr<ParseNode> CUR_NODE) {
    
}

void CodeGenerator::generateIf(const shared_ptr<ParseNode> CUR_NODE) {
    
}

void CodeGenerator::generateLoop(const shared_ptr<ParseNode> CUR_NODE) {
    
}

void CodeGenerator::generateAssign(const shared_ptr<ParseNode> CUR_NODE) {
    
}

void CodeGenerator::generateRO(const shared_ptr<ParseNode> CUR_NODE) {
    const TokenId RELOP = CUR_NODE->getStoredToken().getTokenId();
    
    if (RELOP == LTE_tk) {
        writeBranch("label", BRPOS);
    }
    else if (RELOP == LT_tk) {
        writeBranch("label", BRZPOS);
    }
    else if (RELOP == GTE_tk) {
        writeBranch("label", BRNEG);
    }
    else if (RELOP == GT_tk) {
        writeBranch("label", BRZNEG);
    }
    else if (RELOP == DoubleEqual_tk) {
        writeBranch("label", BRPOS);
        writeNewLine();
        writeBranch("label", BRNEG);
    }
    else if (RELOP == ExclEqual_tk) {
        writeBranch("LABEL", BRZERO);
    }
}

void CodeGenerator::writeStop() {
    m_output_file << "STOP";
    writeNewLine();
}

void CodeGenerator::writeNewLine() {
    m_output_file << endl;
}

void CodeGenerator::writeVars() {
    for (int i = 0; i < m_list_of_vars.size(); i++) {
        m_output_file << m_list_of_vars.at(i) << " " << "0";
        writeNewLine();
    }
}

void CodeGenerator::writePush() {
    m_output_file << "PUSH";
    writeNewLine();
}

void CodeGenerator::writePop() {
    m_output_file << "POP";
    writeNewLine();
}

void CodeGenerator::writeLoad(const string CUR_INSTANCE) {
    m_output_file << "LOAD " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeWrite(const string CUR_INSTANCE) {
    m_output_file << "WRITE " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeAdd(const string CUR_INSTANCE) {
    m_output_file << "ADD " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeStore(const string CUR_INSTANCE) {
    m_output_file << "STORE " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeSub(const string CUR_INSTANCE) {
    m_output_file << "SUB " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeDiv(const string CUR_INSTANCE) {
    m_output_file << "DIV " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeMult(const string CUR_INSTANCE) {
    m_output_file << "MULT " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeBranch(const string CUR_INSTANCE, const BranchType COND) {
    switch(COND) {
        case BRZERO:
            m_output_file << "BRZERO ";
            break;
            
        case BRNEG:
            m_output_file << "BRNEG ";
            break;
        
        case BRZPOS:
            m_output_file << "BRZPOS ";
            break;
            
        case BRPOS:
            m_output_file << "BRPOS ";
            break;
            
        case BRZNEG:
            m_output_file << "BRZNEG ";
            break;
            
        case BR:
            m_output_file << "BR ";
            break;
            
        default:
            break;
    }
    
    m_output_file << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeStackR(const int POS) {
    m_output_file << "STACKR " << POS;
    writeNewLine();
}

void CodeGenerator::writeStackW(const int POS) {
    m_output_file << "STACKW " << POS;
    writeNewLine();
}

void CodeGenerator::writeRead(const string CUR_INSTANCE) {
    m_output_file << "READ " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeCopy() {
    
}

bool CodeGenerator::isVarsOrMvars(const shared_ptr<ParseNode> CUR_NODE) {
    const string NONTERMINAL = CUR_NODE->getNonTerminal();
    
    return NONTERMINAL == "vars" || NONTERMINAL == "mvars";
}
