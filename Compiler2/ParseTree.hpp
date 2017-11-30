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
#include "StaticSem.hpp"

class ParseTree {
private:
    shared_ptr<ParseNode> m_root;
    StaticSem m_staticSem;
    
    
    void printNode(shared_ptr<ParseNode>);
    void deinit();
    void deleteTree(shared_ptr<ParseNode>&);
    bool isSpecialTraversal(const shared_ptr<ParseNode>);
    void normalTraversal(const shared_ptr<ParseNode>);
    bool doesTokenOfNodeMatchGivenTokenId(const Token, const TokenId) const;
    
    int staticSem(const shared_ptr<ParseNode>);
    void codeGen(const shared_ptr<ParseNode>, const int);
    
public:
    ParseTree(shared_ptr<ParseNode> = nullptr, string = "", string = ".asm");
    ~ParseTree();
    void setRoot(shared_ptr<ParseNode> = nullptr);
    shared_ptr<ParseNode> getRoot() const;
    void traverseTree(const shared_ptr<ParseNode>);
    void runStaticSem();
    void removeOutputFile();
    bool doesNodeDeclareVars(const shared_ptr<ParseNode>) const;
    bool doesNodeHoldToken(const shared_ptr<ParseNode>) const;
    bool isNodeABlock(const shared_ptr<ParseNode>) const;
    bool doesNodeUseAVar(const shared_ptr<ParseNode>) const;
    bool doesNonterminalOfNodeMatchGivenNonterminal(const shared_ptr<ParseNode>, const string) const;
    bool isNodeNull(shared_ptr<ParseNode>) const;
};
#endif /* ParseTree_hpp */
