#ifndef GENEEYORE
#define GENEEYORE

#include <string>
#include <vector>
#include <set>

using namespace std;

class EeyoreGenerator {
public:
    vector<string> instructions;
    vector<string> eeyore;
    EeyoreGenerator(vector<string> & _instructions);
    void insert_into_eeyore(string & instruction);
    void insert_into_eeyore(vector<string> & s);
    bool is_var_def(string & s);
    bool is_func_header(string & s);
    bool is_func_end(string & s);
    void proceed();
};

#endif