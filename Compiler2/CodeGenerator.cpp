//
//  CodeGenerator.cpp
//  Compiler2
//
//  Created by Jack Pettit on 11/26/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "CodeGenerator.hpp"

CodeGenerator::CodeGenerator(string basename, string extension): m_list_of_vars(), m_output_file(), m_full_file_name("") {
    
    setFullFileName(buildFullFileName(basename, extension));
}

CodeGenerator::~CodeGenerator() {
    deinit();
}

void CodeGenerator::generateCode(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::popVars(const int NUM_OF_VARS) {
    for (int i = 0; i < NUM_OF_VARS; i++) {
        writePop();
    }
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
    remove(m_full_file_name.c_str());
}
// Private methods

string CodeGenerator::buildFullFileName(const string basename, const string extension) {
    stringstream str;
    
    str << basename << extension;
    
    return str.str();
}

void CodeGenerator::addVarToList(const ParseNode CUR_NODE) {
    m_list_of_vars.push_back(CUR_NODE.getStoredToken().getTokenInstance());
}

void CodeGenerator::deinit() {
    m_list_of_vars.clear();
    m_full_file_name.clear();
}

void CodeGenerator::generateProgram(const ParseNode CUR_NODE) {
    writeStop();
    writeVars();
}

void CodeGenerator::generateVarsOrMvars(const ParseNode CUR_NODE) {
    writePush();
    addVarToList(CUR_NODE);
}

void CodeGenerator::generateBlock(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateExpr(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateM(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateR(const ParseNode CUR_NODE, const int POS) {
    
}

void CodeGenerator::generateIn(const ParseNode CUR_NODE, const int POS) {
    
}

void CodeGenerator::generateIf(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateLoop(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateAssign(const ParseNode CUR_NODE, const int POS) {
    
}

void CodeGenerator::generateRO(const ParseNode CUR_NODE) {
    
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

bool CodeGenerator::isVarsOrMvars(const ParseNode CUR_NODE) {
    const string NONTERMINAL = CUR_NODE.getNonTerminal();
    
    return NONTERMINAL == "vars" || NONTERMINAL == "mvars";
}
