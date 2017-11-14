/*
  Jack Pettit
  CS 4280
  Scanner.cpp
  Compiler2
  October 10, 2017
*/

#include "Scanner.hpp"

// public methods

Scanner::Scanner(string input_file_name, bool has_seen_comment, bool was_file_redirected) : m_preprocessor(has_seen_comment, input_file_name, was_file_redirected) {
    buildTable(m_stateTable);
    setUpColumns();
    setUpMaps();
}

Scanner::~Scanner() {
    deinit();
}

// Used to free up memory after Scanner is done building Tokens
void Scanner::deinit() {
    m_stateTable.clear();
    columns.clear();
    m_chars_From_File.clear();
    m_keyWords.clear();
    m_delims.clear();
    m_operators.clear();
    m_preprocessor.deinit();
}

void Scanner::setCharsFromFile(deque<char> chars) {
    this->m_chars_From_File = chars;
}

deque<char> Scanner::getCharsFromFile() {
    return this->m_chars_From_File;
}
void Scanner::setFileForPreprocss(string inputName) {
    m_preprocessor.setFileName(inputName);
}

// private methods

bool Scanner::dontAppendChar(const char cur_Char, const int CUR_STATE) {
    return isCharNewLine(cur_Char) ||
    isCharWhiteSpace(cur_Char) || isExitState(CUR_STATE);
}

bool Scanner::isCharEndOfFile(const char CUR_CHAR) {
    return CUR_CHAR == '\xff';
}

// Get the column number of the character taken from the deque
int Scanner::getColumnNumber(char currentChar) {
    int column_Number = -1;
    
    column_Number = getColumn(currentChar);
    
    if (column_Number == -1) {
        cout << "Invalid column number " << column_Number << endl;
        exit(-3);
    }
    
    return column_Number;
}

// Return the column number of the given character
int Scanner::getColumn(const char KEY) {
    int column = -1;
    map<char, int>::const_iterator it;
    
    if (columns.find(KEY) != columns.end()) {
        it = columns.find(KEY);
        return it->second;
    }
    
    return column;
}
// Get the next state in the FSA
int Scanner::getNextState(const int CUR_STATE, const char CUR_CHAR) {
    char mapToKey = '\0';
    
    // Letters are mapped to the key 'a'.
    if (isCharLetter(CUR_CHAR)) {
        mapToKey = 'a';
    }
    // Digits are mapped to the key 'b'.
    else if (isCharDigit(CUR_CHAR)) {
        mapToKey = 'b';
    }
    // Whitespaces are mapped to the key 'w'.
    else if (isCharWhiteSpace(CUR_CHAR)){
        mapToKey = 'w';
    }
    // End of file character is mapped to the key 'e'.
    else if (isCharEndOfFile(CUR_CHAR)) {
        mapToKey = 'e';
    }
    else {
        mapToKey = CUR_CHAR;
    }
    
    // Get the column number for that character
    const int NEW_COLUMN_NUM = getColumnNumber(mapToKey);
    
    // Throw an expection if invalid access in the vector
    try {
        return getState(CUR_STATE, NEW_COLUMN_NUM);
    }
    catch (const out_of_range &r) {
        cout << "Invalid table access at " << CUR_STATE << " , " << NEW_COLUMN_NUM << endl;
        exit(2);
    }
}

int Scanner::getState(const int ROW, const int COL) {
    return m_stateTable.at(ROW).at(COL);
}

void Scanner::popChar() {
    m_chars_From_File.pop_front();
}

bool Scanner::shouldPopChar(const char CUR_CHAR) {
    return isCharWhiteSpace(CUR_CHAR) || isCharNewLine(CUR_CHAR) || isCharEndOfFile(CUR_CHAR);
}

bool Scanner::isExitState(const int CUR_STATE) {
    return CUR_STATE >= 1000;
}

bool Scanner::isErrorState(const int CUR_STATE) {
    return CUR_STATE < 0;
}

// Run the preprocessor
void Scanner::preprocessInput() {
    m_preprocessor.preprocessInput();
}

void Scanner::reportError(const int ERROR_STATE, const Token INVALID_TOK) {
    cout << "Error invalid token " << INVALID_TOK.getTokenInstance() << " The state is " << ERROR_STATE << endl;
}

char Scanner::getChar() {
    return m_chars_From_File.front();
}

// Read from the file tabledata.txt to populate the FSA.
void Scanner::buildTable(vector < vector<int> > &table) {
    ifstream table_data;
    
    const int ROW_SIZE = 25;
    const int COL_SIZE = 27;
    
    vector<int> row;
    
    int data;
    
    table_data.open("tabledata.txt", fstream::in);
    
    for (int i = 0; i < COL_SIZE; i++) {
        for (int j = 0; j < ROW_SIZE; j++) {
            table_data >> data;
            row.push_back(data);
        }
        table.push_back(row);
        row.clear();
    }
    
    table_data.close();
}

// The driver function
Token Scanner::buildToken() {
    static Token current_Token;
    static int saved_LineNumber = 1;
    
    char current_Char = '\0';
    
    // Save the linenumber from the previous token
    current_Token.setUpNextToken(saved_LineNumber);
    
    int current_State = 0;
    int next_State = 0;
    
    while (!isCharsFromFileEmpty()) {
        current_Char = getChar();
        
        popChar();
        
        next_State = getNextState(current_State, current_Char);
        current_State = next_State;
        
        if (isCharNewLine(current_Char)) {
            saved_LineNumber++;
        }
        
        if (isErrorState(current_State)) {
            reportError(current_State, current_Token);
            exit(current_State);
        }
        else if (isExitState(current_State)) {
            checkTokenInstance(current_Token);
            
            if (!shouldPopChar(current_Char)) {
                putBackChar(current_Char);
            }
            if (current_Token.getTokenInstance().empty()) {
                current_Token.setUpNextToken(saved_LineNumber);
                current_State = next_State = 0;
                continue;
            }
            else {
               break;
            }
        }
        
        if (!dontAppendChar(current_Char, current_State)) {
            current_Token.appendChar(current_Char);
        }
        
        if (!shouldPopChar(current_Char) && isExitState(current_State)) {
            putBackChar(current_Char);
        }
    }
    return current_Token;
}

void Scanner::setupForBuildToken() {
    setCharsFromFile(m_preprocessor.getCharsFromFile());
}

bool Scanner::isCharsFromFileEmpty() {
    return m_chars_From_File.empty();
}
// Create keys and column numbers
void Scanner::setUpColumns() {
    vector<char> chars = getChars();
    
    for (int i = 0; i < chars.size(); i++) {
        insertIntoColumns(chars.at(i), i);
    }
}

// insert the pair into the column map
void Scanner::insertIntoColumns(const char KEY, const int VALUE) {
    columns.insert(pair<char, int>(KEY, VALUE));
}

// Create all the keys for columns map
vector<char> Scanner::getChars() {
    vector<char> chars;
    
    chars.push_back('a');
    chars.push_back('b');
    chars.push_back('<');
    chars.push_back('>');
    chars.push_back('=');
    chars.push_back('!');
    chars.push_back(':');
    chars.push_back('+');
    chars.push_back('-');
    chars.push_back('*');
    chars.push_back('/');
    chars.push_back('&');
    chars.push_back('%');
    chars.push_back('.');
    chars.push_back('(');
    chars.push_back(')');
    chars.push_back(',');
    chars.push_back('{');
    chars.push_back('}');
    chars.push_back(';');
    chars.push_back('[');
    chars.push_back(']');
    chars.push_back('e');
    chars.push_back('w');
    chars.push_back('\n');
    
    return chars;
}

void Scanner::putBackChar(const char CUR_CHAR) {
    m_chars_From_File.push_front(CUR_CHAR);
}

// Check if the token is only a number.
bool Scanner::checkDoesTokenMatchNumber(const Token TOKEN) {
    const string TOK_INST = TOKEN.getTokenInstance();
    
    // Need to refactor this
    for (int i = 0; i < TOK_INST.size(); i++) {
        if (!isdigit(TOK_INST.at(i))) {
            return false;
        }
    }
    return true;
}

bool Scanner::checkDoesTokenMatchKeyWord(const Token TOKEN) {
    return m_keyWords.find(TOKEN.getTokenInstance().c_str()) != m_keyWords.end();
}

bool Scanner::checkDoesTokenMatchOperator(const Token TOKEN) {
    return m_operators.find(TOKEN.getTokenInstance().c_str()) != m_operators.end();
}

bool Scanner::checkDoesTokenMatchDelimiter(const Token TOKEN) {
    return m_delims.find(TOKEN.getTokenInstance().c_str()) != m_delims.end();
}

// Assign an id to the current Token
void Scanner::checkTokenInstance(Token &token) {
    if (checkDoesTokenMatchNumber(token) && !token.getTokenInstance().empty()) {
        token.setTokenId(Num_tk);
    }
    else if (checkDoesTokenMatchKeyWord(token)) {
        token.setTokenId(getValueWithKey(token.getTokenInstance(), 'k'));
    }
    else if (checkDoesTokenMatchDelimiter(token)) {
        token.setTokenId(getValueWithKey(token.getTokenInstance(), 'd'));
    }
    else if (checkDoesTokenMatchOperator(token)) {
        token.setTokenId(getValueWithKey(token.getTokenInstance(), 'o'));
    }
    else if (token.getTokenInstance().empty()) {
        token.setTokenId(EOF_tk);
    }
    else {
        token.setTokenId(Ident_tk);
    }
}
// Initialize all maps
void Scanner::setUpMaps() {
    setUpKeyWords();
    setUpOps();
    setUpDelims();
}
// Initialize the m_keyWords map
void Scanner::setUpKeyWords() {
    insertValue("Begin", Begin_tk, 'k');
    insertValue("End", End_tk, 'k');
    insertValue("Check", Check_tk, 'k');
    insertValue("Loop", Loop_tk, 'k');
    insertValue("Void", Void_tk, 'k');
    insertValue("Var", Var_tk, 'k');
    insertValue("Return", Return_tk, 'k');
    insertValue("Input", Input_tk, 'k');
    insertValue("Output", Output_tk, 'k');
    insertValue("Program", Program_tk, 'k');
}
// Initialize the m_operators map
void Scanner::setUpOps() {
    insertValue("=", Equal_tk,'o');
    insertValue("<", LT_tk, 'o');
    insertValue("<=", LTE_tk, 'o');
    insertValue(">", GT_tk, 'o');
    insertValue(">=", GTE_tk, 'o');
    insertValue("!=", ExclEqual_tk, 'o');
    insertValue("==", DoubleEqual_tk, 'o');
    insertValue(":", Colon_tk, 'o');
    insertValue("+", Plus_tk, 'o');
    insertValue("-", Minus_tk, 'o');
    insertValue("*", Star_tk, 'o');
    insertValue("/", Slash_tk, 'o');
    insertValue("&", Amp_tk, 'o');
    insertValue(".", Dot_tk, 'o');
    insertValue(";", Semicolon_tk, 'o');
    insertValue("%", Percent_tk, 'o');
}

// Initialize the m_delims map
void Scanner::setUpDelims() {
    insertValue("(", LParan_tk, 'd');
    insertValue(")", RParan_tk, 'd');
    insertValue("[", LBracket_tk, 'd');
    insertValue("]", RBracket_tk, 'd');
    insertValue("{", LBrace_tk, 'd');
    insertValue("}", RBrace_tk, 'd');
    insertValue(",", Comma_tk, 'd');
}

// Insert the the tokenId and key into a map
void Scanner::insertValue(string key, TokenId id, const char WHICH_MAP) {
    switch (WHICH_MAP) {
        case 'k': m_keyWords.insert(pair<string, TokenId>(key, id));
            break;
        case 'd': m_delims.insert(pair<string, TokenId>(key, id));
            break;
        case 'o': m_operators.insert(pair<string, TokenId>(key, id));
            break;
    }
}

// Return the TokenId found
TokenId Scanner::getValueWithKey(string key, const char WHICH_MAP) {
    TokenId id = EOF_tk;
    map<string, TokenId>::const_iterator it;
    
    switch(WHICH_MAP) {
        case 'k': it = m_keyWords.find(key);
            break;
        case 'o': it = m_operators.find(key);
            break;
        case 'd': it = m_delims.find(key);
            break;
    }
    id = it->second;
    return id;
}
