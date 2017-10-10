//
//  Compiler.hpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#ifndef COMPILER_HPP
#define COMPILER_HPP

#include "Includes.hpp"
#include "Scanner.hpp"

class Compiler {
private:
    string m_inputFileName;
    Scanner m_scanner;
    
public:
    Compiler(string="");
    ~Compiler();
    void setInputFileName(string);
    string getInputFileName();
    void runScanner();
};

#endif /* Compiler_hpp */
