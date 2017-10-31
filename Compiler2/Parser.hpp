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
    
    void program();
    void block();
    void vars();
    void mvars();
    void expr();
    void M();
    void F();
    void T();
    void R();
    void stats();
    void mStat();
    void in();
    void out();
    void If();
    void loop();
    void assign();
    void RO();
    
public:
    Parser();
    ~Parser();
    void runParser();
    
    void setCurrentToken(Token);
    Token getCurrentToken() const;
    
};

#endif /* Parser_hpp */
