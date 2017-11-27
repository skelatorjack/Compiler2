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
#include "CodeGenerator.hpp"

class ParseTree {
private:
    shared_ptr<ParseNode> m_root;
    StaticSem m_staticSem;
    CodeGenerator m_codegen;
    
    bool isNodeNull(shared_ptr<ParseNode>) const;
    void printNode(shared_ptr<ParseNode>);
    void deinit();
    void deleteTree(shared_ptr<ParseNode>&);
    bool doesNodeDeclareVars(const shared_ptr<ParseNode>) const;
    bool doesNodeHoldToken(const shared_ptr<ParseNode>) const;
    bool isNodeABlock(const shared_ptr<ParseNode>) const;
    bool doesNodeUseAVar(const shared_ptr<ParseNode>) const;
    bool doesNonterminalOfNodeMatchGivenNonterminal(const shared_ptr<ParseNode>, const string) const;
    
    bool doesTokenOfNodeMatchGivenTokenId(const Token, const TokenId) const;
    
public:
    ParseTree(shared_ptr<ParseNode> = nullptr, string = "", string = ".asm");
    ~ParseTree();
    void setRoot(shared_ptr<ParseNode> = nullptr);
    shared_ptr<ParseNode> getRoot() const;
    void traverseTree(shared_ptr<ParseNode>);
    void runStaticSem();
    void removeOutputFile();
};
#endif /* ParseTree_hpp */
