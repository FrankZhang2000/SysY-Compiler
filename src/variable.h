#ifndef VARIABLE
#define VARIABLE

#include <vector>
#include <string>
#include <queue>

using namespace std;

class Variable {
public:
    static int count;
    static queue<int> freed_seqno;
    enum var_type {t_value, t_temp, t_param, t_access, t_const} type;
    Variable * array;
    Variable * offset;
    int seq_no;
    int init_val;
    int size;
    bool isglobal;
    vector<int> shape;
    vector<int> array_value;
    Variable(bool isconst, bool _isglobal=false);
    Variable(int value);
    Variable(bool isparam, int seq);
    Variable(bool isconst, vector<int> * _shape);
    Variable(int seq, vector<int> * _shape);
    Variable(Variable * _array, Variable * _offset);
    string get_name();
    bool have_init_val();
    bool is_array();
    bool is_access();
    vector<int> get_mul_shape();
    void rel_seqno();
    int alloc_seqno();
};

#endif