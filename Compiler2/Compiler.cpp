/*
//  Jack Pettit
//  Compiler.cpp
//  Compiler2
//  October 10, 2017
*/

#include "Compiler.hpp"

Compiler::Compiler(string inputFileName, string extension) : m_inputFileName(inputFileName), m_parser(inputFileName, false, false), m_EXTENSION(extension)  {
    buildFullFile();
    m_testScanner.setFileName(getFullFileName());
}

Compiler::~Compiler() {
    setInputFileName("");
}

void Compiler::setInputFileName(string newInputFileName) {
    m_inputFileName = newInputFileName;
}

string Compiler::getInputFileName() const {
    return m_inputFileName;
}

void Compiler::runCompiler() {
    //m_parser.runParser();
    m_testScanner.testScanner();
}

void Compiler::buildFullFile() {
    setFullFileName(getInputFileName().append(getFileExtension()));
}

void Compiler::setFullFileName(string new_Full_File_Name_Extension) {
    m_inputFileName_w_Extension = new_Full_File_Name_Extension;
}

string Compiler::getFileExtension() const {
    return m_EXTENSION;
}

string Compiler::getFullFileName() const {
    return m_inputFileName_w_Extension;
}
