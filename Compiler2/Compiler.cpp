/*
//  Jack Pettit
//  Compiler.cpp
//  Compiler2
//  October 10, 2017
*/

#include "Compiler.hpp"

Compiler::Compiler(string inputFileName) {
    setInputFileName(inputFileName);
}

Compiler::~Compiler() {
    setInputFileName("");
}

void Compiler::setInputFileName(string newInputFileName) {
    m_inputFileName = newInputFileName;
}

string Compiler::getInputFileName() {
    return m_inputFileName;
}

void Compiler::runScanner() {
    m_testScanner.setFileName(getInputFileName());
    m_testScanner.testScanner();
}
