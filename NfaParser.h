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
#include "Nfa.h"
#include "Nfa.cpp"

class NfaParser{
private: 
    string address;
    Nfa nfa;
    
    
    
public:
    NfaParser() { }
    NfaParser(string add): address(add){ }
    Nfa parse();
    void set_address(string add);
    set<string> extract(string line);
    map<pair<string,string>, set<string> > make_transition(string line);
    void set_variables(string line);
    
    
};
#endif
