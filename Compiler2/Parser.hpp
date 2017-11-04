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

class Parser {
private:
    ParseTree m_parseTree;
    Token m_currentToken;
    Scanner m_scanner;
    
    // grab a token from the Scanner
    void getTokenFromScanner();
    bool doesCurrentTokenMatchExpectedToken(const TokenId) const;
    void deinit();
    bool isCurrentTokenAStat() const;
    
    void program();
    void block();
    void vars();
    void mvars();
    void expr();
    void M();
    void F();
    void R();
    void stats();
    void stat();
    void mStat();
    void in();
    void out();
    void If();
    void loop();
    void assign();
    void RO();
    
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
