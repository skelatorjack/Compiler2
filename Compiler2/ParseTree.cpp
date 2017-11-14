/*
 //  Jack Pettit
 //  CS 4280
 //  ParserTree.cpp
 //  P2
 //  10/31/17
*/

#include "ParseTree.hpp"

ParseTree::ParseTree(shared_ptr<ParseNode> new_root) : m_root(new_root) {
    
}

ParseTree::~ParseTree() {
    deinit();
}

void ParseTree::deinit() {
    //m_root.reset();
}

void ParseTree::setRoot(shared_ptr<ParseNode> newRoot) {
    m_root = newRoot;
}

shared_ptr<ParseNode> ParseTree::getRoot() const {
    return m_root;
}

void ParseTree::traverseTree(shared_ptr<ParseNode> root) {
    
}


