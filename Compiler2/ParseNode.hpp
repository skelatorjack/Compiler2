/*
 //  Jack Pettit
 //  CS 4280
 //  ParseNode.hpp
 //  P2
 //  10/31/17
*/

#ifndef PARSENODE_HPP
#define PARSENODE_HPP

#include "Includes.hpp"
#include "Token.hpp"

enum subtree {
   firstChild, secondChild, thirdChild, fourthChild
};

class ParseNode {
private:
    Token m_storedToken;
    shared_ptr<ParseNode> m_firstChild;
    shared_ptr<ParseNode> m_secondChild;
    shared_ptr<ParseNode> m_thirdChild;
    shared_ptr<ParseNode> m_fourthChild;
    string m_nonTerminal; // Mark which nonterminal this node was created in

    bool m_isNodeBlock;
    
    void deinit();
    
public:
    ParseNode(shared_ptr<ParseNode> = nullptr, string = "", bool = false);
    ~ParseNode();
    void setStoredToken(const Token);
    Token getStoredToken() const;
    
    void setChild(shared_ptr<ParseNode>, subtree);
    shared_ptr<ParseNode> getChild(subtree) const;
    
    void setNonTerminal(string = "");
    string getNonTerminal() const;
    void printParseNode(const int) const;
    
    void setIsNodeBlock(const bool);
    bool getIsNodeBlock() const;
};

#endif /* ParseNode_hpp */
