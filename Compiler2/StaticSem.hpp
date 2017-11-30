/*
//  Jack Pettit
//  CS 4280
//  StaticSem.hpp
//  Compiler2
//  November 15, 2017
*/

#ifndef STATICSEM_HPP
#define STATICSEM_HPP

#include "Token.hpp"
#include "Scope.hpp"

class StaticSem {

private:
    deque<Scope> m_listOfScopes;
    int m_maxVars;
    int m_totalVars;
    
    void verifyIncomingToken(const Token) const;
    void reportError(const Token, const int) const;
    void printErrorInfo(const Token, const int) const;
    string createMessage(const Token, const int) const;
    bool checkIfVarIsAlreadyDeclared(const Token) const;
    
public:
    StaticSem(const int = 0, const int = 100);
    ~StaticSem();
    
    void setTotalVars(const int);
    int getTotalVars() const;
    void setMaxVars(const int);
    int getMaxVars() const;
    
    void incrementTotalVars();
    void addNewScope();
    void removeCurrentScope();
    void addVarToCurrentScope(const Token);
    int searchForToken(const Token) const;
    int getVarsInScope() const;
    
};

#endif
