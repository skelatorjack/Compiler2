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

void CodeGenerator::generateVars(const ParseNode CUR_NODE) {
    writePush();
    addVarToList(CUR_NODE);
}

void CodeGenerator::generateMvars(const ParseNode CUR_NODE) {
    writePush();
    addVarToList(CUR_NODE);
}

void CodeGenerator::generateBlock(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateExpr(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateM(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateR(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateIn(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateIf(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateLoop(const ParseNode CUR_NODE) {
    
}

void CodeGenerator::generateAssign(const ParseNode CUR_NODE) {
    
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
