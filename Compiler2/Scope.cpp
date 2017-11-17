//
//  Scope.cpp
//  Compiler2
//
//  Created by Jack Pettit on 11/15/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "Scope.hpp"

Scope::Scope(int var_count, int depth_of_scope) {
    setVarCount(var_count);
    setDepthOfThisScope(depth_of_scope);
}

Scope::~Scope() {
    m_storedVarsInThisScope.clear();
    setVarCount(-1);
    setDepthOfThisScope(-1);
}

void Scope::setVarCount(int new_varCount) {
    m_varCount = new_varCount;
}

int Scope::getVarCount() const {
    return m_varCount;
}

void Scope::setDepthOfThisScope(int new_scopeDepth) {
    m_depthOfThisScope = new_scopeDepth;
}

int Scope::getDepthOfThisScope() const {
    return m_depthOfThisScope;
}

deque<Token> Scope::getStoredVarInThisScope() const {
    return m_storedVarsInThisScope;
}

void Scope::addVar(const Token TOKEN) {
    m_storedVarsInThisScope.push_back(TOKEN);
}

int Scope::checkIfVarIsInCurrentScope(const Token TOKEN, int &distance_from_top) const {
    bool was_token_matched = false;
    
    for (auto i = m_storedVarsInThisScope.end(); i != m_storedVarsInThisScope.begin(); i--) {
        if (i->getTokenInstance() == TOKEN.getTokenInstance()) {
            was_token_matched = true;
            break;
        }
        distance_from_top++;
    }
    
    return distance_from_top;
}
void Scope::incrementVarCount() {
    m_varCount++;
}
