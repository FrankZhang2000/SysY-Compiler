#ifndef PARSER
#define PARSER

#include <map>
#include <vector>
#include <string>
#include <stack>
#include "symtable.h"
#include "others.h"

class Parser {
public:
    static int label;
    SymbolTable * top;
    map<string, Function *> func_table;
    stack<WhileLoop *> while_list;
    vector<Variable *> del_var;
    Parser();
    ~Parser();
    void new_symtab();
    void del_symtab();
    bool is_global();
    void add_func(string name, Function * func);
    Function * get_func(string name);
    void add_while(WhileLoop * w);
    void pop_while();
    WhileLoop * get_curr_while();
    int alloc_label();
};

#endif