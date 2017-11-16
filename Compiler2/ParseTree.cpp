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

void ParseTree::traverseTree(shared_ptr<ParseNode> root) {
    
}
        
bool ParseTree::isNodeNull(shared_ptr<ParseNode> current_node) const {
    return current_node == nullptr;
}


