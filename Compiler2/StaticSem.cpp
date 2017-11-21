/*
//  Jack Pettit
//  CS 4280
//  Scope.hpp
//  Compiler2
//  November 15, 2017
*/

#include "StaticSem.hpp"

StaticSem::StaticSem(const int TOTAL_VARS, const int maxVars) : m_totalVars(TOTAL_VARS), m_maxVars(maxVars) {
    m_listOfScopes.push_back(Scope());
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
    
    if (!checkIfVarIsAlreadyDeclared(TOKEN)) {
        m_listOfScopes.back().addVar(TOKEN);
        incrementTotalVars();
    }
    else {
        reportError(TOKEN, 40);
    }
    
    if (getTotalVars() > getMaxVars()) {
        reportError(TOKEN, 60);
    }
}

int StaticSem::searchForToken(const Token TOKEN_TO_SEARCH) const {
    int distance_from_top = 0;
    int result = -1;
    
    // Reverse the list and start from the current scope
    deque<Scope> var_scopes = m_listOfScopes;
    reverse(var_scopes.begin(), var_scopes.end());
    bool did_find_var = false;
    
    // Search for the variable being used starting with the most recently added variable
    for (int i = 0; i < var_scopes.size(); i++) {
        if (var_scopes.at(i).getVarCount() != 0) {
            result = var_scopes.at(i).checkIfVarIsInCurrentScope(TOKEN_TO_SEARCH, distance_from_top, did_find_var);
            if (did_find_var) {
                break;
            }
        }
    }
    
    if (result == -1) {
        reportError(TOKEN_TO_SEARCH, 50);
    }
    
    return result;
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

void StaticSem::setMaxVars(const int MAX) {
    m_maxVars = MAX;
}

int StaticSem::getMaxVars() const {
    return m_maxVars;
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
            message << "Too many variables declared " << TOKEN.getTokenInstance() << " caused it." << endl;
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
