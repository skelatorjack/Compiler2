/*
 //  Jack Pettit
 //  CS 4280
 //  Scope.cpp
 //  Compiler2
 //  November 15, 2017
 */


// NOTE: m_depthOfThisScope is never used
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
    incrementVarCount();
}

int Scope::checkIfVarIsInCurrentScope(const Token TOKEN, int &distance_from_top, bool &did_find_var) const {
    deque<Token> list_of_tokens = m_storedVarsInThisScope;
    reverse(list_of_tokens.begin(), list_of_tokens.end());
    
    if (getVarCount() == 0) {
        return -1;
    }
    
    for (int i = 0; i < list_of_tokens.size(); i++) {
        if (list_of_tokens.at(i).getTokenInstance() == TOKEN.getTokenInstance()) {
            did_find_var = true;
            break;
        }
        distance_from_top++;
    }
    
    if (did_find_var) {
        return distance_from_top;
    }
    else {
        return -1;
    }
}
void Scope::incrementVarCount() {
    m_varCount++;
}
