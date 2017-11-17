/*
 //  Jack Pettit
 //  CS 4280
 //  Parser.hpp
 //  P2
 //  10/31/17
*/

#ifndef PARSER_HPP
#define PARSER_HPP

#include "ParseTree.hpp"
#include "Scanner.hpp"
#include "TestTree.hpp"

class Parser {
private:
    ParseTree m_parseTree;
    Token m_currentToken;
    Scanner m_scanner;
    TestTree m_treeTester;
    
    // grab a token from the Scanner
    void getTokenFromScanner();
    bool doesCurrentTokenMatchExpectedToken(const TokenId) const;
    void deinit();
    bool isCurrentTokenAStat() const;
    
    shared_ptr<ParseNode> program();
    shared_ptr<ParseNode> block();
    shared_ptr<ParseNode> vars();
    shared_ptr<ParseNode> mvars();
    shared_ptr<ParseNode> expr();
    shared_ptr<ParseNode> M();
    shared_ptr<ParseNode> F();
    shared_ptr<ParseNode> R();
    shared_ptr<ParseNode> stats();
    shared_ptr<ParseNode> stat();
    shared_ptr<ParseNode> mStat();
    shared_ptr<ParseNode> in();
    shared_ptr<ParseNode> out();
    shared_ptr<ParseNode> If();
    shared_ptr<ParseNode> loop();
    shared_ptr<ParseNode> assign();
    shared_ptr<ParseNode> RO();
    
    shared_ptr<ParseNode> createNewNode(const string);
    void printError(const string, const int);
    
public:
    Parser();
    ~Parser();
    void runParser();
    
    void setCurrentToken(const Token);
    Token getCurrentToken() const;
    
    void setScannersFile(string);
    
    void setPreprocessorFile(const string);
    void setUpPreprocessor(const string);
};

#endif /* Parser_hpp */
