#include "geneeyore.h"

EeyoreGenerator::EeyoreGenerator(vector<string> & _instructions) {
    instructions = _instructions;
    proceed();
}

void EeyoreGenerator::insert_into_eeyore(string & instruction) {
    eeyore.push_back(instruction);
}

void EeyoreGenerator::insert_into_eeyore(vector<string> & s) {
    eeyore.insert(eeyore.end(), s.begin(), s.end());
}

bool EeyoreGenerator::is_var_def(string & s) {
    return s.substr(0, 3) == "var";
}

bool EeyoreGenerator::is_func_header(string & s) {
    return s.substr(0, 2) == "f_";
}

bool EeyoreGenerator::is_func_end(string & s) {
    return s.substr(0, 6) == "end f_";
}

void EeyoreGenerator::proceed() {
    bool global = true;
    vector<string> global_vardefs;
    vector<string> global_varinits;
    vector<string> insert_into_main;
    for (vector<string>::iterator it = instructions.begin(); it != instructions.end(); it++) {
        if (*it == "//inserttomain") {
            it++;
            insert_into_main.push_back(*it);
        }
        else if (is_func_header(*it))
            global = false;
        else if (is_func_end(*it))
            global = true;
        else if (global) {
            if (is_var_def(*it))
                global_vardefs.push_back(*it);
            else
                global_varinits.push_back(*it);
        }
    }
    insert_into_eeyore(global_vardefs);
    for (vector<string>::iterator it = instructions.begin(); it != instructions.end(); it++) {
        if (is_func_header(*it)) {
            insert_into_eeyore(*it);
            bool is_main = (it->substr(0, 7) == "f_main ");
            vector<string> vardefs;
            vector<string> others;
            do {
                it++;
                if (is_var_def(*it))
                    vardefs.push_back(*it);
                else
                    others.push_back(*it);
            } while(!is_func_end(*it));
            if (is_main)
                vardefs.insert(vardefs.end(), insert_into_main.begin(), insert_into_main.end());
            set<string> s(vardefs.begin(), vardefs.end());
            vector<string> clean_vardefs(s.begin(), s.end());
            insert_into_eeyore(clean_vardefs);
            if (is_main)
                insert_into_eeyore(global_varinits);
            insert_into_eeyore(others);
        }
    }
}