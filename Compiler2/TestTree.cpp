//
//  TestParser.cpp
//  Compiler2
//
//  Created by Jack Pettit on 11/3/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "TestTree.hpp"

TestTree::TestTree() {
    
}

TestTree::~TestTree() {
    
}

bool TestTree::isNodeNull(shared_ptr<ParseNode> cur_Node) {
    return cur_Node == nullptr;
}

void TestTree::printTree(ParseTree tree) {
    printNode(tree.getRoot(), 0);
}

void TestTree::printNode(shared_ptr<ParseNode> cur_Node, const int DEPTH) {
    if (isNodeNull(cur_Node)) {
        return;
    }
    
    printIndent(DEPTH);
    cur_Node->printParseNode(DEPTH);
    cout << endl;
    
    printNode(cur_Node->getChild(firstChild), DEPTH + 1);
    printNode(cur_Node->getChild(secondChild), DEPTH + 1);
    printNode(cur_Node->getChild(thirdChild), DEPTH + 1);
    printNode(cur_Node->getChild(fourthChild), DEPTH + 1);
}

void TestTree::printIndent(const int DEPTH) {
    for (int i = 0; i < DEPTH; i++) {
        cout << " " << " ";
    }
}


