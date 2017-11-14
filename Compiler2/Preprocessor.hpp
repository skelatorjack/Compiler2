/*
//  Jack Pettit
//  CS 4280
//  Preprocessor.hpp
//  Compiler2
//  October 10, 2017
*/

#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP

#include "Includes.hpp"
#include "CharReader.hpp"

class Preprocessor : public CharReader {
private:
    ifstream m_input_File;
    bool m_isCommentSeen;
    string m_inputFileName;
    deque<char> m_chars_From_File;
    bool m_fileWasRedirected;
    map<char, bool> m_operators;
    
    void addCharToVector(vector<char>&, char);
    bool isCharComment(char);
    bool isCharInvalid(char);
    void printError(char);
    void openFile( );
    void closeFile();
    virtual char getChar();
    bool isCharOperator(char);
    void stripVector(vector<char>&);
    bool isInputRedirected();
    void redirectInput();
    void removeRedirectedFile();
    deque<char> convertVectorTodeque(vector<char>);
    void deinit();
    
public:
    Preprocessor(bool=false, string="", bool=false);
    ~Preprocessor();
    string getFileName();
    void setFileName(string);
    void preprocessInput();
    void setCommentSeen(bool);
    bool getCommentSeen();
    bool getFileWasRedirected();
    void setFileWasRedirected(bool);
    void addOperatorsToOperators();
    void setCharsFromFile(vector<char>);
    virtual deque<char> getCharsFromFile();
};

#endif /* Preprocessor_hpp */

