#include "genriscv.h"

RiscvGenerator::RiscvGenerator(vector<string> & tigger) {
    split_tigger(tigger);
    proceed();
}

void RiscvGenerator::split_tigger(vector<string> & tigger) {
    for (vector<string>::iterator it = tigger.begin(); it != tigger.end(); it++) {
        string str = *it + " ";
        vector<string> splitted;
        int pos = str.find(" ");
        while (pos != str.npos) {
            splitted.push_back(str.substr(0, pos));
            str = str.substr(pos + 1);
            pos = str.find(" ");
        }
        splitted_tigger.push_back(splitted);
    }
}

void RiscvGenerator::insert_into_riscv(string instruction) {
    riscv.push_back(instruction);
}

void RiscvGenerator::proceed() {
    for (vector<vector<string> >::iterator it = splitted_tigger.begin(); it != splitted_tigger.end(); it++) {
        vector<string> & instr = *it;
        // function begin
        if (instr[0].substr(0, 2) == "f_") {
            string func_name = instr[0].substr(2);
            int int2 = stoi(instr[2].substr(1, instr[2].size() - 2));
            stk = (int2 / 4 + 1) * 16;
            insert_into_riscv("  .text");
            insert_into_riscv("  .align  2");
            insert_into_riscv("  .global " + func_name);
            insert_into_riscv("  .type   " + func_name + ", @function");
            insert_into_riscv(func_name + ":");
            if (is_int12(stk)) {
                insert_into_riscv("  addi sp, sp, -" + to_string(stk));
                insert_into_riscv("  sw ra, " + to_string(stk - 4) + "(sp)");
            }
            else {
                insert_into_riscv("  li t0, -" + to_string(stk));
                insert_into_riscv("  add sp, sp, t0");
                insert_into_riscv("  li t0, " + to_string(stk - 4));
                insert_into_riscv("  add t0, sp, t0");
                insert_into_riscv("  sw ra, 0(t0)");
            }
        }
        // function end
        else if (instr[0] == "end") {
            string func_name = instr[1].substr(2);
            insert_into_riscv("  .size   " + func_name + ", .-" + func_name);
        }
        // global var or array def
        else if (instr[0][0] == 'v' && instr[1] == "=") {
            // global var def
            if (instr.size() == 3) {
                insert_into_riscv("  .global   " + instr[0]);
                insert_into_riscv("  .section  .sdata");
                insert_into_riscv("  .align    2");
                insert_into_riscv("  .type     " + instr[0] + ", @object");
                insert_into_riscv("  .size     " + instr[0] + ", 4");
                insert_into_riscv(instr[0] + ":");
                insert_into_riscv("  .word     " + instr[2]);
            }
            // global array def
            else if (instr.size() == 4)
                insert_into_riscv("  .comm " + instr[0] + ", " + instr[3] + ", 4");
        }
        // goto label
        else if (instr[0] == "goto")
            insert_into_riscv("  j ." + instr[1]);
        // label def
        else if (instr[0].back() == ':')
            insert_into_riscv("." + instr[0]);
        // function call
        else if (instr[0] == "call")
            insert_into_riscv("  call " + instr[1].substr(2));
        // return statement
        else if (instr[0] == "return") {
            if (is_int12(stk)) {
                insert_into_riscv("  lw ra, " + to_string(stk - 4) + "(sp)");
                insert_into_riscv("  addi sp, sp, " + to_string(stk));
                insert_into_riscv("  ret");
            }
            else {
                insert_into_riscv("  li t0, " + to_string(stk - 4));
                insert_into_riscv("  add t0, sp, t0");
                insert_into_riscv("  lw ra, 0(t0)");
                insert_into_riscv("  li t0, " + to_string(stk));
                insert_into_riscv("  add sp, sp, t0");
                insert_into_riscv("  ret");
            }
        }
        // store statement
        else if (instr[0] == "store") {
            int offset = 4 * stoi(instr[2]);
            if (is_int12(offset))
                insert_into_riscv("  sw " + instr[1] + ", " + to_string(offset) + "(sp)");
            else {
                insert_into_riscv("  li t0, " + to_string(offset));
                insert_into_riscv("  add t0, sp, t0");
                insert_into_riscv("  sw " + instr[1] + ", 0(t0)");
            }
        }
        // load statement
        else if (instr[0] == "load") {
            // load global var
            if (instr[1][0] == 'v') {
                insert_into_riscv("  lui " + instr[2] + ", %hi(" + instr[1] + ")");
                insert_into_riscv("  lw " + instr[2] + ", %lo(" + instr[1] + ")(" + instr[2] + ")");
            }
            // load local var
            else {
                int offset = 4 * stoi(instr[1]);
                if (is_int12(offset))
                    insert_into_riscv("  lw " + instr[2] + ", " + to_string(offset) + "(sp)");
                else {
                    insert_into_riscv("  li t0, " + to_string(offset));
                    insert_into_riscv("  add t0, sp, t0");
                    insert_into_riscv("  lw " + instr[2] + ", 0(t0)");
                }
            }
        }
        // loadaddr statement
        else if (instr[0] == "loadaddr") {
            // load global var
            if (instr[1][0] == 'v')
                insert_into_riscv("  la " + instr[2] + ", " + instr[1]);
            // load local var
            else {
                int offset = 4 * stoi(instr[1]);
                if (is_int12(offset))
                    insert_into_riscv("  addi " + instr[2] + ", sp, " + to_string(offset));
                else {
                    insert_into_riscv("  li t0, " + to_string(offset));
                    insert_into_riscv("  add " + instr[2] + ", sp, t0");
                }
            }
        }
        // conditional branch
        else if (instr[0] == "if") {
            string op = instr[2];
            string reg1 = instr[1];
            string reg2 = instr[3];
            string label = instr[5];
            if (op == "<")
                insert_into_riscv("  blt " + reg1 + ", " + reg2 + ", ." + label);
            else if (op == ">")
                insert_into_riscv("  bgt " + reg1 + ", " + reg2 + ", ." + label);
            else if (op == "<=")
                insert_into_riscv("  ble " + reg1 + ", " + reg2 + ", ." + label);
            else if (op == ">=")
                insert_into_riscv("  bge " + reg1 + ", " + reg2 + ", ." + label);
            else if (op == "!=")
                insert_into_riscv("  bne " + reg1 + ", " + reg2 + ", ." + label);
            else if (op == "==")
                insert_into_riscv("  beq " + reg1 + ", " + reg2 + ", ." + label);
            else
                riscverror("undefined relop");
        }
        // binary operation
        else if (instr.size() == 5 && instr[1] == "=") {
            string op = instr[3];
            string reg1 = instr[0];
            string reg2 = instr[2];
            string reg3 = instr[4];
            if (op == "+") {
                // addi
                if (is_immediate(reg3)) {
                    if (is_int12(reg3))
                        insert_into_riscv("  addi " + reg1 + ", " + reg2 + ", " + reg3);
                    else {
                        insert_into_riscv("  li t0, " + reg3);
                        insert_into_riscv("  add " + reg1 + ", " + reg2 + ", t0");
                    }
                }
                // add
                else
                    insert_into_riscv("  add " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (op == "-") {
                // addi -reg3
                if (is_immediate(reg3)) {
                    int addval = -1 * stoi(reg3);
                    if (is_int12(addval))
                        insert_into_riscv("  addi " + reg1 + ", " + reg2 + ", " + to_string(addval));
                    else {
                        insert_into_riscv("  li t0, " + to_string(addval));
                        insert_into_riscv("  add " + reg1 + ", " + reg2 + ", t0");
                    }
                }
                // sub
                else
                    insert_into_riscv("  sub " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (op == "*")
                insert_into_riscv("  mul " + reg1 + ", " + reg2 + ", " + reg3);
            else if (op == "/")
                insert_into_riscv("  div " + reg1 + ", " + reg2 + ", " + reg3);
            else if (op == "%")
                insert_into_riscv("  rem " + reg1 + ", " + reg2 + ", " + reg3);
            else if (op == "<") {
                // slti
                if (is_immediate(reg3)) {
                    if (is_int12(reg3))
                        insert_into_riscv("  slti " + reg1 + ", " + reg2 + ", " + reg3);
                    else {
                        insert_into_riscv("  li t0, " + reg3);
                        insert_into_riscv("  slt " + reg1 + ", " + reg2 + ", t0");
                    }
                }
                // slt
                else
                    insert_into_riscv("  slt " + reg1 + ", " + reg2 + ", " + reg3);
            }
            else if (op == ">")
                insert_into_riscv("  sgt " + reg1 + ", " + reg2 + ", " + reg3);
            else if (op == "<=") {
                insert_into_riscv("  sgt " + reg1 + ", " + reg2 + ", " + reg3);
                insert_into_riscv("  seqz " + reg1 + ", " + reg1);
            }
            else if (op == ">=") {
                insert_into_riscv("  slt " + reg1 + ", " + reg2 + ", " + reg3);
                insert_into_riscv("  seqz " + reg1 + ", " + reg1);
            }
            else if (op == "&&") {
                insert_into_riscv("  snez " + reg1 + ", " + reg2);
                insert_into_riscv("  snez t0, " + reg3);
                insert_into_riscv("  and " + reg1 + ", " + reg1 + ", t0");
            }
            else if (op == "||") {
                insert_into_riscv("  or "+ reg1 + ", " + reg2 + ", " + reg3);
                insert_into_riscv("  snez " + reg1 + ", " + reg1);
            }
            else if (op == "!=") {
                insert_into_riscv("  xor " + reg1 + ", " + reg2 + ", " + reg3);
                insert_into_riscv("  snez " + reg1 + ", " + reg1);
            }
            else if (op == "==") {
                insert_into_riscv("  xor " + reg1 + ", " + reg2 + ", " + reg3);
                insert_into_riscv("  seqz " + reg1 + ", " + reg1);
            }
            else
                riscverror("invalid binary operator");
        }
        // unary operation
        else if (instr.size() == 4 && instr[1] == "=") {
            string op = instr[2];
            string reg1 = instr[0];
            string reg2 = instr[3];
            if (op == "-")
                insert_into_riscv("  neg " + reg1 + ", " + reg2);
            else if (op == "!")
                insert_into_riscv("  seqz " + reg1 + ", " + reg2);
            else
                riscverror("invalid unary operator");
        }
        // assign operation
        else if (instr.size() == 3 && instr[1] == "=") {
            // a[b] = c
            if (is_access(instr[0])) {
                pair<string, string> access = parse_array_access(instr[0]);
                string reg1 = access.first;
                string offset = access.second;
                string reg2 = instr[2];
                if (is_int12(offset))
                    insert_into_riscv("  sw " + reg2 + ", " + offset + "(" + reg1 + ")");
                else {
                    insert_into_riscv("  li t0, " + offset);
                    insert_into_riscv("  add t0, " + reg1 + ", t0");
                    insert_into_riscv("  sw " + reg2 + ", 0(t0)");
                }
            }
            // a = b[c]
            else if (is_access(instr[2])) {
                pair<string, string> access = parse_array_access(instr[2]);
                string reg2 = access.first;
                string offset = access.second;
                string reg1 = instr[0];
                if (is_int12(offset))
                    insert_into_riscv("  lw " + reg1 + ", " + offset + "(" + reg2 + ")");
                else {
                    insert_into_riscv("  li t0, " + offset);
                    insert_into_riscv("  add t0, " + reg2 + ", t0");
                    insert_into_riscv("  lw " + reg1 + ", 0(t0)");
                }
            }
            // a = b
            else {
                if (is_immediate(instr[2]))
                    insert_into_riscv("  li " + instr[0] + ", " + instr[2]);
                else
                    insert_into_riscv("  mv " + instr[0] + ", " + instr[2]);
            }
        }
        else
            riscverror("syntax error");
    }
}

bool RiscvGenerator::is_immediate(string var) {
    return (var[0] >= '0' && var[0] <= '9') || var[0] == '-';
}

bool RiscvGenerator::is_int12(string var) {
    int intval = stoi(var);
    return intval >= -2048 && intval <= 2047;
}

bool RiscvGenerator::is_int12(int intval) {
    return intval >= -2048 && intval <= 2047;
}

pair<string, string> RiscvGenerator::parse_array_access(string access) {
    int pos_l = access.find("[");
    int pos_r = access.find("]");
    if (pos_l == access.npos || pos_r == access.npos)
        riscverror("undefined array access pattern");
    return make_pair(access.substr(0, pos_l), access.substr(pos_l + 1, pos_r - pos_l - 1));
}

bool RiscvGenerator::is_access(string var) {
    return var.find("[") != var.npos && var.find("]") != var.npos;
}

void RiscvGenerator::riscverror(string msg) {
    cerr << "riscv generator: " << msg << endl;
    exit(-1);
}