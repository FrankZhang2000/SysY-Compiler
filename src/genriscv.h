#ifndef GENRISCV
#define GENRISCV

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class RiscvGenerator {
public:
    int stk;
    vector<vector<string> > splitted_tigger;
    vector<string> riscv;
    RiscvGenerator(vector<string> & tigger);
    void split_tigger(vector<string> & tigger);
    void insert_into_riscv(string instruction);
    void proceed();
    void riscverror(string msg);
    bool is_immediate(string var);
    bool is_int12(string var);
    bool is_int12(int intval);
    pair<string, string> parse_array_access(string access);
    bool is_access(string var);
};

#endif