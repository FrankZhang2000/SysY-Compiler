#include "others.h"

Function::Function(bool _ret_int, int _param_count) {
    ret_int = _ret_int;
    param_count = _param_count;
}

IfStmt::IfStmt(int _true_label, int _false_label, int _next_label) {
    true_label = _true_label;
    false_label = _false_label;
    next_label = _next_label;
}

WhileLoop::WhileLoop(int _begin_label, int _next_label) {
    begin_label = _begin_label;
    next_label = _next_label;
}