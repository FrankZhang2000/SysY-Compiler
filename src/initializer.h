#ifndef INITIALIZER
#define INITIALIZER

#include "variable.h"

class Initializer {
public:
    Variable * target;
    bool is_array;
    vector<int> dim_size;
    int current_dim;
    int current_pos;
    void set_target(Variable * var, bool _is_array);
    pair<int, int> increase_dim();
    pair<int, int> decrease_dim();
    int init_next_val(int val);
};

#endif