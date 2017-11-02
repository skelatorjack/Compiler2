//
//  ParseTree.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/31/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "ParseTree.hpp"

ParseTree::ParseTree(shared_ptr<ParseNode> new_root) : m_root(new_root) {
    
}

ParseTree::~ParseTree() {
    
}

void ParseTree::setRoot(shared_ptr<ParseNode> newRoot) {
    m_root = newRoot;
}

shared_ptr<ParseNode> ParseTree::getRoot() const {
    return m_root;
}

void ParseTree::traverseTree(shared_ptr<ParseNode> root) {
    
}


