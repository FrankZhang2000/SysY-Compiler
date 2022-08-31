#ifndef GENTIGGER
#define GENTIGGER

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>

using namespace std;

class TiggerGenerator {
public:
    vector<vector<string> > splitted_eeyore;
    vector<string> tigger;
    map<string, string> var_to_reg;
    map<string, int> var_to_offset;
    map<string, int> reg_to_offset;
    map<string, string> global_to_v;
    set<string> used_reg;
    set<string> array_var;
    int global_cnt;
    bool global;
    int param_cnt;
    TiggerGenerator(vector<string> & eeyore);
    void insert_into_tigger(string instruction);
    void caller_pushstack();
    void caller_popstack();
    void callee_pushstack();
    void callee_popstack();
    void split_eeyore(vector<string> & eeyore);
    int alloc_reg(vector<vector<string> >::iterator funcbegin, int param_cnt);
    bool reg_used(string reg);
    bool is_reg(string reg);
    bool have_reg(string var);
    void load_var_to_reg(string var, string reg);
    void store_reg_to_var(string reg_src, string reg_tmp, string var);
    void proceed();
    bool is_access(string var);
    pair<string, string> parse_array_access(string access);
    bool is_immediate(string var);
    string alloc_func_reg(string var, string default_reg);
    string alloc_arr_elem_pointer(string var, string reg_pt, string offset);
    void tiggererror(string msg);
};

#endif