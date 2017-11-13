/*
//  Jack Pettit
//  Preprocessor.cpp
//  Compiler2
//  October 10, 2017.
*/

#include "Preprocessor.hpp"

// public methods
Preprocessor::Preprocessor(bool hasSeenComment, string fileName, bool wasFileRedirected) {
    setCommentSeen(hasSeenComment);
    setFileName(fileName);
    setFileWasRedirected(wasFileRedirected);
}

Preprocessor::~Preprocessor() {
    
}

// Free up memory when the Preprocessor is done
void Preprocessor::deinit() {
    m_chars_From_File.clear();
    m_operators.clear();
    m_inputFileName.clear();
}

void Preprocessor::setFileName(string fileName) {
    m_inputFileName = fileName;
}

string Preprocessor::getFileName() {
    return m_inputFileName;
}

void Preprocessor::setCommentSeen(bool commentSeen) {
    m_isCommentSeen = commentSeen;
}

bool Preprocessor::getCommentSeen() {
    return m_isCommentSeen;
}

deque<char> Preprocessor::getCharsFromFile() {
    return m_chars_From_File;
}

void Preprocessor::setCharsFromFile(vector<char> chars) {
    m_chars_From_File = convertVectorTodeque(chars);
}

void Preprocessor::setFileWasRedirected(bool isRedirected) {
    m_fileWasRedirected = isRedirected;
}

bool Preprocessor::getFileWasRedirected() {
    return m_fileWasRedirected;
}
// private methods
// Used to add characters read from the file
void Preprocessor::addCharToVector(vector<char> &chars, char toAdd) {
    chars.push_back(toAdd);
}

bool Preprocessor::isCharComment(char currentChar) {
    return currentChar == '#';
}

bool Preprocessor::isCharInvalid(char current_Char) {
    if (isCharLetter(current_Char)) {
        return false;
    }
    else if (isCharDigit(current_Char)) {
        return false;
    }
    else if (isCharOperator(current_Char)) {
        return false;
    }
    else if (current_Char == '\xff') {
        return false;
    }
    else if (isCharComment(current_Char)) {
        return false;
    }
    else if (isCharNewLine(current_Char)) {
        return false;
    }
    else if (isCharWhiteSpace(current_Char)) {
        return false;
    }
    else {
        return true;
    }
}

bool Preprocessor::isCharOperator(char current_Char) {
    return m_operators.find(current_Char) != m_operators.end();
}

void Preprocessor::printError(char currentChar) {
    cout << "Scanner: Invalid character " << currentChar << endl;
}

void Preprocessor::openFile() {
    m_input_File.open(getFileName());
}

void Preprocessor::closeFile() {
    m_input_File.close();
}

char Preprocessor::getChar() {
    char cur_char;
    
    if (m_input_File.eof()) {
        cur_char = '\0';
    }
    else {
        cur_char = m_input_File.get();
    }
    
    return cur_char;
}

void Preprocessor::preprocessInput() {
    
    vector<char> chars_From_File;
    
    if (isInputRedirected()) {
        setFileWasRedirected(true);
        redirectInput();
    }
    addOperatorsToOperators();
    openFile();
    char current_Char = getChar();
    
    while (current_Char != '\0') {
        
        if (isCharInvalid(current_Char) && !getCommentSeen()) {
            printError(current_Char);
            exit(2);
        }
        else if (isCharComment(current_Char) && getCommentSeen()) {
            setCommentSeen(false);
        }
        else if (isCharComment(current_Char) && !getCommentSeen()) {
            setCommentSeen(true);
        }
        
        if ((!getCommentSeen() && !isCharComment(current_Char)) || isCharNewLine(current_Char)) {
            addCharToVector(chars_From_File, current_Char);
        }
        
        current_Char = getChar();
    }
    
    closeFile();
    removeRedirectedFile();
    stripVector(chars_From_File);
    setCharsFromFile(chars_From_File);
}

// Strip the vector of duplicate whitespaces
void Preprocessor::stripVector(vector<char> &chars) {
    int num_of_whitespaces = 0;
    
    for (int i = 0; i < m_chars_From_File.size(); i++) {
        if (num_of_whitespaces > 0 && isCharWhiteSpace(chars.at(i))) {
            chars.erase(chars.begin() + i);
        }
        
        if (isCharWhiteSpace(chars.at(i))) {
            num_of_whitespaces++;
        }
        else {
            num_of_whitespaces = 0;
        }
    }
}

bool Preprocessor::isInputRedirected() {
    return getFileName() == "redirect.txt";
}

// Read redirected input into a temporary file
void Preprocessor::redirectInput() {
    char file_Stuff = '\0';
    ofstream redirect_Output;
    
    redirect_Output.open(getFileName().c_str(), fstream::out);
    
    cout << "Enter input:\n";
    while (cin >> noskipws >> file_Stuff) {
        redirect_Output << file_Stuff;
    }
    redirect_Output.close();
}

// After reading all characters into a file remove the redirect.txt.
void Preprocessor::removeRedirectedFile() {
    if (getFileWasRedirected()) {
        remove(getFileName().c_str());
    }
}

// Initialize the m_operators map
void Preprocessor::addOperatorsToOperators() {
    m_operators.insert(pair<char, bool>('=', true));
    m_operators.insert(pair<char, bool>('<', true));
    m_operators.insert(pair<char, bool>('>', true));
    m_operators.insert(pair<char, bool>('!', true));
    m_operators.insert(pair<char, bool>(':', true));
    m_operators.insert(pair<char, bool>('+', true));
    m_operators.insert(pair<char, bool>('-', true));
    m_operators.insert(pair<char, bool>('*', true));
    m_operators.insert(pair<char, bool>('/', true));
    m_operators.insert(pair<char, bool>('&', true));
    m_operators.insert(pair<char, bool>('%', true));
    m_operators.insert(pair<char, bool>('.', true));
    m_operators.insert(pair<char, bool>('(', true));
    m_operators.insert(pair<char, bool>(')', true));
    m_operators.insert(pair<char, bool>('[', true));
    m_operators.insert(pair<char, bool>(']', true));
    m_operators.insert(pair<char, bool>('{', true));
    m_operators.insert(pair<char, bool>('}', true));
    m_operators.insert(pair<char, bool>(';', true));
    m_operators.insert(pair<char, bool>(',', true));
}

// Convert the vector into a deque
deque<char> Preprocessor::convertVectorTodeque(vector<char> chars) {
    deque<char> char_List;
    
    for (int i = 0; i < chars.size(); i++) {
        char_List.push_back(chars.at(i));
    }
    
    return char_List;
}
