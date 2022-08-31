%{

#define YYPARSER

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "parser.h"
#include "variable.h"
#include "symtable.h"
#include "initializer.h"
#include "others.h"
#include "geneeyore.h"
#include "gentigger.h"
#include "genriscv.h"

using namespace std;

#define YYSTYPE void *

extern FILE * yyin;
extern FILE * yyout;
extern int yylineno;
extern int yylex();

vector<string> instructions;

Parser parser;
Initializer initializer;

vector<Variable *> del_var;

void yyerror(string msg) {
    cerr << "Error at line: " << yylineno << "\tMessage: " << msg << endl;
    exit(1);
}

void emit(string s) {
    instructions.push_back(s);
}

void loop_init_to_zero(string name, int start, int end) {
    if (start >= end)
        return;
    if (parser.is_global())
        emit("//inserttomain");
    Variable * temp = new Variable(false);
    emit(temp->get_name() + " = " + to_string(start * 4));
    int label = parser.alloc_label();
    emit("l" + to_string(label) + ":");
    emit(name + "[" + temp->get_name() + "] = 0");
    emit(temp->get_name() + " = " + temp->get_name() + " + 4");
    emit("if " + temp->get_name() + " < " + to_string(end * 4) + " goto " + "l" + to_string(label));
    temp->rel_seqno();
}

%}

%token IF ELSE WHILE BREAK CONTINUE RETURN
%token INT VOID CONST
%token EQ NE LE GE LT GT PLUS MINUS TIMES OVER MOD ASSIGN
%token NOT AND OR
%token LPAREN RPAREN LSQBRKET RSQBRKET LFLBRKET RFLBRKET SEMI COMMA
%token NUM
%token IDENT

%%

CompUnit            :   Decl
                    |   FuncDef
                    |   CompUnit Decl
                    |   CompUnit FuncDef
                    ;

Decl                :   ConstDecl
                    |   VarDecl
                    ;

ConstDecl           :   CONST INT ConstDefCommaArray SEMI
                    ;

ConstDefCommaArray  :   ConstDef
                    |   ConstDefCommaArray COMMA ConstDef
                    ;

ConstDef            :   IDENT {
                            $$ = new Variable(true, true);
                            parser.top->insert_var(*((string *)$1), (Variable *)$$);
                            initializer.set_target((Variable *)$$, false);
                        }
                        ASSIGN ConstInitVal
                    |   IDENT ConstExpSqArray {
                            $$ = new Variable(true, (vector<int> *)$2);
                            parser.top->insert_var(*((string *)$1), (Variable *)$$);
                            initializer.set_target((Variable *)$$, true);
                        }
                        ASSIGN ConstInitVal
                    ;

ConstExpSqArray     :   LSQBRKET ConstExp RSQBRKET {
                            $$ = new vector<int>;
                            ((vector<int> *)$$)->push_back(((Variable *)$2)->init_val);
                        }
                    |   ConstExpSqArray LSQBRKET ConstExp RSQBRKET {
                            $$ = $1;
                            ((vector<int> *)$$)->push_back(((Variable *)$3)->init_val);
                        }
                    ;

ConstInitVal        :   ConstExp {
                            int val = ((Variable *)$1)->init_val;
                            if (!initializer.is_array) {
                                initializer.target->init_val = val;
                                emit(initializer.target->get_name() + " = " + to_string(val));
                            }
                            else {
                                int pos = initializer.init_next_val(val);
                                emit(initializer.target->get_name() + "[" + to_string(pos * 4) + "] = " + to_string(val));
                            }
                            ((Variable *)$1)->rel_seqno();
                        }
                    |   LFLBRKET {
                            pair<int, int> p = initializer.increase_dim();
                            if (!parser.is_global()) {
                                string name = initializer.target->get_name();
                                loop_init_to_zero(name, p.first, p.second);
                            }
                            int pos = initializer.init_next_val(0);
                            if (!parser.is_global())
                                emit(name + "[" + to_string(pos * 4) + "] = 0");
                        }
                        RFLBRKET {
                            pair<int, int> p = initializer.decrease_dim();
                            if (!parser.is_global()) {
                                string name = initializer.target->get_name();
                                loop_init_to_zero(name, p.first, p.second);
                            }
                        }
                    |   LFLBRKET {
                            pair<int, int> p = initializer.increase_dim();
                            if (!parser.is_global()) {
                                string name = initializer.target->get_name();
                                loop_init_to_zero(name, p.first, p.second);
                            }
                        }
                        ConstInitValArray RFLBRKET {
                            pair<int, int> p = initializer.decrease_dim();
                            if (!parser.is_global()) {
                                string name = initializer.target->get_name();
                                loop_init_to_zero(name, p.first, p.second);
                            }
                        }
                    ;

ConstInitValArray   :   ConstInitVal
                    |   ConstInitValArray COMMA ConstInitVal
                    ;

VarDecl             :   INT VarDefCommaArray SEMI
                    ;

VarDefCommaArray    :   VarDef
                    |   VarDefCommaArray COMMA VarDef
                    ;

VarDef              :   IDENT {
                            $$ = new Variable(false, true);
                            parser.top->insert_var(*((string *)$1), (Variable *)$$);
                        }
                    |   IDENT {
                            $$ = new Variable(false, true);
                            parser.top->insert_var(*((string *)$1), (Variable *)$$);
                            initializer.set_target((Variable *)$$, false);
                        }
                        ASSIGN InitVal
                    |   IDENT ConstExpSqArray {
                            $$ = new Variable(false, (vector<int> *)$2);
                            parser.top->insert_var(*((string *)$1), (Variable *)$$);
                        }
                    |   IDENT ConstExpSqArray {
                            $$ = new Variable(false, (vector<int> *)$2);
                            parser.top->insert_var(*((string *)$1), (Variable *)$$);
                            initializer.set_target((Variable *)$$, true);
                        }
                        ASSIGN InitVal
                    ;

InitVal             :   Exp {
                            string name = ((Variable *)$1)->get_name();
                            if (!initializer.is_array)
                                emit(initializer.target->get_name() + " = " + name);
                            else {
                                int pos = initializer.init_next_val(0);
                                emit(initializer.target->get_name() + "[" + to_string(pos * 4) + "] = " + name);
                            }
                            ((Variable *)$1)->rel_seqno();
                        }
                    |   LFLBRKET {
                            pair<int, int> p = initializer.increase_dim();
                            if (!parser.is_global()) {
                                string name = initializer.target->get_name();
                                loop_init_to_zero(name, p.first, p.second);
                            }
                            int pos = initializer.init_next_val(0);
                            if (!parser.is_global())
                                emit(name + "[" + to_string(pos * 4) + "] = 0");
                        }
                        RFLBRKET {
                            pair<int, int> p = initializer.decrease_dim();
                            if (!parser.is_global()) {
                                string name = initializer.target->get_name();
                                loop_init_to_zero(name, p.first, p.second);
                            }
                        }
                    |   LFLBRKET {
                            pair<int, int> p = initializer.increase_dim();
                            if (!parser.is_global()) {
                                string name = initializer.target->get_name();
                                loop_init_to_zero(name, p.first, p.second);
                            }
                        }
                        InitValArray RFLBRKET {
                            pair<int, int> p = initializer.decrease_dim();
                            if (!parser.is_global()) {
                                string name = initializer.target->get_name();
                                loop_init_to_zero(name, p.first, p.second);
                            }
                        }
                    ;

InitValArray        :   InitVal
                    |   InitValArray COMMA InitVal
                    ;

FuncDef             :   VOID IDENT LPAREN RPAREN {
                            emit("f_" + *((string *)$2) + " [0]");
                            Function * func = new Function(false, 0);
                            parser.add_func(*((string *)$2), func);
                        }
                        Block {
                            if (instructions.back().substr(0, 6) != "return")
                                emit("return");
                            emit("end f_" + *((string *)$2));
                        }
                    |   VOID IDENT LPAREN {
                            parser.new_symtab();
                        }
                        FuncFParams RPAREN {
                            emit("f_" + *((string *)$2) + " [" + to_string(*((int *)$5)) + "]");
                            Function * func = new Function(false, *((int *)$5));
                            parser.add_func(*((string *)$2), func);
                        }
                        Block {
                            if (instructions.back().substr(0, 6) != "return")
                                emit("return");
                            emit("end f_" + *((string *)$2));
                            parser.del_symtab();
                        }
                    |   INT IDENT LPAREN RPAREN {
                            emit("f_" + *((string *)$2) + " [0]");
                            Function * func = new Function(true, 0);
                            parser.add_func(*((string *)$2), func);
                        }
                        Block {
                            if (instructions.back().substr(0, 6) != "return")
                                emit("return 0");
                            emit("end f_" + *((string *)$2));
                        }
                    |   INT IDENT LPAREN {
                            parser.new_symtab();
                        }
                        FuncFParams RPAREN {
                            emit("f_" + *((string *)$2) + " [" + to_string(*((int *)$5)) + "]");
                            Function * func = new Function(true, *((int *)$5));
                            parser.add_func(*((string *)$2), func);
                        }
                        Block {
                            if (instructions.back().substr(0, 6) != "return")
                                emit("return 0");
                            emit("end f_" + *((string *)$2));
                            parser.del_symtab();
                        }
                    ;

FuncFParams         :   INT IDENT {
                            $$ = new int;
                            *((int *)$$) = 0;
                            Variable * param = new Variable(true, *((int *)$$));
                            (*((int *)$$))++;
                            parser.top->insert_var(*((string *)$2), param);
                        }
                    |   INT IDENT LSQBRKET RSQBRKET {
                            $$ = new int;
                            *((int *)$$) = 0;
                            vector<int> * shape = new vector<int>;
                            shape->push_back(0);
                            Variable * param = new Variable(*((int *)$$), shape);
                            (*((int *)$$))++;
                            parser.top->insert_var(*((string *)$2), param);
                        }
                    |   INT IDENT LSQBRKET RSQBRKET ConstExpSqArray {
                            $$ = new int;
                            *((int *)$$) = 0;
                            vector<int> * shape = new vector<int>;
                            shape->push_back(0);
                            shape->insert(shape->end(), ((vector<int> *)$5)->begin(), ((vector<int> *)$5)->end());
                            Variable * param = new Variable(*((int *)$$), shape);
                            (*((int *)$$))++;
                            parser.top->insert_var(*((string *)$2), param);
                        }
                    |   FuncFParams COMMA INT IDENT {
                            $$ = $1;
                            Variable * param = new Variable(true, *((int *)$$));
                            (*((int *)$$))++;
                            parser.top->insert_var(*((string *)$4), param);
                        }
                    |   FuncFParams COMMA INT IDENT LSQBRKET RSQBRKET {
                            $$ = $1;
                            vector<int> * shape = new vector<int>;
                            shape->push_back(0);
                            Variable * param = new Variable(*((int *)$$), shape);
                            (*((int *)$$))++;
                            parser.top->insert_var(*((string *)$4), param);
                        }
                    |   FuncFParams COMMA INT IDENT LSQBRKET RSQBRKET ConstExpSqArray {
                            $$ = $1;
                            vector<int> * shape = new vector<int>;
                            shape->push_back(0);
                            shape->insert(shape->end(), ((vector<int> *)$7)->begin(), ((vector<int> *)$7)->end());
                            Variable * param = new Variable(*((int *)$$), shape);
                            (*((int *)$$))++;
                            parser.top->insert_var(*((string *)$4), param);
                        }
                    ;

Block               :   LFLBRKET RFLBRKET
                    |   LFLBRKET {
                            parser.new_symtab();
                        }
                        BlockItemArray {
                            parser.del_symtab();
                        }
                        RFLBRKET
                    ;

BlockItemArray      :   BlockItem
                    |   BlockItemArray BlockItem
                    ;

BlockItem           :   Decl
                    |   Stmt
                    ;

Stmt                :   LVal ASSIGN Exp SEMI {
                            emit(((Variable *)$1)->get_name() + " = " + ((Variable *)$3)->get_name());
                            if (((Variable *)$1)->is_access()) {
                                ((Variable *)$1)->offset->rel_seqno();
                                delete (Variable *)$1;
                            }
                            ((Variable *)$3)->rel_seqno();
                        }
                    |   SEMI
                    |   Exp SEMI
                    |   Block
                    |   IF LPAREN Cond RPAREN {
                            $1 = new IfStmt(*((int *)$3), parser.alloc_label(), parser.alloc_label());
                            emit("goto l" + to_string(((IfStmt *)$1)->false_label));
                            emit("l" + to_string(((IfStmt *)$1)->true_label) + ":");
                        }
                        Stmt {
                            emit("goto l" + to_string(((IfStmt *)$1)->next_label));
                            emit("l" + to_string(((IfStmt *)$1)->false_label) + ":");
                        }
                        OptionalElse {
                            emit("l" + to_string(((IfStmt *)$1)->next_label) + ":");
                            delete (IfStmt *)$1;
                        }
                    |   WHILE {
                            $1 = new WhileLoop(parser.alloc_label(), parser.alloc_label());
                            parser.add_while((WhileLoop *)$1);
                            emit("l" + to_string(((WhileLoop *)$1)->begin_label) + ":");
                        }
                        LPAREN Cond RPAREN {
                            emit("goto l" + to_string(((WhileLoop *)$1)->next_label));
                            emit("l" + to_string(*((int *)$4)) + ":");
                        }
                        Stmt {
                            emit("goto l" + to_string(((WhileLoop *)$1)->begin_label));
                            emit("l" + to_string(((WhileLoop *)$1)->next_label) + ":");
                            parser.pop_while();
                        }
                    |   BREAK SEMI {
                            WhileLoop * current = parser.get_curr_while();
                            emit("goto l" + to_string(current->next_label));
                        }
                    |   CONTINUE SEMI {
                            WhileLoop * current = parser.get_curr_while();
                            emit("goto l" + to_string(current->begin_label));
                        }
                    |   RETURN SEMI {
                            emit("return");
                        }
                    |   RETURN Exp SEMI {
                            emit("return " + ((Variable *)$2)->get_name());
                            ((Variable *)$2)->rel_seqno();
                        }
                    ;

OptionalElse        :   ELSE Stmt
                    |   
                    ;

Exp                 :   AddExp {
                            $$ = $1;
                        }
                    ;

Cond                :   LOrExp {
                            $$ = $1;
                        }
                    ;

LVal                :   IDENT {
                            string name = *((string *)$1);
                            $$ = parser.top->find_var(name);
                        }
                    |   IDENT ExpSqArray {
                            string name = *((string *)$1);
                            Variable * var = parser.top->find_var(name);
                            vector<Variable *> & pos = *((vector<Variable *> *)$2);
                            const vector<int> & mul_shape = var->get_mul_shape();
                            bool all_have_init_val = true;
                            int len = pos.size();
                            int sum_offset = 0;
                            for (int i = 0; i < len; i++) {
                                if (!pos[i]->have_init_val())
                                    all_have_init_val = false;
                                else {
                                    sum_offset += pos[i]->init_val * mul_shape[i];
                                    pos[i]->rel_seqno();
                                }
                            }
                            if (all_have_init_val) {
                                if (pos.size() == mul_shape.size()) {
                                    if (var->have_init_val())
                                        $$ = new Variable(var->array_value[sum_offset / 4]);
                                    else {
                                        Variable * var_offset = new Variable(sum_offset);
                                        $$ = new Variable(var, var_offset);
                                    }
                                }
                                else {
                                    $$ = new Variable(false);
                                    emit(((Variable *)$$)->get_name() + " = " + var->get_name() + " + " + to_string(sum_offset));
                                    var->rel_seqno();
                                }
                            }
                            else {
                                Variable * var_offset = new Variable(false);
                                emit(var_offset->get_name() + " = " + to_string(sum_offset));
                                Variable * temp = new Variable(false);
                                for (int i = 0; i < len; i++) {
                                    if (!pos[i]->have_init_val()) {
                                        emit(temp->get_name() + " = " + pos[i]->get_name() + " * " + to_string(mul_shape[i]));
                                        pos[i]->rel_seqno();
                                        emit(var_offset->get_name() + " = " + var_offset->get_name() + " + " + temp->get_name());
                                    }
                                }
                                temp->rel_seqno();
                                if (pos.size() == mul_shape.size())
                                    $$ = new Variable(var, var_offset);
                                else {
                                    $$ = new Variable(false);
                                    emit(((Variable *)$$)->get_name() + " = " + var->get_name() + " + " + var_offset->get_name());
                                    var->rel_seqno();
                                    var_offset->rel_seqno();
                                }
                            }
                        }
                    ;

ExpSqArray          :   LSQBRKET Exp RSQBRKET {
                            $$ = new vector<Variable *>;
                            ((vector<Variable *> *)$$)->push_back((Variable *)$2);
                        }
                    |   ExpSqArray LSQBRKET Exp RSQBRKET {
                            $$ = $1;
                            ((vector<Variable *> *)$$)->push_back((Variable *)$3);
                        }
                    ;

PrimaryExp          :   LPAREN Exp RPAREN {
                            $$ = $2;
                        }
                    |   LVal {
                            if (((Variable *)$1)->is_access()) {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name());
                                ((Variable *)$1)->offset->rel_seqno();
                                delete (Variable *)$1;
                            }
                            else
                                $$ = $1;
                        }
                    |   NUM {
                            $$ = new Variable(*((int *)$1));
                        }
                    ;

UnaryExp            :   PrimaryExp {
                            $$ = $1;
                        }
                    |   IDENT LPAREN RPAREN {
                            string name = *((string *)$1);
                            if (name == "starttime") {
                                emit("param "+ to_string(yylineno));
                                emit("call f__sysy_starttime");
                            }
                            else if (name == "stoptime") {
                                emit("param "+ to_string(yylineno));
                                emit("call f__sysy_stoptime");
                            }
                            else {
                                Function * func = parser.get_func(name);
                                if (func->ret_int) {
                                    $$ = new Variable(false);
                                    emit(((Variable *)$$)->get_name() + " = call f_" + name);
                                }
                                else
                                    emit("call f_" + name);
                            }
                        }
                    |   IDENT LPAREN FuncRParams RPAREN {
                            string name = *((string *)$1);
                            Function * func = parser.get_func(name);
                            vector<Variable *> & params = *((vector<Variable *> *)$3);
                            if (params.size() != func->param_count)
                                yyerror("function get wrong parameters");
                            for (vector<Variable *>::iterator it = params.begin(); it != params.end(); it++) {
                                emit("param " + (*it)->get_name());
                                (*it)->rel_seqno();
                            }
                            if (func->ret_int) {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = call f_" + name);
                            }
                            else
                                emit("call f_" + name);
                        }
                    |   PLUS UnaryExp {
                            $$ = $2;
                        }
                    |   MINUS UnaryExp {
                            if (((Variable *)$2)->have_init_val())
                                $$ = new Variable(-1 * ((Variable *)$2)->init_val);
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = - " + ((Variable *)$2)->get_name());
                            }
                            ((Variable *)$2)->rel_seqno();
                        }
                    |   NOT UnaryExp {
                            if (((Variable *)$2)->have_init_val()) {
                                if ((((Variable *)$2)->init_val) == 0)
                                    $$ = new Variable(1);
                                else
                                    $$ = new Variable(0);
                            }
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = ! " + ((Variable *)$2)->get_name());
                            }
                            ((Variable *)$2)->rel_seqno();
                        }
                    ;

FuncRParams         :   Exp {
                            $$ = new vector<Variable *>;
                            ((vector<Variable *> *)$$)->push_back((Variable *)$1);
                        }
                    |   FuncRParams COMMA Exp {
                            $$ = $1;
                            ((vector<Variable *> *)$$)->push_back((Variable *)$3);
                        }
                    ;

MulExp              :   UnaryExp {
                            $$ = $1;
                        }
                    |   MulExp TIMES UnaryExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable(((Variable *)$1)->init_val * ((Variable *)$3)->init_val);
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " * " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    |   MulExp OVER UnaryExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable(((Variable *)$1)->init_val / ((Variable *)$3)->init_val);
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " / " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    |   MulExp MOD UnaryExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable(((Variable *)$1)->init_val % ((Variable *)$3)->init_val);
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " % " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    ;

AddExp              :   MulExp {
                            $$ = $1;
                        }
                    |   AddExp PLUS MulExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable(((Variable *)$1)->init_val + ((Variable *)$3)->init_val);
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " + " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    |   AddExp MINUS MulExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable(((Variable *)$1)->init_val - ((Variable *)$3)->init_val);
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " - " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    ;

RelExp              :   AddExp {
                            $$ = $1;
                        }
                    |   RelExp LT AddExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable((int)(((Variable *)$1)->init_val < ((Variable *)$3)->init_val));
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " < " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    |   RelExp GT AddExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable((int)(((Variable *)$1)->init_val > ((Variable *)$3)->init_val));
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " > " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    |   RelExp LE AddExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable((int)(((Variable *)$1)->init_val <= ((Variable *)$3)->init_val));
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " <= " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    |   RelExp GE AddExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable((int)(((Variable *)$1)->init_val >= ((Variable *)$3)->init_val));
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " >= " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    ;

EqExp               :   RelExp {
                            $$ = $1;
                        }
                    |   EqExp EQ RelExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable((int)(((Variable *)$1)->init_val == ((Variable *)$3)->init_val));
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " == " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    |   EqExp NE RelExp {
                            if (((Variable *)$1)->have_init_val() && ((Variable *)$3)->have_init_val())
                                $$ = new Variable((int)(((Variable *)$1)->init_val != ((Variable *)$3)->init_val));
                            else {
                                $$ = new Variable(false);
                                emit(((Variable *)$$)->get_name() + " = " + ((Variable *)$1)->get_name() + " != " + ((Variable *)$3)->get_name());
                            }
                            ((Variable *)$1)->rel_seqno();
                            ((Variable *)$3)->rel_seqno();
                        }
                    ;

LAndExp             :   EqExp {
                            $$ = new int;
                            *((int *)$$) = parser.alloc_label();
                            emit("if " + ((Variable *)$1)->get_name() + " == 0 goto l" + to_string(*((int *)$$)));
                            ((Variable *)$1)->rel_seqno();
                        }
                    |   LAndExp AND EqExp {
                            $$ = $1;
                            emit("if " + ((Variable *)$3)->get_name() + " == 0 goto l" + to_string(*((int *)$$)));
                            ((Variable *)$3)->rel_seqno();
                        }
                    ;

LOrExp              :   LAndExp {
                            $$ = new int;
                            *((int *)$$) = parser.alloc_label();
                            emit("goto l" + to_string(*((int *)$$)));
                            emit("l" + to_string(*((int *)$1)) + ":");
                        }
                    |   LOrExp OR LAndExp {
                            $$ = $1;
                            emit("goto l" + to_string(*((int *)$$)));
                            emit("l" + to_string(*((int *)$3)) + ":");
                        }
                    ;

ConstExp            :   AddExp {
                            $$ = $1;
                        }
                    ;

%%

void add_sys_calls() {
    parser.add_func("getint", new Function(true, 0));
    parser.add_func("getch", new Function(true, 0));
    parser.add_func("getarray", new Function(true, 1));
    parser.add_func("putint", new Function(false, 1));
    parser.add_func("putch", new Function(false, 1));
    parser.add_func("putarray", new Function(false, 2));
}

void del_temp_var() {
    for (vector<Variable *>::iterator it = del_var.begin(); it != del_var.end(); it++)
        delete *it;
}

int main(int argc, char ** argv) {
    bool to_eeyore = false;
    bool to_tigger = false;
    bool to_riscv = false;
    if (argc == 5) {
        if ((yyin = fopen(argv[2], "r")) == NULL) {
            cerr << "can't open " << argv[3] << endl;
            exit(1);
        }
        if (freopen(argv[4], "w", stdout) == NULL) {
            cerr << "can't open " << argv[5] << endl;
            exit(1);
        }
        to_riscv = true;
    }
    else if (argc == 6) {
        if ((yyin = fopen(argv[3], "r")) == NULL) {
            cerr << "can't open " << argv[3] << endl;
            exit(1);
        }
        if (freopen(argv[5], "w", stdout) == NULL) {
            cerr << "can't open " << argv[5] << endl;
            exit(1);
        }
        if (argv[2][1] == 't')
            to_tigger = true;
        else if (argv[2][1] == 'e')
            to_eeyore = true;
        else {
            cerr << "wrong parameter " << argv[2] << endl;
            exit(1);
        }
    }
    else {
        cerr << "wrong parameter" << endl;
        exit(1);
    }
    add_sys_calls();
    yyparse();
    del_temp_var();
    EeyoreGenerator eeyoregenerator(instructions);
    if (to_eeyore) {
        for (vector<string>::iterator it = eeyoregenerator.eeyore.begin(); it != eeyoregenerator.eeyore.end(); it++)
            cout << *it << endl;
        return 0;
    }
    TiggerGenerator tiggergenerator(eeyoregenerator.eeyore);
    if (to_tigger) {
        for (vector<string>::iterator it = tiggergenerator.tigger.begin(); it != tiggergenerator.tigger.end(); it++)
            cout << *it << endl;
        return 0;
    }
    RiscvGenerator riscvgenerator(tiggergenerator.tigger);
    if (to_riscv) {
        for (vector<string>::iterator it = riscvgenerator.riscv.begin(); it != riscvgenerator.riscv.end(); it++)
            cout << *it << endl;
    }
    return 0;
}