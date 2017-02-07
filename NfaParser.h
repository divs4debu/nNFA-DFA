#ifndef PARSER
#define PARSER

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include "utils.cpp"

class NfaParser{
private: 
    string address;
    const char var_list[6] = {'Q','E','e','D','I','F'};
    map<pair<string,string>, set<string> > transition;
    
    
    map<pair<string,string>, set<string> > get_transition();
    bool is_var(char var);
    set<string> extract(string line);
    map<pair<string,string>, set<string> > make_transition(string line);
    
public:
    NfaParser(){}
    NfaParser(string add): address(add){}
    
    void parse();
    void set_address(string add);
    
    
};
#endif
