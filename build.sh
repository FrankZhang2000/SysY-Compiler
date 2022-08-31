#!/bin/zsh

cd src/
flex -o lexer.yy.cpp lexer.l
bison -d -o parser.tab.cpp parser.y
g++ -Wno-register -O2 -lm -std=c++17 lexer.yy.cpp others.cpp variable.cpp symtable.cpp parser.cpp initializer.cpp geneeyore.cpp gentigger.cpp genriscv.cpp parser.tab.cpp -o ../build/compiler -Idirs