//  Jack Pettit
//  CS 4280
//  main.cpp
//  P1
//  10/10/17.


#include "Includes.hpp"
#include "Compiler.hpp"

static void preprocessArgs(int, const char*[], bool&);
static bool isFileValid(const string);
static bool validNumOfArgs(int);
static string buildFile(const char*);
static bool doesArgCountEqual(const int, const int);
static bool didRedirectInput(int, const char*[]);

int main(int argc, const char * argv[]) {
    // Set the default file to redirect.txt
    string fileName = "";
    bool was_file_passed_in = false;
    
    // Check for invalid input from command line
    preprocessArgs(argc, argv, was_file_passed_in);
    
    if (was_file_passed_in) {
        fileName = argv[1];
    }
    else {
        fileName = "redirect.txt";
    }
    Compiler compiler(fileName);
    compiler.runCompiler();
    
    return 0;
}


// Check for file redirection, invalid command line arguments, and checks if input exists
static void preprocessArgs(int argCount, const char* args [], bool &was_file_passed_in) {
    string fileName = "";
    
    if (didRedirectInput(argCount, args)) {
        was_file_passed_in = true;
    }
    else if (validNumOfArgs(argCount) && doesArgCountEqual(argCount, 2)) {
        fileName = buildFile(args[1]);
        
        if (!isFileValid(fileName)) {
            cout << "File is not valid.\n";
            exit(1);
        }
        was_file_passed_in = true;
    }
    else if (doesArgCountEqual(argCount, 1)) {
        was_file_passed_in = false;
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

// Check if there were two arguments supplied to the program and if there was redirection
static bool didRedirectInput(int argCount, const char* arg[]) {
    string input;
    
    if (doesArgCountEqual(argCount, 2)) {
        input = arg[1];
        
        if (input.at(0) == '<') {
            return true;
        }
    }
    return false;
}

static string buildFile(const char* file_name) {
    stringstream file_with_extension;
    
    file_with_extension << file_name << ".fs17";
    
    return file_with_extension.str();
}
