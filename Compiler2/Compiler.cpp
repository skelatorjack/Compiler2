//
//  Compiler.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "Compiler.hpp"

#include "Compiler.hpp"

Compiler::Compiler(string inputFileName) {
    this->setInputFileName(inputFileName);
}

Compiler::~Compiler() {
    setInputFileName("");
}

void Compiler::setInputFileName(string inputFileName) {
    this->m_inputFileName = inputFileName;
}

string Compiler::getInputFileName() {
    return this->m_inputFileName;
}

void Compiler::runScanner() {
    m_testScanner.setFileName(getInputFileName());
    m_testScanner.testScanner();
}
