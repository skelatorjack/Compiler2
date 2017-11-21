/*
//  Jack Pettit
//  CS 4280
//  Scope.hpp
//  Compiler2
//  November 15, 2017
*/

#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "Token.hpp"


class Scope {
    
private:
    deque<Token> m_storedVarsInThisScope;
    int m_varCount;
    int m_depthOfThisScope;
    
    void incrementVarCount();

public:
    Scope(int = 0, int = 0);
    ~Scope();
    
    void setVarCount(int);
    void setDepthOfThisScope(int);
    int getVarCount() const;
    int getDepthOfThisScope() const;
    deque<Token> getStoredVarInThisScope() const;
    
    void addVar(const Token);
    int checkIfVarIsInCurrentScope(const Token, int&, bool&) const;
};
#endif /* SCOPE_HPP */
