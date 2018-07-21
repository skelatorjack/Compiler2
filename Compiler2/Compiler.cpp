/*
//  Jack Pettit
//  Compiler.cpp
//  Compiler2
//  October 10, 2017
*/


#include "Compiler.hpp"

Compiler::Compiler(string inputFileName, string extension, string redirectedFile, string output_extension) : m_inputFileName(inputFileName), m_redirectedFile(redirectedFile),  m_EXTENSION(extension), m_parseTree(), m_codeGenerator(inputFileName, output_extension) {
    
    setFullFileName(buildFullFile());
    
    if (wasInputRedirected()) {
        m_parser.setUpPreprocessor(getRedirectedFile());
    }
    else {
        m_parser.setUpPreprocessor(getFullFileName());
    }
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
    runFrontEnd();
    runBackEnd();
}

void Compiler::runFrontEnd() {
    m_parser.runParser(m_parseTree);
}

void Compiler::runBackEnd() {
    try {
        m_codeGenerator.setParseTree(m_parseTree);
        m_codeGenerator.generateCode();
    }
    catch (int errorCode) {
        m_codeGenerator.removeFile();
        exit(errorCode);
    }
}

string Compiler::buildFullFile() {
    return m_inputFileName.append(getFileExtension());
}

/*
void Compiler::setParseTree(ParseTree new_parseTree) {
    this->m_parseTree = new_parseTree;
}

ParseTree Compiler::getParseTree() const {
    return m_parseTree;
}
*/

void Compiler::setRedirectedFile(string redirected_file) {
    m_redirectedFile = redirected_file;
}

string Compiler::getRedirectedFile() const {
    return m_redirectedFile;
}

bool Compiler::wasInputRedirected() {
    return getRedirectedFile() == "redirect.txt";
}

void Compiler::setPreprocessorFile(const string FILE_NAME) {
    m_parser.setPreprocessorFile(FILE_NAME);
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
