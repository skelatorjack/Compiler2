//
//  Token.hpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef Token_hpp
#define Token_hpp

#include "Includes.hpp"

enum TokenId {
    Begin_tk, End_tk, Check_tk, Loop_tk, Void_tk, Var_tk, Return_tk,
    Input_tk, Output_tk, Program_tk,
    
    
    Equal_tk, LT_tk, LTE_tk, GT_tk, GTE_tk, ExclEqual_tk, DoubleEqual_tk,
    
    Colon_tk, Plus_tk, Minus_tk, Star_tk, Slash_tk, Amp_tk, Dot_tk, LParan_tk, RParan_tk, Comma_tk, LBrace_tk,
    RBrace_tk, Semicolon_tk, LBracket_tk, RBracket_tk,
    
    Num_tk, Ident_tk, EOF_tk
};

class Token {
private:
    TokenId m_tokenId;
    string m_tokenInstance;
    int m_tokenLineNumber;
    map<string, TokenId> m_keyWords;
    map<string, TokenId> m_delims;
    map<string, TokenId> m_operators;
    
    bool checkDoesTokenMatchKeyWord();
    bool checkDoesTokenMatchOperator();
    bool checkDoesTokenMatchDelimiter();
    bool checkDoesTokenMatchNumber();
    bool checkDoesTokenMatchIdentifier();
    
    void setUpKeyWords();
    void setUpOps();
    void setUpDelims();
    void setUpMaps();
    
    void insertValue(string, TokenId, const char);
    TokenId getValueWithKey(string, const char);
    
public:
    Token(TokenId=EOF_tk, string="", int=1);
    ~Token();
    
    void setTokenId(TokenId);
    void setTokenInstance(string);
    void setTokenLineNumber(int);
    TokenId getTokenId() const;
    string getTokenInstance() const;
    int getTokenLineNumber() const;
    
    void incrementLineNumber();
    void appendChar(char);
    void checkTokenInstance();
    void setUpNextToken();
    void toString() const;
    char getLastCharOfInstance();
};

#endif /* Token_hpp */
