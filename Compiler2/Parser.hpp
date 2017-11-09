//
//  Parser.hpp
//  Compiler2
//
//  Created by Jack Pettit on 10/31/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

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
    Parser(bool = false, string = "", bool = false);
    ~Parser();
    void runParser();
    
    void setCurrentToken(const Token);
    Token getCurrentToken() const;
    
    void setParseTree(const ParseTree);
    ParseTree getParseTree() const;
    void setScannersFile(string);
};

#endif /* Parser_hpp */
