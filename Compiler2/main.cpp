//  Jack Pettit
//  CS 4280
//  main.cpp
//  P1
//  10/10/17.


#include "Includes.hpp"
#include "Compiler.hpp"

static bool preprocessArgs(int, const char*[]);
static bool isFileValid(const string);
static bool validNumOfArgs(int);
static string buildFile(const char*);
static bool doesArgCountEqual(const int, const int);
static string stripRedirect(const char*);
static bool didReadInInput(int, const char*[]);

int main(int argc, const char * argv[]) {
    // Set the default file to redirect.txt
    string fileName = "redirect.txt";
    Compiler compiler(fileName);
    
    // Check for invalid input from command line
    if (preprocessArgs(argc, argv)) {
        // Checks in input was redirected
        if (didReadInInput(argc, argv)) {
            fileName = stripRedirect(argv[1]);
        }
        else {
            fileName = buildFile(argv[1]);
        }
        // Set Compiler's inputFile and Preprocessor's inputfile to fileName
        compiler.setInputFileName(fileName);
    }
    
    // run the scanner
    compiler.runScanner();
    
    return 0;
}

// Check for file redirection, invalid command line arguments, and checks if input exists
static bool preprocessArgs(int argCount, const char* args []) {
    string fileName = "";
    
    if (didReadInInput(argCount, args)) {
        return true;
    }
    else if (validNumOfArgs(argCount) && doesArgCountEqual(argCount, 2)) {
        fileName = buildFile(args[1]);
        
        if (!isFileValid(fileName)) {
            cout << "File is not valid.\n";
            exit(1);
        }
        return true;
    }
    else if (doesArgCountEqual(argCount, 1)) {
        return false;
    }
    else {
        cout << "Invalid number of args " << argCount << endl;
        exit(2);
    }
}

static bool isFileValid(const string ARG) {
    ifstream inputFile;
    bool FILE_VALID = false;
    
    inputFile.open(ARG.c_str(), fstream::in);
    
    if (inputFile.good()) {
        FILE_VALID = true;
    }
    inputFile.close();
    
    return FILE_VALID;
}

static bool validNumOfArgs(int argCount) {
    if (argCount > 2) {
        return false;
    }
    return true;
}

static bool doesArgCountEqual(const int VALUE, const int VALUE_TO_CHECK) {
    return VALUE == VALUE_TO_CHECK;
}

// Add the file extension to the input
static string buildFile(const char* inputName) {
    const string FILE_EXTENSION = ".fs17";
    stringstream fileName;
    
    fileName << inputName << FILE_EXTENSION;
    
    return fileName.str();
}

// Check if there were two arguments supplied to the program and if there was redirection
static bool didReadInInput(int argCount, const char* arg[]) {
    string input;
    
    if (argCount == 2) {
        input = arg[1];
        
        if (input.at(0) == '<') {
            return true;
        }
    }
    return false;
}

// Strip the input of '<'
static string stripRedirect(const char* arg) {
    string input = arg;
    string stripedInput;
    
    stripedInput = input.substr(input.find(" ") + 1);
    
    cout << "Input stripped is " << stripedInput << endl;
    
    return stripedInput;
}
