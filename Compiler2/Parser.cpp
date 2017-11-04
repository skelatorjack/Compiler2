//
//  Parser.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/31/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "Parser.hpp"

Parser::Parser(bool has_seen_comment, string file_name, bool was_file_redirected) : m_scanner(file_name, has_seen_comment, was_file_redirected), m_parseTree(nullptr) {
    
    m_scanner.preprocessInput();
    m_scanner.setupForBuildToken();
}

Parser::~Parser() {
    deinit();
}

void Parser::runParser() {
    getTokenFromScanner();
    program();
    
    return;
}

void Parser::setCurrentToken(const Token NEW_TOKEN) {
    m_currentToken = NEW_TOKEN;
}

Token Parser::getCurrentToken() const {
    return m_currentToken;
}

ParseTree Parser::getParseTree() const {
    return m_parseTree;
}

void Parser::setParseTree(const ParseTree NEW_PARSE_TREE) {
    m_parseTree = NEW_PARSE_TREE;
}

void Parser::setScannersFile(string scanner_file) {
    m_scanner.setFileForPreprocss(scanner_file);
}
// private methods

void Parser::getTokenFromScanner() {
    setCurrentToken(m_scanner.buildToken());
}

void Parser::deinit() {

}

void Parser::program() {
    vars();
    block();
    
    if (!doesCurrentTokenMatchExpected(EOF_tk)) {
        printError("Expected End of file", -1);
    }
    else {
        cout << "Parse OK.\n";
    }
    
    return;
}

void Parser::block() {
    if (doesCurrentTokenMatchExpected(Begin_tk)) {
        getTokenFromScanner();
        
        vars();
        stats();
        
        if (doesCurrentTokenMatchExpected(End_tk)) {
            getTokenFromScanner();
        }
        else {
            printError("Expected End", -5);
        }
    }
    else {
        printError("Expected Begin", -4);
    }
    return;
}

void Parser::vars() {
    if (doesCurrentTokenMatchExpected(Var_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpected(Ident_tk)) {
            getTokenFromScanner();
            mvars();
        }
        else {
            printError("Expected Identifier", -2);
        }
    }
    return;
}

void Parser::mvars() {
    if (doesCurrentTokenMatchExpected(Dot_tk)) {
        getTokenFromScanner();
    }
    else if (doesCurrentTokenMatchExpected(Comma_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpected(Ident_tk)) {
            getTokenFromScanner();
            mvars();
        }
        else {
            printError("Expected identifier", -3);
        }
    }
    else {
        printError("Expected . or , tokens", -3);
    }
    
    return;
}

void Parser::expr() {
    M();
    
    if (doesCurrentTokenMatchExpected(Plus_tk) || doesCurrentTokenMatchExpected(Minus_tk)) {
        getTokenFromScanner();
        expr();
    }
    
    return;
}

void Parser::M() {
    F();
    
    if (doesCurrentTokenMatchExpected(Percent_tk) || doesCurrentTokenMatchExpected(Star_tk)) {
        getTokenFromScanner();
        M();
    }
    
    return;
}

void Parser::F() {
    if (doesCurrentTokenMatchExpected(LParan_tk)) {
        getTokenFromScanner();
        F();
        
        if (doesCurrentTokenMatchExpected(RParan_tk)) {
            getTokenFromScanner();
        }
        else {
            printError("Missing )", -12);
        }
    }
    else {
        R();
    }
    
    return;
}

void Parser::T() {
    
}

void Parser::R() {
    if (doesCurrentTokenMatchExpected(LBracket_tk)) {
        getTokenFromScanner();
        expr();
        
        if (doesCurrentTokenMatchExpected(RBracket_tk)) {
            getTokenFromScanner();
        }
        else {
            printError("Missing ]", -13);
        }
    }
    else if (doesCurrentTokenMatchExpected(Ident_tk) || doesCurrentTokenMatchExpected(Num_tk)) {
        getTokenFromScanner();
    }
    
    return;
}

void Parser::stats() {
    stat();
    mStat();
    
    return;
}

void Parser::stat() {
    
    if (doesCurrentTokenMatchExpected(Begin_tk)) {
        block();
    }
    else if (doesCurrentTokenMatchExpected(Input_tk)) {
        in();
    }
    else if (doesCurrentTokenMatchExpected(Output_tk)) {
        out();
    }
    else if (doesCurrentTokenMatchExpected(Check_tk)) {
        If();
    }
    else if (doesCurrentTokenMatchExpected(Loop_tk)) {
        loop();
    }
    else if (doesCurrentTokenMatchExpected(Ident_tk)) {
        assign();
    }
    else {
        printError("Invalid statement", -6);
    }
    
    return;
}

void Parser::mStat() {
    if (isCurrentTokenAStat()) {
        stat();
        mStat();
    }
    return;
}

void Parser::in() {
    if (doesCurrentTokenMatchExpected(Input_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpected(Ident_tk)) {
            getTokenFromScanner();
            
            if (doesCurrentTokenMatchExpected(Semicolon_tk)) {
                getTokenFromScanner();
            }
            else {
                printError("Expected ;", -8);
            }
        }
        else {
            printError("Expected identifier", -7);
        }
    }
    return;
}

void Parser::out() {
    if (doesCurrentTokenMatchExpected(Output_tk)) {
        getTokenFromScanner();
        expr();
        
        if (doesCurrentTokenMatchExpected(Semicolon_tk)) {
            getTokenFromScanner();
        }
        else {
            printError("Expected ;", -9);
        }
    }
    else {
        printError("Expected Output", -10);
    }
}

void Parser::If() {
    if (doesCurrentTokenMatchExpected(Check_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpected(LBracket_tk)) {
            getTokenFromScanner();
            expr();
            RO();
            expr();
            
            if (doesCurrentTokenMatchExpected(RBracket_tk)) {
                getTokenFromScanner();
                stat();
            }
            else {
                printError("Expected ]", -14);
            }
        }
        else {
            printError("Expected [", -15);
        }
    }
    else {
        printError("Expected Check", -16);
    }
    return;
}

void Parser::loop() {
    if (doesCurrentTokenMatchExpected(Loop_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpected(LBracket_tk)) {
            getTokenFromScanner();
            expr();
            RO();
            expr();
            
            if (doesCurrentTokenMatchExpected(RBracket_tk)) {
                getTokenFromScanner();
                stat();
            }
            else {
                printError("Expected ]", -17);
            }
        }
        else {
            printError("Expected [", -18);
        }
    }
    else {
        printError("Expected Loop", -19);
    }
    return;
}

void Parser::assign() {
    if (doesCurrentTokenMatchExpected(Ident_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpected(Colon_tk)) {
            getTokenFromScanner();
            expr();
            
            if (doesCurrentTokenMatchExpected(Semicolon_tk)) {
                getTokenFromScanner();
            }
            else {
                printError("Expected ; after expression", -19);
            }
        }
        else {
            printError("Expected colon in assignment", -11);
        }
    }
    else {
        printError("Need identifer to assign to", -12);
    }
    
    return;
}

void Parser::RO() {
    const vector<TokenId> RELATIONAL_OPS = {LT_tk, LTE_tk, GT_tk, GTE_tk, DoubleEqual_tk, ExclEqual_tk};
    
    for (int i = 0; i < RELATIONAL_OPS.size(); i++) {
        if (doesCurrentTokenMatchExpected(RELATIONAL_OPS.at(i))) {
            getTokenFromScanner();
            return;
        }
    }
    printError("Not a valid relational operator", -19);
}

shared_ptr<ParseNode> Parser::createNewNode(const string NON_TERM) {
    shared_ptr<ParseNode> newNode(new ParseNode(nullptr, NON_TERM));
    newNode->setStoredToken(getCurrentToken());
    
    return newNode;
}

void Parser::printError(const string MESSAGE, const int ERROR_CODE) {
    cout << "Parser Error: invalid token at line number " << getCurrentToken().getTokenLineNumber() << " " << MESSAGE <<
        " got " << getCurrentToken().getTokenInstance() << endl;
    
    exit(ERROR_CODE);
}

bool Parser::doesCurrentTokenMatchExpected(const TokenId EXPECTED_TOKEN) const {
    return getCurrentToken().doesTokenMatchId(EXPECTED_TOKEN);
}

bool Parser::isCurrentTokenAStat() const {
    const vector<TokenId> STAT_IDS {Input_tk, Output_tk, Check_tk, Loop_tk, Ident_tk, Begin_tk};
    
    for (int i = 0; i < STAT_IDS.size(); i++) {
        if (doesCurrentTokenMatchExpected(STAT_IDS.at(i))) {
            return true;
        }
    }
    return false;
}
