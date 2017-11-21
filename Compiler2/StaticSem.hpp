//
//  StaticSem.hpp
//  Compiler2
//
//  Created by Jack Pettit on 11/15/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef STATICSEM_HPP
#define STATICSEM_HPP

#include "Token.hpp"
#include "Scope.hpp"

class StaticSem {

private:
    deque<Scope> m_listOfScopes;
    int m_totalVars;
    
    void verifyIncomingToken(const Token) const;
    void reportError(const Token, const int) const;
    void printErrorInfo(const Token, const int) const;
    string createMessage(const Token, const int) const;
    bool checkIfVarIsAlreadyDeclared(const Token) const;
    
public:
    StaticSem(const int = 0);
    ~StaticSem();
    
    void setTotalVars(const int);
    int getTotalVars() const;
    
    void incrementTotalVars();
    void addNewScope();
    void removeCurrentScope();
    void addVarToCurrentScope(const Token);
    void searchForToken(const Token) const;
    
};

#endif