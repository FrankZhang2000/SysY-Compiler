#include "gentigger.h"

using namespace std;

#define USER_REG_NO 15

string reg_name[] = {
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11",
    "t4", "t5", "t6"
};

#define FUNC_REG_NO 3

string func_def_reg[] = {
    "t1", "t2", "t3"
};

string param_reg[] = {
    "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"
};

#define CALLEE_SAVED_REG_NO 12

string callee_saved_reg[] = {
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11"
};

#define CALLER_SAVED_REG_NO 11

string caller_saved_reg[] = {
    "t4", "t5", "t6",
    "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7"
};

void TiggerGenerator::tiggererror(string msg) {
    cerr << "tigger generator: " << msg << endl;
    exit(-1);
}

TiggerGenerator::TiggerGenerator(vector<string> & eeyore) {
    global = true;
    global_cnt = 0;
    param_cnt = 0;
    split_eeyore(eeyore);
    proceed();
}

void TiggerGenerator::insert_into_tigger(string instruction) {
    tigger.push_back(instruction);
}

void TiggerGenerator::caller_pushstack() {
    for (int i = 0; i < CALLER_SAVED_REG_NO; i++) {
        string reg = caller_saved_reg[i];
        if (reg_used(reg))
            insert_into_tigger("store " + reg + " " + to_string(reg_to_offset[reg]));
    }
}

void TiggerGenerator::caller_popstack() {
    for (int i = 0; i < CALLER_SAVED_REG_NO; i++) {
        string reg = caller_saved_reg[i];
        if (reg_used(reg))
            insert_into_tigger("load " + to_string(reg_to_offset[reg]) + " " + reg);
    }
}

void TiggerGenerator::callee_pushstack() {
    for (int i = 0; i < CALLEE_SAVED_REG_NO; i++) {
        string reg = callee_saved_reg[i];
        if (reg_used(reg))
            insert_into_tigger("store " + reg + " " + to_string(reg_to_offset[reg]));
    }
}

void TiggerGenerator::callee_popstack() {
    for (int i = 0; i < CALLEE_SAVED_REG_NO; i++) {
        string reg = callee_saved_reg[i];
        if (reg_used(reg))
            insert_into_tigger("load " + to_string(reg_to_offset[reg]) + " " + reg);
    }
}

void TiggerGenerator::split_eeyore(vector<string> & eeyore) {
    for (vector<string>::iterator it = eeyore.begin(); it != eeyore.end(); it++) {
        string str = *it + " ";
        vector<string> splitted;
        int pos = str.find(" ");
        while (pos != str.npos) {
            splitted.push_back(str.substr(0, pos));
            str = str.substr(pos + 1);
            pos = str.find(" ");
        }
        splitted_eeyore.push_back(splitted);
    }
}

int TiggerGenerator::alloc_reg(vector<vector<string> >::iterator funcbegin, int param_cnt) {
    var_to_reg = map<string, string>();
    var_to_offset = map<string, int>();
    reg_to_offset = map<string, int>();
    int current_offset = 0;
    used_reg = set<string>();
    for (int i = 0; i < param_cnt; i++) {
        used_reg.insert(param_reg[i]);
        var_to_reg.insert(make_pair("p" + to_string(i), param_reg[i]));
    }
    map<string, int> var_cnt;
    for (vector<vector<string> >::iterator it = funcbegin; ; it++) {
        vector<string> & instr = *it;
        if (instr[0] == "var") {
            if (instr.size() == 2)
                var_cnt.insert(make_pair(instr[1], 0));
            else {
                var_to_offset.insert(make_pair(instr[2], current_offset));
                array_var.insert(instr[2]);
                current_offset += stoi(instr[1]) / 4;
            }
        }
        else if (instr[0] == "end")
            break;
        else {
            for (vector<string>::iterator var = instr.begin(); var != instr.end(); var++) {
                if (var_cnt.find(*var) != var_cnt.end())
                    var_cnt[*var]++;
            }
        }
    }
    multimap<int, string, greater<int> > tmp;
    for (multimap<string, int>::iterator it = var_cnt.begin(); it != var_cnt.end(); it++)
        tmp.insert(make_pair(it->second, it->first));
    int count = 0;
    for (multimap<int, string>::iterator it = tmp.begin(); it != tmp.end(); it++) {
        if (count < USER_REG_NO) {
            var_to_reg.insert(make_pair(it->second, reg_name[count]));
            used_reg.insert(reg_name[count]);
            count++;
        }
        else
            var_to_offset.insert(make_pair(it->second, current_offset++));
    }
    for (set<string>::iterator it = used_reg.begin(); it != used_reg.end(); it++)
        reg_to_offset.insert(make_pair(*it, current_offset++));
    return current_offset;
}

void TiggerGenerator::proceed() {
    for (vector<vector<string> >::iterator it = splitted_eeyore.begin(); it != splitted_eeyore.end(); it++) {
        vector<string> & instr = *it;
        // variable def
        if (instr[0] == "var") {
            if (global) {
                int count = global_cnt++;
                if (instr.size() == 2) {
                    insert_into_tigger("v" + to_string(count) + " = 0");
                    global_to_v.insert(make_pair(instr[1], "v" + to_string(count)));
                }
                else {
                    insert_into_tigger("v" + to_string(count) + " = malloc " + instr[1]);
                    array_var.insert(instr[2]);
                    global_to_v.insert(make_pair(instr[2], "v" + to_string(count)));
                }
            }
        }
        // function start
        else if (instr[0].substr(0, 2) == "f_") {
            global = false;
            int num_param = stoi(instr[1].substr(1, instr[1].length() - 2));
            int stack_usage = alloc_reg(it, num_param);
            insert_into_tigger(instr[0] + " [" + to_string(num_param) + "] [" + to_string(stack_usage) + "]");
            callee_pushstack();
        }
        // function end
        else if (instr[0] == "end") {
            insert_into_tigger("end " + instr[1]);
            global = true;
        }
        // conditional goto
        else if (instr[0] == "if") {
            string reg1 = alloc_func_reg(instr[1], "t1");
            string reg2 = alloc_func_reg(instr[3], "t2");
            insert_into_tigger("if " + reg1 + " " + instr[2] + " " + reg2 + " goto " + instr[5]);
        }
        // unconditional goto
        else if (instr[0] == "goto")
            insert_into_tigger("goto " + instr[1]);
        // label
        else if (instr[0][0] == 'l')
            insert_into_tigger(instr[0]);
        // return
        else if (instr[0] == "return") {
            if (instr.size() == 2) {
                if (have_reg(instr[1]))
                    insert_into_tigger("a0 = " + var_to_reg[instr[1]]);
                else {
                    string reg1 = alloc_func_reg(instr[1], "a0");
                    if (reg1 != "a0")
                        insert_into_tigger("a0 = " + reg1);
                }
            }
            callee_popstack();
            insert_into_tigger("return");
        }
        // binary operation
        else if (instr.size() == 5 && instr[1] == "=") {
            if (array_var.find(instr[2]) == array_var.end()) {
                string reg1 = alloc_func_reg(instr[2], "t1");
                string reg2;
                if (is_immediate(instr[4]) && (instr[3] == "+" || instr[3] == "<" || instr[3] == "-"))
                    reg2 = instr[4];
                else
                    reg2 = alloc_func_reg(instr[4], "t2");
                string lval;
                if (is_immediate(instr[0]))
                    tiggererror("leftvalue is an immedaite number");
                if (have_reg(instr[0]))
                    lval = var_to_reg[instr[0]];
                else
                    lval = "t3";
                insert_into_tigger(lval + " = " + reg1 + " " + instr[3] + " " + reg2);
                if (lval == "t3")
                    store_reg_to_var("t3", "t1", instr[0]);
            }
            else {
                string reg3;
                if (is_immediate(instr[4]) && (instr[3] == "+" || instr[3] == "<" || instr[3] == "-"))
                    reg3 = instr[4];
                else
                    reg3 = alloc_func_reg(instr[4], "t2");
                string lval;
                if (have_reg(instr[0]))
                    lval = var_to_reg[instr[0]];
                else
                    lval = "t3";
                string array = alloc_arr_elem_pointer(instr[2], lval, reg3);
                if (is_immediate(reg3)) {
                    if (array != lval)
                        insert_into_tigger(lval + " = " + array + " + " + reg3);
                    else
                        insert_into_tigger(lval + " = " + lval + " + " + reg3);
                }
                if (lval == "t3")
                    store_reg_to_var("t3", "t1", instr[0]);
            }
        }
        // assign operation
        else if (instr.size() == 3 && instr[1] == "=") {
            // a[i] = b
            if (is_access(instr[0])) {
                pair<string, string> access = parse_array_access(instr[0]);
                string reg2;
                if (is_immediate(access.second))
                    reg2 = access.second;
                else
                    reg2 = alloc_func_reg(access.second, "t1");
                string array = alloc_arr_elem_pointer(access.first, "t3", reg2);
                string reg3 = alloc_func_reg(instr[2], "t2");
                if (is_immediate(reg2))
                    insert_into_tigger(array + "[" + reg2 + "] = " + reg3);
                else
                    insert_into_tigger(array + "[0] = " + reg3);
            }
            // a = b[j]
            else if (is_access(instr[2])) {
                pair<string, string> access = parse_array_access(instr[2]);
                string reg3;
                if (is_immediate(access.second))
                    reg3 = access.second;
                else
                    reg3 = alloc_func_reg(access.second, "t2");
                string array = alloc_arr_elem_pointer(access.first, "t1", reg3);
                string lval;
                if (have_reg(instr[0]))
                    lval = var_to_reg[instr[0]];
                else
                    lval = "t3";
                if (is_immediate(reg3))
                    insert_into_tigger(lval + " = " + array + "[" + reg3 + "]");
                else
                    insert_into_tigger(lval + " = " + array + "[0]");
                if (lval == "t3")
                    store_reg_to_var("t3", "t1", instr[0]);
            }
            // a = b
            else {
                string reg1;
                if (is_immediate(instr[2]))
                    reg1 = instr[2];
                else
                    reg1 = alloc_func_reg(instr[2], "t1");
                string lval;
                if (have_reg(instr[0]))
                    lval = var_to_reg[instr[0]];
                else
                    lval = "t3";
                insert_into_tigger(lval + " = " + reg1);
                if (lval == "t3")
                    store_reg_to_var("t3", "t1", instr[0]);
            }
        }
        // unary operation
        else if (instr.size() == 4 && instr[1] == "=" && instr[2] != "call") {
            string reg1 = alloc_func_reg(instr[3], "t1");
            string lval;
            if (have_reg(instr[0]))
                lval = var_to_reg[instr[0]];
            else
                lval = "t3";
            insert_into_tigger(lval + " = " + instr[2] + " " + reg1);
            if (lval == "t3")
                store_reg_to_var("t3", "t1", instr[0]);
        }
        // param decl
        else if (instr[0] == "param") {
            if (param_cnt == 0)
                caller_pushstack();
            if (array_var.find(instr[1]) == array_var.end()) {
                string reg = alloc_func_reg(instr[1], param_reg[param_cnt]);
                if (reg != param_reg[param_cnt]) {
                    if (reg[0] == 'a' && stoi(reg.substr(1)) < param_cnt) {
                        int offset = reg_to_offset[reg];
                        insert_into_tigger("load " + to_string(offset) + " " + param_reg[param_cnt]);
                    }
                    else
                        insert_into_tigger(param_reg[param_cnt] + " = " + reg);
                }
            }
            else {
                map<string, int>::iterator it = var_to_offset.find(instr[1]);
                if (it != var_to_offset.end())
                    insert_into_tigger("loadaddr " + to_string(it->second) + " " + param_reg[param_cnt]);
                else {
                    map<string, string>::iterator itv = global_to_v.find(instr[1]);
                    if (itv != global_to_v.end())
                        insert_into_tigger("loadaddr " + itv->second + " " + param_reg[param_cnt]);
                    else
                        tiggererror("array not defined");
                }
            }
            param_cnt++;
        }
        // call function without return value
        else if (instr[0] == "call") {
            if (param_cnt == 0)
                caller_pushstack();
            param_cnt = 0;
            insert_into_tigger("call " + instr[1]);
            caller_popstack();
        }
        // call function with return value
        else if (instr.size() == 4 && instr[2] == "call") {
            if (param_cnt == 0)
                caller_pushstack();
            param_cnt = 0;
            insert_into_tigger("call " + instr[3]);
            insert_into_tigger("t3 = a0");
            caller_popstack();
            string lval;
            if (have_reg(instr[0])) {
                lval = var_to_reg[instr[0]];
                insert_into_tigger(lval + " = t3");
            }
            else
                store_reg_to_var("t3", "t1", instr[0]);
        }
        else
            tiggererror("syntax error");
    }
}

bool TiggerGenerator::reg_used(string reg) {
    return used_reg.find(reg) != used_reg.end();
}

bool TiggerGenerator::have_reg(string var) {
    return var_to_reg.find(var) != var_to_reg.end();
}

void TiggerGenerator::load_var_to_reg(string var, string reg) {
    map<string, int>::iterator it = var_to_offset.find(var);
    if (it != var_to_offset.end())
        insert_into_tigger("load " + to_string(it->second) + " " + reg);
    else {
        map<string, string>::iterator itv = global_to_v.find(var);
        if (itv != global_to_v.end())
            insert_into_tigger("load " + itv->second + " " + reg);
        else
            tiggererror("variable not in stack or heap");
    }
}

void TiggerGenerator::store_reg_to_var(string reg_src, string reg_tmp, string var) {
    map<string, int>::iterator it = var_to_offset.find(var);
    if (it != var_to_offset.end())
        insert_into_tigger("store " + reg_src + " " + to_string(it->second));
    else {
        map<string, string>::iterator itv = global_to_v.find(var);
        if (itv != global_to_v.end()) {
            insert_into_tigger("loadaddr " + itv->second + " " + reg_tmp);
            insert_into_tigger(reg_tmp + "[0] = " + reg_src);
        }
        else
            tiggererror("variable not in stack or heap");
    }
}

pair<string, string> TiggerGenerator::parse_array_access(string access) {
    int pos_l = access.find("[");
    int pos_r = access.find("]");
    if (pos_l == access.npos || pos_r == access.npos)
        tiggererror("undefined array access pattern");
    return make_pair(access.substr(0, pos_l), access.substr(pos_l + 1, pos_r - pos_l - 1));
}

bool TiggerGenerator::is_access(string var) {
    return var.find("[") != var.npos && var.find("]") != var.npos;
}

bool TiggerGenerator::is_immediate(string var) {
    return (var[0] >= '0' && var[0] <= '9') || var[0] == '-';
}

string TiggerGenerator::alloc_func_reg(string var, string default_reg) {
    map<string, string>::iterator it;
    if (is_immediate(var)) {
        if (var == "0")
            return "x0";
        else {
            insert_into_tigger(default_reg + " = " + var);
            return default_reg;
        }
    }
    else {
        if (have_reg(var))
            return var_to_reg[var];
        else {
            load_var_to_reg(var, default_reg);
            return default_reg;
        }
    }
}

string TiggerGenerator::alloc_arr_elem_pointer(string var, string reg_pt, string offset) {
    if (have_reg(var) && var[0] == 'p') {
        if (is_immediate(offset))
            return var_to_reg[var];
        else {
            insert_into_tigger(reg_pt + " = " + var_to_reg[var] + " + " + offset);
            return reg_pt;
        }
    }
    map<string, int>::iterator it = var_to_offset.find(var);
    if (it != var_to_offset.end()) {
        insert_into_tigger("loadaddr " + to_string(it->second) + " " + reg_pt);
        if (offset != "x0" && !is_immediate(offset))
            insert_into_tigger(reg_pt + " = " + reg_pt + " + " + offset);
        return reg_pt;
    }
    else {
        map<string, string>::iterator itv = global_to_v.find(var);
        if (itv != global_to_v.end()) {
            insert_into_tigger("loadaddr " + itv->second + " " + reg_pt);
            if (offset != "x0" && !is_immediate(offset))
                insert_into_tigger(reg_pt + " = " + reg_pt + " + " + offset);
            return reg_pt;
        }
        else {
            tiggererror("array not in stack or heap");
            return reg_pt;
        }
    }
}