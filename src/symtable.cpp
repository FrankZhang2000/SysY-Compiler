#include "symtable.h"

extern void yyerror(string msg);

SymbolTable::SymbolTable(SymbolTable * _prev) {
    prev = _prev;
}

SymbolTable::~SymbolTable() {
    map<string, Variable *>::iterator it;
    for (it = symtable.begin(); it != symtable.end(); it++)
        delete it->second;
}

void SymbolTable::insert_var(string name, Variable * var) {
    if (symtable.find(name) != symtable.end())
        yyerror("variable redefined");
    symtable.insert(make_pair(name, var));
}

Variable * SymbolTable::find_var(string name) {
    SymbolTable * current = this;
    while (current) {
        map<string, Variable *>::iterator it;
        if ((it = current->symtable.find(name)) != current->symtable.end())
            return it->second;
        else
            current = current->prev;
    }
    yyerror("variable undefined");
    return NULL;
}