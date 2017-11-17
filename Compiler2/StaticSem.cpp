//
//  StaticSem.cpp
//  Compiler2
//
//  Created by Jack Pettit on 11/15/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "StaticSem.hpp"

StaticSem::StaticSem(const int TOTAL_VARS) : m_totalVars(TOTAL_VARS) {
    
}

StaticSem::~StaticSem() {
    m_listOfScopes.clear();
}

void StaticSem::addNewScope() {
    m_listOfScopes.push_back(Scope());
}

void StaticSem::removeCurrentScope() {
    m_listOfScopes.pop_back();
}

void StaticSem::addVarToCurrentScope(const Token TOKEN) {
    if (getTotalVars() > 100) {
        reportError(TOKEN, 60);
    }
    
    if (!checkIfVarIsAlreadyDeclared(TOKEN)) {
        m_listOfScopes.back().addVar(TOKEN);
    }
    else {
        reportError(TOKEN, 40);
    }
    
}

void StaticSem::searchForToken(const Token TOKEN_TO_SEARCH) const {
    int distance_from_top = 0;
    int result = 0;
    
    for (auto i = m_listOfScopes.end(); i != m_listOfScopes.begin(); i--) {
        result = i->checkIfVarIsInCurrentScope(TOKEN_TO_SEARCH, distance_from_top);
    }
    
    reportError(TOKEN_TO_SEARCH, 50);
}

void StaticSem::setTotalVars(const int NEW_VARCOUNT) {
    m_totalVars = NEW_VARCOUNT;
}

int StaticSem::getTotalVars() const {
    return m_totalVars;
}

void StaticSem::incrementTotalVars() {
    m_totalVars++;
}

/*
 Case 40 indicates that the identifier was already in current scope.
 Case 50 indicates that the identifier couldn't be found or is not in scope.
 Case 60 indicates that there are too many identifiers declared.
 */
void StaticSem::reportError(const Token TOKEN,  const int ERROR_CODE) const {
    switch(ERROR_CODE) {
        case 40:
            printErrorInfo(TOKEN, ERROR_CODE);
            break;
        case 50:
            printErrorInfo(TOKEN, ERROR_CODE);
            break;
        case 60:
            printErrorInfo(TOKEN, ERROR_CODE);
        default:
            break;
    }
    
    exit(ERROR_CODE);
}

void StaticSem::printErrorInfo(const Token TOKEN, const int ERROR_CODE) const {
    cout << "Error at line number " << TOKEN.getTokenLineNumber() << ": ";
    cout << createMessage(TOKEN, ERROR_CODE);
}

string StaticSem::createMessage(const Token TOKEN,  const int ERROR_CODE) const {
    stringstream message;
    
    switch (ERROR_CODE) {
        case 40:
            message << TOKEN.getTokenInstance() << " has already been declared\n";
            break;
        case 50:
            message << "Cannot find variable " << TOKEN.getTokenInstance() << endl;
            break;
        case 60:
            message << "Too many variables declared " << endl;
            break;
        default:
            break;
    }
    
    return message.str();
}

bool StaticSem::checkIfVarIsAlreadyDeclared(const Token TOKEN) const {
    deque<Token> vars_InScope = m_listOfScopes.back().getStoredVarInThisScope();
    
    return find(vars_InScope.begin(), vars_InScope.end(), TOKEN) != vars_InScope.end();
}
