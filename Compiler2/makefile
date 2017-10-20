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

testScanner: main.o CharReader.o Preprocessor.o Token.o Scanner.o TestScanner.o Compiler.o
	${GPP} ${EXEC} testScanner ${DBG} ${STD} main.o CharReader.o Preprocessor.o Token.o Scanner.o TestScanner.o Compiler.o

main.o: Includes.hpp Compiler.hpp main.cpp
	${GPP} ${OBJDBG} ${STD} Includes.hpp Compiler.hpp main.cpp

Compiler.o: TestScanner.hpp Compiler.hpp Compiler.cpp
	${GPP} ${OBJDBG} ${STD} TestScanner.hpp Compiler.hpp Compiler.cpp

CharReader.o: CharReader.hpp CharReader.cpp
	${GPP} ${OBJDBG} ${STD} CharReader.hpp CharReader.cpp

Preprocessor.o: Preprocessor.hpp Preprocessor.cpp
	${GPP} ${OBJDBG} ${STD} Preprocessor.hpp Preprocessor.cpp

Token.o: Token.hpp Token.cpp
	${GPP} ${OBJDBG} ${STD} Token.hpp Token.cpp

Scanner.o: Scanner.hpp Scanner.cpp
	${GPP} ${OBJDBG} ${STD} Scanner.hpp Scanner.cpp

TestScanner.o: TestScanner.hpp TestScanner.cpp
	${GPP} ${OBJDBG} ${STD} TestScanner.hpp TestScanner.cpp

clean:
	rm *.o *.gch testScanner
