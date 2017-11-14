/*
 //  Jack Pettit
 //  CS 4280
 //  ParserTree.hpp
 //  P2
 //  10/31/17
*/

#ifndef PARSERTREE_HPP
#define PARSERTREE_HPP

#include "Includes.hpp"
#include "ParseNode.hpp"

class ParseTree {
private:
    shared_ptr<ParseNode> m_root;
    
    bool isNodeNull(shared_ptr<ParseNode>);
    void printNode(shared_ptr<ParseNode>);
    void deinit();
public:
    ParseTree(shared_ptr<ParseNode> = nullptr);
    ~ParseTree();
    void setRoot(shared_ptr<ParseNode> = nullptr);
    shared_ptr<ParseNode> getRoot() const;
    void traverseTree(shared_ptr<ParseNode>);
};
#endif /* ParseTree_hpp */
