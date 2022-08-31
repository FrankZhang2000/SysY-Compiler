CCFLAGS=-DDEBUG -Wall -g
CXXFLAGS=-Wno-register -O2 -std=c++17 -Idirs

TOP_DIR := $(shell pwd)
BUILD_DIR ?= $(TOP_DIR)/build
SRC_DIR := $(TOP_DIR)/src

${BUILD_DIR}/compiler: ${BUILD_DIR}/lexer.yy.o ${BUILD_DIR}/others.o ${BUILD_DIR}/variable.o \
	${BUILD_DIR}/symtable.o ${BUILD_DIR}/parser.o ${BUILD_DIR}/initializer.o ${BUILD_DIR}/geneeyore.o ${BUILD_DIR}/gentigger.o ${BUILD_DIR}/genriscv.o ${BUILD_DIR}/parser.tab.o
	g++ ${CXXFLAGS} -lm ${BUILD_DIR}/lexer.yy.o ${BUILD_DIR}/others.o ${BUILD_DIR}/variable.o \
	${BUILD_DIR}/symtable.o ${BUILD_DIR}/parser.o ${BUILD_DIR}/initializer.o ${BUILD_DIR}/geneeyore.o ${BUILD_DIR}/gentigger.o ${BUILD_DIR}/genriscv.o ${BUILD_DIR}/parser.tab.o -o ${BUILD_DIR}/compiler

${BUILD_DIR}/lexer.yy.o: ${SRC_DIR}/lexer.yy.cpp
	g++ ${CXXFLAGS} -c ${SRC_DIR}/lexer.yy.cpp -o ${BUILD_DIR}/lexer.yy.o 

${SRC_DIR}/parser.tab.cpp: ${SRC_DIR}/lexer.l
	flex -o ${SRC_DIR}/parser.tab.cpp ${SRC_DIR}/lexer.l

${SRC_DIR}/parser.tab.hpp: ${SRC_DIR}/parser.y ${SRC_DIR}/parser.tab.cpp ${SRC_DIR}/parser.h ${SRC_DIR}/variable.h \
	${SRC_DIR}/symtable.h ${SRC_DIR}/initializer.h ${SRC_DIR}/others.h
	bison -d -o ${SRC_DIR}/parser.tab.cpp ${SRC_DIR}/parser.y

${BUILD_DIR}/others.o: ${SRC_DIR}/others.cpp ${SRC_DIR}/others.h
	g++ ${CXXFLAGS} -c ${SRC_DIR}/others.cpp -o ${BUILD_DIR}/others.o

${BUILD_DIR}/variable.o: ${SRC_DIR}/variable.cpp ${SRC_DIR}/variable.h
	g++ ${CXXFLAGS} -c ${SRC_DIR}/variable.cpp -o ${BUILD_DIR}/variable.o

${BUILD_DIR}/symtable.o: ${SRC_DIR}/symtable.cpp ${SRC_DIR}/variable.h
	g++ ${CXXFLAGS} -c ${SRC_DIR}/symtable.cpp -o ${BUILD_DIR}/symtable.o

${BUILD_DIR}/parser.o: ${SRC_DIR}/parser.cpp ${SRC_DIR}/parser.h
	g++ ${CXXFLAGS} -c ${SRC_DIR}/parser.cpp -o ${BUILD_DIR}/parser.o

${BUILD_DIR}/initializer.o: ${SRC_DIR}/initializer.cpp ${SRC_DIR}/initializer.h
	g++ ${CXXFLAGS} -c ${SRC_DIR}/initializer.cpp -o ${BUILD_DIR}/initializer.o

${BUILD_DIR}/geneeyore.o: ${SRC_DIR}/geneeyore.cpp ${SRC_DIR}/geneeyore.h
	g++ ${CXXFLAGS} -c ${SRC_DIR}/geneeyore.cpp -o ${BUILD_DIR}/geneeyore.o

${BUILD_DIR}/gentigger.o: ${SRC_DIR}/gentigger.cpp ${SRC_DIR}/gentigger.h
	g++ ${CXXFLAGS} -c ${SRC_DIR}/gentigger.cpp -o ${BUILD_DIR}/gentigger.o

${BUILD_DIR}/genriscv.o: ${SRC_DIR}/genriscv.cpp ${SRC_DIR}/genriscv.h
	g++ ${CXXFLAGS} -c ${SRC_DIR}/genriscv.cpp -o ${BUILD_DIR}/genriscv.o

${BUILD_DIR}/parser.tab.o: ${SRC_DIR}/parser.tab.cpp
	g++ ${CXXFLAGS} -c ${SRC_DIR}/parser.tab.cpp -o ${BUILD_DIR}/parser.tab.o

clean:
	rm -rf ${BUILD_DIR}/*

.PHONY: clean