//  Jack Pettit
//  CS 4280
//  main.cpp
//  P1
//  10/10/17.


#include "Includes.hpp"
#include "Compiler.hpp"

static void preprocessArgs(int, const char*[], string&, string&);
static bool isFileValid(const string);
static bool validNumOfArgs(int);
static string buildFile(const char*);
static bool doesArgCountEqual(const int, const int);
static bool wasFilePassedIn(int);

int main(int argc, const char * argv[]) {
    // Set the default file to redirect.txt
    string fileName = "";
    string redirectedFile = "";
    
    // Check for invalid input from command line
    preprocessArgs(argc, argv, fileName, redirectedFile);
    
    Compiler compiler(fileName, ".fs17", redirectedFile);
    compiler.runCompiler();
   
    
    return 0;
}


// Check for file redirection, invalid command line arguments, and checks if input exists
static void preprocessArgs(int argCount, const char* args [], string &fileName, string &redirectedFileName) {
    
    if (!validNumOfArgs(argCount)) {
        cout << "Invalid number of args " << argCount << ". Need zero or one.\n";
        exit(10);
    }
    
    if (wasFilePassedIn(argCount) && isFileValid(args[1])) {
        fileName = args[1];
    }
    else if (!wasFilePassedIn(argCount)){
        fileName = "out";
        redirectedFileName = "redirect.txt";
    }
    else {
        cout << "File is not valid. Exiting program\n";
    }
    
}

static bool isFileValid(const string ARG) {
    ifstream inputFile;
    bool FILE_VALID = false;
    string full_fileName = buildFile(ARG.c_str());
    
    inputFile.open(full_fileName.c_str(), fstream::in);
    
    if (inputFile.good()) {
        FILE_VALID = true;
    }
    inputFile.close();
    
    return FILE_VALID;
}

static bool validNumOfArgs(int argCount) {
    return argCount <= 2;
}

static bool doesArgCountEqual(const int VALUE, const int VALUE_TO_CHECK) {
    return VALUE == VALUE_TO_CHECK;
}

// Check if there were two arguments supplied to the program and if there was redirection
static bool wasFilePassedIn(int argCount) {
    return doesArgCountEqual(argCount, 2);
}

// Append the extension to the file passed from the command line
static string buildFile(const char* file_name) {
    stringstream file_with_extension;
    
    file_with_extension << file_name << ".fs17";
    
    return file_with_extension.str();
}
