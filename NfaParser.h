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
    
    
    
    
public:
    NfaParser() { }
    NfaParser(string add): address(add){ }
    set<string> eclose(string state);
    void parse();
    void set_address(string add);

    map<pair<string,string>, set<string> > get_transition();
    set<string> eclose(set<string> visited, set<string> ecl, string state);
    set<string> extract(string line);
    map<pair<string,string>, set<string> > make_transition(string line);
    set<string> get_transition_states(pair<string, string> transition);
    
    
};
#endif
