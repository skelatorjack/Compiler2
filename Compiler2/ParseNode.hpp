//
//  ParseNode.hpp
//  Compiler2
//
//  Created by Jack Pettit on 10/31/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef ParseNode_hpp
#define ParseNode_hpp

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
    string m_nonTerminal;                   // Mark which nonterminal this node was created in
    
    void deinit();
    
public:
    ParseNode(shared_ptr<ParseNode> = nullptr, string = "");
    ~ParseNode();
    void setStoredToken(const Token);
    Token getStoredToken() const;
    
    void setChild(shared_ptr<ParseNode>, subtree);
    shared_ptr<ParseNode> getChild(subtree) const;
    
    void setNonTerminal(string = "");
    string getNonTerminal() const;
    void printParseNode(const int) const;
};

#endif /* ParseNode_hpp */
