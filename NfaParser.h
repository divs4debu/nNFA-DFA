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
    map<pair<string,string>, set<string> > transition;
    set<string> alphabets;
    set<string> states;
    set<string> final_state;
    string initial_state;
    
    
    
public:
    NfaParser() { }
    NfaParser(string add): address(add){ }
    
    string get_initial_state();
    set<string> get_final_state();
    set<string> eclose(string state);
    void parse();
    void set_address(string add);

    map<pair<string,string>, set<string> > get_transition();
    set<string> eclose(set<string> visited, set<string> ecl, string state);
    set<string> extract(string line);
    map<pair<string,string>, set<string> > make_transition(string line);
    set<string> get_transition_states(pair<string, string> transition);
    void set_variables(string line);
    
    
};
#endif
