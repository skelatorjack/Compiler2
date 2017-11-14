/*
 //  Jack Pettit
 //  CS 4280
 //  TestTree.hpp
 //  P2
 //  11/3/17
*/

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
