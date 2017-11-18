/*
 //  Jack Pettit
 //  CS 4280
 //  ParserTree.cpp
 //  P2
 //  10/31/17
*/

#include "ParseTree.hpp"

ParseTree::ParseTree(shared_ptr<ParseNode> new_root) : m_root(new_root), m_staticSem() {
    
}

ParseTree::~ParseTree() {
    deinit();
}

void ParseTree::deinit() {
    deleteTree(m_root);
}

void ParseTree::deleteTree(shared_ptr<ParseNode> &current_node) {
    if (isNodeNull(current_node)) {
        return;
    }
    
    shared_ptr<ParseNode> child1 = current_node->getChild(firstChild);
    shared_ptr<ParseNode> child2 = current_node->getChild(secondChild);
    shared_ptr<ParseNode> child3 = current_node->getChild(thirdChild);
    shared_ptr<ParseNode> child4 = current_node->getChild(fourthChild);
    
    deleteTree(child1);
    deleteTree(child2);
    deleteTree(child3);
    deleteTree(child4);
    
    current_node.reset();
    current_node = nullptr;
}

void ParseTree::setRoot(shared_ptr<ParseNode> newRoot) {
    m_root = newRoot;
}

shared_ptr<ParseNode> ParseTree::getRoot() const {
    return m_root;
}

void ParseTree::traverseTree(shared_ptr<ParseNode> current_node) {
    
    if (isNodeNull(current_node)) {
        return;
    }
    
    if (isNodeABlock(current_node)) {
        m_staticSem.addNewScope();
    }
    else if (doesNodeDeclareVars(current_node) && doesNodeHoldToken(current_node)) {
        m_staticSem.addVarToCurrentScope(current_node->getStoredToken());
    }
    else if (doesNodeUseAVar(current_node) && doesTokenOfNodeMatchGivenTokenId(current_node->getStoredToken(), Ident_tk) && doesNodeHoldToken(current_node)) {
        m_staticSem.searchForToken(current_node->getStoredToken());
    }
    
    traverseTree(current_node->getChild(firstChild));
    traverseTree(current_node->getChild(secondChild));
    traverseTree(current_node->getChild(thirdChild));
    traverseTree(current_node->getChild(fourthChild));
    
    if (isNodeABlock(current_node)) {
        m_staticSem.removeCurrentScope();
    }
}
        
bool ParseTree::isNodeNull(shared_ptr<ParseNode> current_node) const {
    return current_node == nullptr;
}

void ParseTree::runStaticSem() {
    traverseTree(getRoot());
}

bool ParseTree::doesNodeDeclareVars(const shared_ptr<ParseNode> CUR_NODE) const {
    return doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "vars") || doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "mvars");
}

bool ParseTree::doesNodeHoldToken(const shared_ptr<ParseNode> CUR_NODE) const {
    return !CUR_NODE->getStoredToken().doesTokenMatchId(EOF_tk);
}

bool ParseTree::doesNonterminalOfNodeMatchGivenNonterminal(const shared_ptr<ParseNode> CUR_NODE, const string NONTERMINAL) const {
    return CUR_NODE->getNonTerminal() == NONTERMINAL;
}

bool ParseTree::isNodeABlock(const shared_ptr<ParseNode> CUR_NODE) const {
    return doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "block");
}

bool ParseTree::doesNodeUseAVar(const shared_ptr<ParseNode> CUR_NODE) const {
    return doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "R") || doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "in");
}

bool ParseTree::doesTokenOfNodeMatchGivenTokenId(const Token TOKEN, const TokenId ID_TO_MATCH) const {
    return TOKEN.doesTokenMatchId(ID_TO_MATCH);
}
