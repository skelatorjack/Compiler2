//
//  CodeGenerator.cpp
//  Compiler2
//
//  Created by Jack Pettit on 11/26/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

#include "CodeGenerator.hpp"

CodeGenerator::CodeGenerator(string basename, string extension, int ifSkipCount, int loopSkipCount, int loopJumpBackCount): m_list_of_vars(), m_output_file(), m_full_file_name(""), m_staticSemantics(), m_parseTree(), m_ifSkipLabelCount(ifSkipCount), m_LoopSkipLabelCount(loopSkipCount), m_LoopJumpBackLabelCount(loopJumpBackCount) {
    
    setFullFileName(buildFullFileName(basename, extension));
}

CodeGenerator::~CodeGenerator() {
    deinit();
}

void CodeGenerator::generateCode() {
    openFile();
    traverseTree(m_parseTree.getRoot());
    closeFile();
}

void CodeGenerator::codeGen(const shared_ptr<ParseNode> CUR_NODE) {
    bool continueTraversal = true;
    
    if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "expr")) {
        exprTraversal(CUR_NODE, continueTraversal);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "if")) {
        ifTraversal(CUR_NODE, continueTraversal);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "M")) {
        mTraversal(CUR_NODE, continueTraversal);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "Loop")) {
        loopTraversal(CUR_NODE, continueTraversal);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "block")) {
        m_staticSemantics.addNewScope();
    }
    else if (m_parseTree.doesNodeDeclareVars(CUR_NODE) && m_parseTree.doesNodeHoldToken(CUR_NODE)) {
        m_staticSemantics.addVarToCurrentScope(CUR_NODE->getStoredToken());
        generateVarsOrMvars(CUR_NODE);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "out")) {
        outTraversal(CUR_NODE, continueTraversal);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "assign")) {
        assignTraversal(CUR_NODE, continueTraversal);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "R")) {
        rTraversal(CUR_NODE, continueTraversal);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "F")) {
        fTraversal(CUR_NODE, continueTraversal);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "in")) {
        generateIn(CUR_NODE);
        continueTraversal = false;
    }

    if (continueTraversal) {
        traverseTree(CUR_NODE->getChild(firstChild));
        traverseTree(CUR_NODE->getChild(secondChild));
        traverseTree(CUR_NODE->getChild(thirdChild));
        traverseTree(CUR_NODE->getChild(fourthChild));
    }
    
    if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "block")) {
        const int TIMES_TO_POP = m_staticSemantics.getVarsInScope();
        m_staticSemantics.removeCurrentScope();
        popVars(TIMES_TO_POP);
    }
    else if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE, "program")) {
        const int TIMES_TO_POP = m_staticSemantics.getVarsInScope();
        popVars(TIMES_TO_POP);
        generateProgram(CUR_NODE);
    }
}
void CodeGenerator::traverseTree(const shared_ptr<ParseNode> CUR_NODE) {
    if (m_parseTree.isNodeNull(CUR_NODE)) {
        return;
    }
    codeGen(CUR_NODE);
}

int CodeGenerator::getCount(const LabelType WHICHCOUNT) const {
    int value = -1;
    
    switch(WHICHCOUNT) {
        case IfSkip:
            value = m_ifSkipLabelCount;
            break;
        
        case LoopSkip:
            value = m_LoopSkipLabelCount;
            break;
            
        case LoopJumpback:
            value = m_LoopJumpBackLabelCount;
            break;
            
        default:
            break;
    }
    
    return value;
}

void CodeGenerator::setCount(const int COUNT, const LabelType WHICH_COUNT) {
    switch(WHICH_COUNT) {
        case IfSkip:
            m_ifSkipLabelCount = COUNT;
            break;
            
        case LoopSkip:
            m_LoopSkipLabelCount = COUNT;
            break;
            
        case LoopJumpback:
            m_LoopJumpBackLabelCount = COUNT;
            break;
            
        default:
            break;
    }
}

void CodeGenerator::exprTraversal(const shared_ptr<ParseNode> CURRENT_NODE, bool &continueTraversal) {
    if (CURRENT_NODE->getStoredToken().doesTokenMatchId(Plus_tk) || CURRENT_NODE->getStoredToken().doesTokenMatchId(Minus_tk)) {
        generateExpr(CURRENT_NODE);
        continueTraversal = false;
    }
}
void CodeGenerator::popVars(const int NUM_OF_VARS) {
    for (int i = 0; i < NUM_OF_VARS; i++) {
        writePop();
    }
}

void CodeGenerator::setParseTree(const ParseTree newTree) {
    m_parseTree = newTree;
}

string CodeGenerator::getFullFileName() const {
    return m_full_file_name;
}

void CodeGenerator::setFullFileName(const string full_file_name) {
    m_full_file_name = full_file_name;
}

void CodeGenerator::openFile() {
    m_output_file.open(getFullFileName().c_str());
}

void CodeGenerator::closeFile() {
    if (m_output_file.is_open()) {
        m_output_file.close();
    }
}

void CodeGenerator::removeFile() {
    closeFile();
    remove(m_full_file_name.c_str());
}
// Private methods

string CodeGenerator::buildFullFileName(const string basename, const string extension) {
    stringstream str;
    
    str << basename << extension;
    
    return str.str();
}

void CodeGenerator::addVarToList(const string VAR_NAME) {
    m_list_of_vars.push_back(VAR_NAME);
}

void CodeGenerator::addVarToTempList(const string TEMP_VAR_NAME) {
    m_listOfTempVars.push_back(TEMP_VAR_NAME);
}

void CodeGenerator::deinit() {
    m_list_of_vars.clear();
    m_full_file_name.clear();
}

void CodeGenerator::generateProgram(const shared_ptr<ParseNode> CUR_NODE) {
    writeStop();
    writeVars();
}

void CodeGenerator::generateVarsOrMvars(const shared_ptr<ParseNode> CUR_NODE) {
    writePush();
    addVarToList(CUR_NODE->getStoredToken().getTokenInstance());
}

string CodeGenerator::createLabel(const LabelType TYPE_OF_LABEL) {
    string label_name;
    
    if (TYPE_OF_LABEL == IfSkip) {
        const int LABEL_COUNT = getCount(IfSkip);
        label_name = "IfSkip";
        label_name.append("_");
        label_name.append(to_string(LABEL_COUNT));
        setCount(m_ifSkipLabelCount + 1, IfSkip);
    }
    else if (TYPE_OF_LABEL == LoopSkip) {
        const int LABEL_COUNT = getCount(LoopSkip);
        label_name = "LoopSkip";
        label_name.append("_");
        label_name.append(to_string(LABEL_COUNT));
        setCount(m_LoopSkipLabelCount + 1, LoopSkip);
    }
    else if (TYPE_OF_LABEL == LoopJumpback) {
        const int LABEL_COUNT = getCount(LoopJumpback);
        label_name = "LoopJumpBack";
        label_name.append("_");
        label_name.append(to_string(LABEL_COUNT));
        setCount(m_LoopJumpBackLabelCount + 1, LoopJumpback);
    }
    
    return label_name;
}

string CodeGenerator::createTempVariable() {
    string temp_var = "temp";
    const string UNDER_SCORE = "_";
    const string SIZE = to_string(m_listOfTempVars.size());
    
    temp_var.append(UNDER_SCORE);
    temp_var.append(SIZE);
    
    addVarToList(temp_var);
    addVarToTempList(temp_var);
    
    return temp_var;
}

string CodeGenerator::getTempVariable(const int INDEX) {
    if (INDEX > m_listOfTempVars.size()) {
        return m_listOfTempVars.back();
    }
    else if (INDEX < 0) {
        return m_listOfTempVars.front();
    }
    
    return m_listOfTempVars.at(INDEX);
}

void CodeGenerator::generateBlock(const int NUM_VARS) {
    popVars(NUM_VARS);
}

void CodeGenerator::generateExpr(const shared_ptr<ParseNode> CUR_NODE) {
    const string EXPR_TEMP = createTempVariable();
    
    traverseTree(CUR_NODE->getChild(secondChild));
    writeStore(EXPR_TEMP);
    traverseTree(CUR_NODE->getChild(firstChild));
    
    if (CUR_NODE->getStoredToken().doesTokenMatchId(Plus_tk)) {
        writeAdd(EXPR_TEMP);
    }
    else {
        writeSub(EXPR_TEMP);
    }
}

void CodeGenerator::mTraversal(const shared_ptr<ParseNode> CUR_NODE, bool &continueTraversal) {
    if (m_parseTree.doesNodeHoldToken(CUR_NODE)) {
        generateM(CUR_NODE);
        continueTraversal = false;
    }
}

void CodeGenerator::generateM(const shared_ptr<ParseNode> CUR_NODE) {
    const string M_TEMP = createTempVariable();
    traverseTree(CUR_NODE->getChild(secondChild));
    writeStore(M_TEMP);
    traverseTree(CUR_NODE->getChild(firstChild));
    
    if (CUR_NODE->getStoredToken().doesTokenMatchId(Star_tk)) {
        writeMult(M_TEMP);
    }
    else {
        writeDiv(M_TEMP);
    }
}

void CodeGenerator::rTraversal(const shared_ptr<ParseNode> CUR_NODE, bool &continueTraversal) {
    if (m_parseTree.doesNodeHoldToken(CUR_NODE)) {
        generateR(CUR_NODE);
        continueTraversal = false;
    }
}

void CodeGenerator::generateR(const shared_ptr<ParseNode> CUR_NODE) {
    writeLoad(CUR_NODE->getStoredToken().getTokenInstance());
}

void CodeGenerator::outTraversal(const shared_ptr<ParseNode> CUR_NODE, bool &continueTraversal) {
    generateOut(CUR_NODE);
    continueTraversal = false;
}

void CodeGenerator::generateOut(const shared_ptr<ParseNode> CUR_NODE) {
    const string OUT_TEMP_VAR = createTempVariable();
    traverseTree(CUR_NODE->getChild(firstChild));
    writeStore(OUT_TEMP_VAR);
    writeWrite(OUT_TEMP_VAR);
}

void CodeGenerator::generateIn(const shared_ptr<ParseNode> CUR_NODE) {
    const int POS = m_staticSemantics.searchForToken(CUR_NODE->getStoredToken());
    
    writeRead(CUR_NODE->getStoredToken().getTokenInstance());
    writeLoad(CUR_NODE->getStoredToken().getTokenInstance());
    writeStackW(POS);
}

void CodeGenerator::ifTraversal(const shared_ptr<ParseNode> CUR_NODE, bool &continueTraversal) {
    generateIf(CUR_NODE);
    continueTraversal = false;
}

void CodeGenerator::generateIf(const shared_ptr<ParseNode> CUR_NODE) {
    const string THIRD_CHILD_TEMP = createTempVariable();
    const string FIRST_CHILD_TEMP = createTempVariable();
    const string IF_JUMP_LABEL = createLabel(IfSkip);
    
    traverseTree(CUR_NODE->getChild(thirdChild));
    writeStore(THIRD_CHILD_TEMP);
    traverseTree(CUR_NODE->getChild(firstChild));
    writeStore(FIRST_CHILD_TEMP);
    writeSub(THIRD_CHILD_TEMP);
    generateRO(CUR_NODE->getChild(secondChild), IF_JUMP_LABEL);
    traverseTree(CUR_NODE->getChild(fourthChild));
    writeLabel(IF_JUMP_LABEL);
    writeNoop();
}

void CodeGenerator::loopTraversal(const shared_ptr<ParseNode> CUR_NODE, bool &continueTraversal) {
    
}

void CodeGenerator::generateLoop(const shared_ptr<ParseNode> CUR_NODE) {
    
}

void CodeGenerator::assignTraversal(const shared_ptr<ParseNode> CUR_NODE, bool &continueTraversal) {
    traverseTree(CUR_NODE->getChild(firstChild));
    generateAssign(CUR_NODE);
    continueTraversal = false;
}
void CodeGenerator::generateAssign(const shared_ptr<ParseNode> CUR_NODE) {
    const int POS = m_staticSemantics.searchForToken(CUR_NODE->getStoredToken());
    
    writeStore(CUR_NODE->getStoredToken().getTokenInstance());
    writeStackW(POS);
}

void CodeGenerator::fTraversal(const shared_ptr<ParseNode> CUR_NODE, bool &continueTraversal) {
    if (m_parseTree.doesNonterminalOfNodeMatchGivenNonterminal(CUR_NODE->getChild(firstChild), "F")) {
        generateF(CUR_NODE);
        continueTraversal = false;
    }
}

void CodeGenerator::generateF(const shared_ptr<ParseNode> CUR_NODE) {
    traverseTree(CUR_NODE->getChild(firstChild));
    writeMult("-1");
}

void CodeGenerator::generateRO(const shared_ptr<ParseNode> CUR_NODE, const string LABEL) {
    const TokenId RELOP = CUR_NODE->getStoredToken().getTokenId();
    
    if (RELOP == LTE_tk) {
        writeBranch(LABEL, BRPOS);
    }
    else if (RELOP == LT_tk) {
        writeBranch(LABEL, BRZPOS);
    }
    else if (RELOP == GTE_tk) {
        writeBranch(LABEL, BRNEG);
    }
    else if (RELOP == GT_tk) {
        writeBranch(LABEL, BRZNEG);
    }
    else if (RELOP == DoubleEqual_tk) {
        writeBranch(LABEL, BRPOS);
        writeBranch(LABEL, BRNEG);
    }
    else if (RELOP == ExclEqual_tk) {
        writeBranch(LABEL, BRZERO);
    }
}

void CodeGenerator::writeStop() {
    m_output_file << "STOP";
    writeNewLine();
}

void CodeGenerator::writeNewLine() {
    m_output_file << endl;
}

void CodeGenerator::writeVars() {
    for (int i = 0; i < m_list_of_vars.size(); i++) {
        m_output_file << m_list_of_vars.at(i) << " " << "0";
        writeNewLine();
    }
}

void CodeGenerator::writePush() {
    m_output_file << "PUSH";
    writeNewLine();
}

void CodeGenerator::writePop() {
    m_output_file << "POP";
    writeNewLine();
}

void CodeGenerator::writeLoad(const string CUR_INSTANCE) {
    m_output_file << "LOAD " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeWrite(const string CUR_INSTANCE) {
    m_output_file << "WRITE " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeAdd(const string CUR_INSTANCE) {
    m_output_file << "ADD " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeStore(const string CUR_INSTANCE) {
    m_output_file << "STORE " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeSub(const string CUR_INSTANCE) {
    m_output_file << "SUB " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeDiv(const string CUR_INSTANCE) {
    m_output_file << "DIV " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeMult(const string CUR_INSTANCE) {
    m_output_file << "MULT " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeBranch(const string CUR_INSTANCE, const BranchType COND) {
    switch(COND) {
        case BRZERO:
            m_output_file << "BRZERO ";
            break;
            
        case BRNEG:
            m_output_file << "BRNEG ";
            break;
        
        case BRZPOS:
            m_output_file << "BRZPOS ";
            break;
            
        case BRPOS:
            m_output_file << "BRPOS ";
            break;
            
        case BRZNEG:
            m_output_file << "BRZNEG ";
            break;
            
        case BR:
            m_output_file << "BR ";
            break;
            
        default:
            break;
    }
    
    m_output_file << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeStackR(const int POS) {
    m_output_file << "STACKR " << POS;
    writeNewLine();
}

void CodeGenerator::writeStackW(const int POS) {
    m_output_file << "STACKW " << POS;
    writeNewLine();
}

void CodeGenerator::writeRead(const string CUR_INSTANCE) {
    m_output_file << "READ " << CUR_INSTANCE;
    writeNewLine();
}

void CodeGenerator::writeCopy(const string COPY_DEST, const string COPY_SRC) {
    m_output_file << "COPY " << COPY_DEST << " " << COPY_SRC;
    writeNewLine();
}

void CodeGenerator::writeLabel(const string LABEL) {
    m_output_file << LABEL << ": ";
}

void CodeGenerator::writeNoop() {
    m_output_file << "NOOP";
    writeNewLine();
}

bool CodeGenerator::isVarsOrMvars(const shared_ptr<ParseNode> CUR_NODE) {
    const string NONTERMINAL = CUR_NODE->getNonTerminal();
    
    return NONTERMINAL == "vars" || NONTERMINAL == "mvars";
}
