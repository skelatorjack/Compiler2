//
//  ParseTree.hpp
//  Compiler2
//
//  Created by Jack Pettit on 10/31/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef ParseTree_hpp
#define ParseTree_hpp

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
