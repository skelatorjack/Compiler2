//
//  Scope.hpp
//  Compiler2
//
//  Created by Jack Pettit on 11/15/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef Scope_hpp
#define Scope_hpp

#include "StaticSem.hpp"


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
    
    void addVar(const Token) const;
    int checkIfVarIsInCurrentScope(const Token) const;
};
#endif /* Scope_hpp */
