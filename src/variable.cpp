#include "variable.h"

extern void yyerror(string msg);
extern void emit(string s);
extern vector<Variable *> del_var;

Variable::Variable(bool isconst, bool _isglobal) {
    isglobal = _isglobal;
    if (isconst)
        type = var_type::t_const;
    else
        type = var_type::t_temp;
    seq_no = alloc_seqno();
    size = 1;
    emit("var " + get_name());
}

Variable::Variable(int value) {
    seq_no = -1;
    type = var_type::t_value;
    init_val = value;
    size = 1;
}

Variable::Variable(bool isparam, int seq) {
    seq_no = seq;
    type = var_type::t_param;
    size = 1;
}

Variable::Variable(bool isconst, vector<int> * _shape) {
    shape = *_shape;
    seq_no = count++;
    if (isconst)
        type = var_type::t_const;
    else
        type = var_type::t_temp;
    size = 1;
    for (vector<int>::iterator it = shape.begin(); it != shape.end(); it++)
        size *= *it;
    array_value = vector<int>(size, 0);
    emit("var " + to_string(size * 4) + " " + get_name());
}

Variable::Variable(int seq, vector<int> * _shape) {
    shape = *_shape;
    seq_no = seq;
    type = var_type::t_param;
    size = -1;
}

Variable::Variable(Variable * _array, Variable * _offset) {
    array = _array;
    offset = _offset;
    type = var_type::t_access;
    size = -1;
}

string Variable::get_name() {
    switch (type) {
        case t_const:
            return "T" + to_string(seq_no);
        case t_temp:
            return "t" + to_string(seq_no);
        case t_param:
            return "p" + to_string(seq_no);
        case t_value:
            return to_string(init_val);
        case t_access:
            return array->get_name() + "[" + offset->get_name() + "]";
        default:
            yyerror("unknown type");
    }
    return string();
}

bool Variable::have_init_val() {
    return type == var_type::t_const || type == var_type::t_value;
}

bool Variable::is_array() {
    return shape.size() != 0;
}

bool Variable::is_access() {
    return type == var_type::t_access;
}

vector<int> Variable::get_mul_shape() {
    int mul = 4;
    vector<int> mul_shape = shape;
    int len = shape.size();
    for (int i = len - 1; i >= 0; i--) {
        mul_shape[i] = mul;
        mul *= shape[i];
    }
    return mul_shape;
}

void Variable::rel_seqno() {
    if (type == var_type::t_temp && !is_array() && !isglobal) {
        freed_seqno.push(seq_no);
        seq_no = -1;
        del_var.push_back(this);
    }
    else if (type == var_type::t_value)
        del_var.push_back(this);
}

int Variable::alloc_seqno() {
    if (type == var_type::t_temp && !is_array() && !isglobal && !freed_seqno.empty()) {
        int seqno = freed_seqno.front();
        freed_seqno.pop();
        return seqno;
    }
    else
        return count++;
}

int Variable::count = 0;
queue<int> Variable::freed_seqno = queue<int>();