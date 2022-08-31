#ifndef SYMTABLE
#define SYMTABLE

#include <map>
#include <string>
#include "variable.h"

class SymbolTable {
public:
    map<string, Variable *> symtable;
    SymbolTable * prev;
    SymbolTable(SymbolTable * _prev);
    ~SymbolTable();
    void insert_var(string name, Variable * var);
    Variable * find_var(string name);
};

#endif