#Jack Pettit
#CS 4280
#October 19, 2017
#Makefile

GPP=g++
OBJ=-c
DBG=-g
OBJDBG=${OBJ} ${DBG}
EXEC=-o
STD=--std=c++11

comp: main.o CharReader.o Preprocessor.o Token.o Scanner.o ParseNode.o ParseTree.o Parser.o StaticSem.o Scope.o CodeGenerator.o Compiler.o
	${GPP} ${EXEC} comp ${DBG} ${STD} main.o CharReader.o Preprocessor.o Token.o Scanner.o ParseNode.o ParseTree.o Parser.o StaticSem.o Scope.o CodeGenerator.o Compiler.o

main.o: Includes.hpp Compiler.hpp main.cpp
	${GPP} ${OBJDBG} ${STD} Includes.hpp Compiler.hpp main.cpp

Compiler.o: Compiler.hpp Compiler.cpp
	${GPP} ${OBJDBG} ${STD} Compiler.hpp Compiler.cpp

CharReader.o: CharReader.hpp CharReader.cpp
	${GPP} ${OBJDBG} ${STD} CharReader.hpp CharReader.cpp

Preprocessor.o: Preprocessor.hpp Preprocessor.cpp
	${GPP} ${OBJDBG} ${STD} Preprocessor.hpp Preprocessor.cpp

Token.o: Token.hpp Token.cpp
	${GPP} ${OBJDBG} ${STD} Token.hpp Token.cpp

Scanner.o: Scanner.hpp Scanner.cpp
	${GPP} ${OBJDBG} ${STD} Scanner.hpp Scanner.cpp

ParseNode.o: ParseNode.hpp ParseNode.cpp
	${GPP} ${OBJDBG} ${STD} ParseNode.hpp ParseNode.cpp

ParseTree.o: ParseTree.hpp ParseTree.cpp
	${GPP} ${OBJDBG} ${STD} ParseTree.hpp ParseTree.cpp

Parser.o: Parser.hpp Parser.cpp
	${GPP} ${OBJDBG} ${STD} Parser.hpp Parser.cpp

StaticSem.o: StaticSem.hpp StaticSem.cpp
	${GPP} ${OBJDBG} ${STD} StaticSem.hpp StaticSem.cpp

Scope.o: Scope.hpp Scope.cpp
	${GPP} ${OBJDBG} ${STD} Scope.hpp Scope.cpp

CodeGenerator.o: CodeGenerator.hpp CodeGenerator.cpp
	${GPP} ${OBJDBG} ${STD} CodeGenerator.hpp CodeGenerator.cpp

clean:
	rm *.o *.gch comp 
