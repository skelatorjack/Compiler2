//
//  Parser.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/31/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "Parser.hpp"

Parser::Parser(bool has_seen_comment, string file_name, bool was_file_redirected) : m_scanner(file_name, has_seen_comment, was_file_redirected), m_parseTree(nullptr), m_treeTester() {
    
    m_scanner.preprocessInput();
    m_scanner.setupForBuildToken();
}

Parser::~Parser() {
    deinit();
}

void Parser::runParser() {
    getTokenFromScanner();
    getParseTree().setRoot(program());
    m_treeTester.printTree(getParseTree());
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

shared_ptr<ParseNode> Parser::program() {
    const string PROG_NONTERMINAL = "program";
    shared_ptr<ParseNode> prog_node = createNewNode(PROG_NONTERMINAL);
    
    prog_node->setChild(vars(), firstChild);
    prog_node->setChild(block(), secondChild);
    
    if (!doesCurrentTokenMatchExpectedToken(EOF_tk)) {
        printError("Expected End of file", -1);
    }
    else {
        cout << "Parse OK.\n";
    }
    
    return prog_node;
}

shared_ptr<ParseNode> Parser::block() {
    const string BLOCK_NONTERMINAL = "block";
    shared_ptr<ParseNode> block_node = createNewNode(BLOCK_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(Begin_tk)) {
        getTokenFromScanner();
        
        block_node->setChild(vars(), firstChild);
        block_node->setChild(stats(), secondChild);
        
        if (doesCurrentTokenMatchExpectedToken(End_tk)) {
            getTokenFromScanner();
        }
        else {
            printError("Expected End", -5);
        }
    }
    else {
        printError("Expected Begin", -4);
    }
    return block_node;
}

shared_ptr<ParseNode> Parser::vars() {
    const string VARS_NONTERMINAL = "vars";
    shared_ptr<ParseNode> vars_node = createNewNode(VARS_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(Var_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpectedToken(Ident_tk)) {
            vars_node->setStoredToken(getCurrentToken());
            getTokenFromScanner();
            vars_node->setChild(mvars(), firstChild);
        }
        else {
            printError("Expected Identifier", -2);
        }
    }
    return vars_node;
}

shared_ptr<ParseNode> Parser::mvars() {
    const string MVARS_NONTERMINAL = "mvars";
    shared_ptr<ParseNode> mvars_node = createNewNode(MVARS_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(Dot_tk)) {
        getTokenFromScanner();
    }
    else if (doesCurrentTokenMatchExpectedToken(Comma_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpectedToken(Ident_tk)) {
            mvars_node->setStoredToken(getCurrentToken());
            getTokenFromScanner();
            mvars_node->setChild(mvars(), firstChild);
        }
        else {
            printError("Expected identifier", -3);
        }
    }
    else {
        printError("Expected . or , tokens", -3);
    }
    
    return mvars_node;
}

shared_ptr<ParseNode> Parser::expr() {
    const string EXPR_NONTERMINAL = "expr";
    shared_ptr<ParseNode> expr_node = createNewNode(EXPR_NONTERMINAL);
    
    expr_node->setChild(M(), firstChild);
    
    if (doesCurrentTokenMatchExpectedToken(Plus_tk) || doesCurrentTokenMatchExpectedToken(Minus_tk)) {
        expr_node->setStoredToken(getCurrentToken());
        
        getTokenFromScanner();
        
        expr_node->setChild(expr(), secondChild);
    }
    
    return expr_node;
}

shared_ptr<ParseNode> Parser::M() {
    const string M_NONTERMINAL = "M";
    shared_ptr<ParseNode> m_node = createNewNode(M_NONTERMINAL);
    
    m_node->setChild(F(), firstChild);
    
    if (doesCurrentTokenMatchExpectedToken(Percent_tk) || doesCurrentTokenMatchExpectedToken(Star_tk)) {
        
        m_node->setStoredToken(getCurrentToken());
        
        getTokenFromScanner();
        
        m_node->setChild(M(), secondChild);
    }
    
    return m_node;
}

shared_ptr<ParseNode> Parser::F() {
    const string F_NONTERMINAL = "F";
    shared_ptr<ParseNode> f_node = createNewNode(F_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(LParan_tk)) {
        getTokenFromScanner();
        f_node->setChild(F(), firstChild);
        
        if (doesCurrentTokenMatchExpectedToken(RParan_tk)) {
            getTokenFromScanner();
        }
        else {
            printError("Missing )", -12);
        }
    }
    else {
        f_node->setChild(R(), firstChild);
    }
    
    return f_node;
}

shared_ptr<ParseNode> Parser::R() {
    const string R_NONTERMINAL = "R";
    shared_ptr<ParseNode> r_node = createNewNode(R_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(LBracket_tk)) {
        getTokenFromScanner();
        r_node->setChild(expr(), firstChild);
        
        if (doesCurrentTokenMatchExpectedToken(RBracket_tk)) {
            getTokenFromScanner();
        }
        else {
            printError("Missing ]", -13);
        }
    }
    else if (doesCurrentTokenMatchExpectedToken(Ident_tk) || doesCurrentTokenMatchExpectedToken(Num_tk)) {
        r_node->setStoredToken(getCurrentToken());
        getTokenFromScanner();
    }
    
    return r_node;
}

shared_ptr<ParseNode> Parser::stats() {
    const string STATS_NONTERMINAL = "stats";
    shared_ptr<ParseNode> stats_node = createNewNode(STATS_NONTERMINAL);
    
    stats_node->setChild(stat(), firstChild);
    stats_node->setChild(mStat(), secondChild);
    
    return stats_node;
}

shared_ptr<ParseNode> Parser::stat() {
    const string STAT_NONTERMINAL = "stat";
    shared_ptr<ParseNode> stat_node = createNewNode(STAT_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(Begin_tk)) {
        stat_node->setChild(block(), firstChild);
    }
    else if (doesCurrentTokenMatchExpectedToken(Input_tk)) {
        stat_node->setChild(in(), firstChild);
    }
    else if (doesCurrentTokenMatchExpectedToken(Output_tk)) {
        stat_node->setChild(out(), firstChild);
    }
    else if (doesCurrentTokenMatchExpectedToken(Check_tk)) {
        stat_node->setChild(If(), firstChild);
    }
    else if (doesCurrentTokenMatchExpectedToken(Loop_tk)) {
        stat_node->setChild(loop(), firstChild);
    }
    else if (doesCurrentTokenMatchExpectedToken(Ident_tk)) {
        stat_node->setChild(assign(), firstChild);
    }
    else {
        printError("Invalid statement", -6);
    }
    
    return stat_node;
}

shared_ptr<ParseNode> Parser::mStat() {
    const string MSTAT_NONTERMINAL = "mStat";
    shared_ptr<ParseNode> mStat_Node(nullptr);
    
    if (isCurrentTokenAStat()) {
        mStat_Node = createNewNode(MSTAT_NONTERMINAL);
        
        mStat_Node->setChild(stat(), firstChild);
        mStat_Node->setChild(mStat(), secondChild);
    }
    return mStat_Node;
}

shared_ptr<ParseNode> Parser::in() {
    const string IN_NONTERMINAL = "in";
    shared_ptr<ParseNode> in_node = createNewNode(IN_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(Input_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpectedToken(Ident_tk)) {
            in_node->setStoredToken(getCurrentToken());
            getTokenFromScanner();
            
            if (doesCurrentTokenMatchExpectedToken(Semicolon_tk)) {
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
    return in_node;
}

shared_ptr<ParseNode> Parser::out() {
    const string OUT_NONTERMINAL = "out";
    shared_ptr<ParseNode> out_node = createNewNode(OUT_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(Output_tk)) {
        getTokenFromScanner();
        out_node->setChild(expr(), firstChild);
        
        if (doesCurrentTokenMatchExpectedToken(Semicolon_tk)) {
            getTokenFromScanner();
        }
        else {
            printError("Expected ;", -9);
        }
    }
    else {
        printError("Expected Output", -10);
    }
    
    return out_node;
}

shared_ptr<ParseNode> Parser::If() {
    const string IF_NODE = "if";
    shared_ptr<ParseNode> if_node = createNewNode(IF_NODE);
    
    if (doesCurrentTokenMatchExpectedToken(Check_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpectedToken(LBracket_tk)) {
            getTokenFromScanner();
            if_node->setChild(expr(), firstChild);
            if_node->setChild(RO(), secondChild);
            if_node->setChild(expr(), thirdChild);
            
            if (doesCurrentTokenMatchExpectedToken(RBracket_tk)) {
                getTokenFromScanner();
                if_node->setChild(stat(), fourthChild);
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
    
    return if_node;
}

shared_ptr<ParseNode> Parser::loop() {
    const string LOOP_NONTERMINAL = "loop";
    shared_ptr<ParseNode> loop_node = createNewNode(LOOP_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(Loop_tk)) {
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpectedToken(LBracket_tk)) {
            getTokenFromScanner();
            loop_node->setChild(expr(), firstChild);
            loop_node->setChild(RO(), secondChild);
            loop_node->setChild(expr(), thirdChild);
            
            if (doesCurrentTokenMatchExpectedToken(RBracket_tk)) {
                getTokenFromScanner();
                loop_node->setChild(stat(), fourthChild);
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
    
    return loop_node;
}

shared_ptr<ParseNode> Parser::assign() {
    const string ASSIGN_NONTERMINAL = "assign";
    shared_ptr<ParseNode> assign_node = createNewNode(ASSIGN_NONTERMINAL);
    
    if (doesCurrentTokenMatchExpectedToken(Ident_tk)) {
        assign_node->setStoredToken(getCurrentToken());
        getTokenFromScanner();
        
        if (doesCurrentTokenMatchExpectedToken(Colon_tk)) {
            getTokenFromScanner();
            expr();
            
            if (doesCurrentTokenMatchExpectedToken(Semicolon_tk)) {
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
    
    return assign_node;
}

shared_ptr<ParseNode> Parser::RO() {
    const vector<TokenId> RELATIONAL_OPS = {LT_tk, LTE_tk, GT_tk, GTE_tk, DoubleEqual_tk, ExclEqual_tk};
    
    const string RO_NONTERMINAL = "RO";
    shared_ptr<ParseNode> ro_node = createNewNode(RO_NONTERMINAL);
    
    for (int i = 0; i < RELATIONAL_OPS.size(); i++) {
        if (doesCurrentTokenMatchExpectedToken(RELATIONAL_OPS.at(i))) {
            ro_node->setStoredToken(getCurrentToken());
            getTokenFromScanner();
            return ro_node;
        }
    }
    printError("Not a valid relational operator", -19);
    return nullptr;
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

bool Parser::doesCurrentTokenMatchExpectedToken(const TokenId EXPECTED_TOKEN) const {
    return getCurrentToken().doesTokenMatchId(EXPECTED_TOKEN);
}

bool Parser::isCurrentTokenAStat() const {
    const vector<TokenId> STAT_IDS {Input_tk, Output_tk, Check_tk, Loop_tk, Ident_tk, Begin_tk};
    
    for (int i = 0; i < STAT_IDS.size(); i++) {
        if (doesCurrentTokenMatchExpectedToken(STAT_IDS.at(i))) {
            return true;
        }
    }
    return false;
}
