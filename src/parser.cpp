#include "parser.h"

extern void yyerror(string msg);

Parser::Parser() {
    top = new SymbolTable(NULL);
}

Parser::~Parser() {
    map<string, Function *>::iterator it;
    for (it = func_table.begin(); it != func_table.end(); it++)
        delete it->second;
}

void Parser::new_symtab() {
    top = new SymbolTable(top);
}

void Parser::del_symtab() {
    if (top == NULL)
        yyerror("no active symtab");
    SymbolTable * del = top;
    top = top->prev;
    delete del;
}

bool Parser::is_global() {
    return top->prev == NULL;
}

void Parser::add_func(string name, Function * func) {
    map<string, Function *>::iterator it;
    if ((it = func_table.find(name)) != func_table.end())
        yyerror("function redefined");
    else
        func_table.insert(make_pair(name, func));
}

Function * Parser::get_func(string name) {
    map<string, Function *>::iterator it;
    if ((it = func_table.find(name)) != func_table.end())
        return it->second;
    else
        yyerror("function undefined");
    return NULL;
}

void Parser::add_while(WhileLoop * w) {
    while_list.push(w);
}

void Parser::pop_while() {
    if (while_list.empty())
        yyerror("no while loop");
    delete while_list.top();
    while_list.pop();
}

WhileLoop * Parser::get_curr_while() {
    if (while_list.empty())
        yyerror("no while loop");
    return while_list.top();
}

int Parser::alloc_label() {
    return label++;
}

int Parser::label = 0;