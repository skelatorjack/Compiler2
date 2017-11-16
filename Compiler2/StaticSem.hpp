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
    const int MAX_VARS;
    
    void findIncomingToken(const Token) const;
    void verifyIncomingToken(const Token) const;
    void reportError(const Token, const int) const;
    
public:
    StaticSem(int = 100);
    ~StaticSem();
    
    void addNewScope();
    void removeCurrentScope();
    void addVarToCurrentScope(const Token);
    
};

#endif
