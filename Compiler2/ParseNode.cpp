//
//  ParseNode.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/31/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "ParseNode.hpp"

ParseNode::ParseNode(shared_ptr<ParseNode> children, string non_terminal) : m_storedToken(), m_nonTerminal(non_terminal), m_firstChild(children), m_secondChild(children), m_thirdChild(children), m_fourthChild(children) {
    
}

ParseNode::~ParseNode() {
    deinit();
}

void ParseNode::deinit() {
    m_firstChild.reset();
    m_secondChild.reset();
    m_thirdChild.reset();
    m_fourthChild.reset();
    setNonTerminal();
}

void ParseNode::setChild(shared_ptr<ParseNode> node, subtree child) {
    switch(child) {
        case firstChild:
            m_firstChild = node;
            break;
        
        case secondChild:
            m_secondChild = node;
            break;
        
        case thirdChild:
            m_thirdChild = node;
            break;
            
        case fourthChild:
            m_fourthChild = node;
            break;
        
        default:
            break;
    }
}

shared_ptr<ParseNode>ParseNode::getChild(subtree child_to_return) const {
    shared_ptr<ParseNode> node_to_return;
    
    switch (child_to_return) {
        case firstChild:
            node_to_return = m_firstChild;
            break;
            
        case secondChild:
            node_to_return = m_secondChild;
            break;
            
        case thirdChild:
            node_to_return = m_thirdChild;
            break;
            
        case fourthChild:
            node_to_return = m_fourthChild;
            break;
            
        default:
            break;
    }
    
    return node_to_return;
}

void ParseNode::setNonTerminal(string non_nterminal) {
    m_nonTerminal = non_nterminal;
}

string ParseNode::getNonTerminal() const {
    return m_nonTerminal;
}

void ParseNode::setStoredToken(const Token TOKEN) {
    m_storedToken = TOKEN;
}

Token ParseNode::getStoredToken() const {
    return m_storedToken;
}

void ParseNode::printParseNode(const int INDENT) const {
    cout << setw(INDENT * 2) << setfill(' ') << getNonTerminal() << " ";
    
    if (getStoredToken().getTokenId() != EOF_tk) {
        getStoredToken().toString();
    }
    
    cout << endl;
}
