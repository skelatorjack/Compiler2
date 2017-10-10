//
//  main.cpp
//  Compiler2
//
//  Created by Jack Pettit on 10/10/17.
//  Copyright © 2017 Jack Pettit. All rights reserved.
//

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
    string fileName = "redirect.txt";
    Compiler compiler(fileName);
    
    if (preprocessArgs(argc, argv)) {
        if (didReadInInput(argc, argv)) {
            fileName = stripRedirect(argv[1]);
        }
        else {
            fileName = buildFile(argv[1]);
        }
        compiler.setInputFileName(fileName);
    }
    
    compiler.runScanner();
    
    return 0;
}

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

static string buildFile(const char* inputName) {
    const string FILE_EXTENSION = ".fs17";
    stringstream fileName;
    
    fileName << inputName << FILE_EXTENSION;
    
    return fileName.str();
}

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

static string stripRedirect(const char* arg) {
    string input = arg;
    string stripedInput;
    
    stripedInput = input.substr(input.find(" ") + 1);
    
    cout << "Input stripped is " << stripedInput << endl;
    
    return stripedInput;
}
