#include "initializer.h"

extern void yyerror(string msg);

void Initializer::set_target(Variable * var, bool _is_array) {
    target = var;
    is_array = _is_array;
    if (_is_array) {
        if (!var->is_array())
            yyerror("try to initialize a scalar with vector");
        int len = target->shape.size();
        dim_size = vector<int>(len);
        current_dim = -1;
        current_pos = 0;
        int mul = 1;
        for (int i = len - 1; i >= 0; i--) {
            mul *= target->shape[i];
            dim_size[i] = mul;
        }
    }
}

pair<int, int> Initializer::increase_dim() {
    if (current_dim + 1 >= dim_size.size())
        yyerror("redundant '{'");
    current_dim++;
    int old_pos = current_pos;
    int temp = current_pos % dim_size[current_dim];
    if (temp != 0)
        current_pos += (dim_size[current_dim] - temp);
    return make_pair(old_pos, current_pos);
}

pair<int, int> Initializer::decrease_dim() {
    if (current_dim < 0)
        yyerror("redundant '}'");
    int old_pos = current_pos;
    int temp = current_pos % dim_size[current_dim];
    if (temp != 0)
        current_pos += (dim_size[current_dim] - temp);
    current_dim--;
    return make_pair(old_pos, current_pos);
}

int Initializer::init_next_val(int val) {
    if (current_pos >= target->array_value.size())
        yyerror("array index out of range");
    target->array_value[current_pos] = val;
    return current_pos++;
}