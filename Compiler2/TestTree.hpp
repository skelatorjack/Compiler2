//
//  TestParser.hpp
//  Compiler2
//
//  Created by Jack Pettit on 11/3/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef TESTTREE_HPP
#define TESTTREE_HPP

#include "ParseTree.hpp"

class TestTree {
public:
    TestTree();
    ~TestTree();
    void printTree(ParseTree);
    void printNode(shared_ptr<ParseNode>, const int);
    bool isNodeNull(shared_ptr<ParseNode>);
    void printIndent(const int);
};

#endif /* TestParser_hpp */
