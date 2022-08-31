#ifndef OTHERS
#define OTHERS

class Function {
public:
    bool ret_int;
    int param_count;
    Function(bool _ret_int, int _param_count);
};

class IfStmt {
public:
    int true_label;
    int false_label;
    int next_label;
    IfStmt(int _true_label, int _false_label, int _next_label);
};

class WhileLoop {
public:
    int begin_label;
    int next_label;
    WhileLoop(int _begin_label, int _next_label);
};

#endif