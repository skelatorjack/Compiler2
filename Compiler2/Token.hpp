/*
//  Jack Pettit
//  CS 4280
//  Token.hpp
//  Compiler2
//  October 10, 2017
*/

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "Includes.hpp"

enum TokenId {
    Begin_tk, End_tk, Check_tk, Loop_tk, Void_tk, Var_tk, Return_tk,
    Input_tk, Output_tk, Program_tk,
    
    
    Equal_tk, LT_tk, LTE_tk, GT_tk, GTE_tk, ExclEqual_tk, DoubleEqual_tk,
    
    Colon_tk, Plus_tk, Minus_tk, Star_tk, Slash_tk, Amp_tk, Percent_tk, Dot_tk, LParan_tk, RParan_tk, Comma_tk, LBrace_tk,
    RBrace_tk, Semicolon_tk, LBracket_tk, RBracket_tk,
    
    Num_tk, Ident_tk, EOF_tk
};

class Token {
private:
    TokenId m_tokenId;
    string m_tokenInstance;
    int m_tokenLineNumber;
    
public:
    Token(TokenId=EOF_tk, string="", int=0);
    ~Token();
    
    void setTokenId(TokenId);
    void setTokenInstance(string);
    void setTokenLineNumber(int);
    TokenId getTokenId() const;
    string getTokenInstance() const;
    int getTokenLineNumber() const;
    
    void incrementLineNumber();
    void appendChar(char);
    void setUpNextToken(int);
    void toString() const;
    char getLastCharOfInstance();
    bool doesTokenMatchId(const TokenId) const;
};

#endif /* Token_hpp */
