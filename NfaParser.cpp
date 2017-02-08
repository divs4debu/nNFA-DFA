#include "NfaParser.h"
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

using namespace std;


set<string> NfaParser:: extract(string line) {
    set<string> vars;
    size_t start = line.find_first_of('{');
    size_t end = line.find_last_of('}');
    if (start == string::npos || end == string::npos) return vars;  // throw exception later
    string sub = line.substr(start + 1, end - start - 1);
    vector<string> spli = split(trim(sub), ',');
    vars.insert(spli.begin(), spli.end());
    return vars;
}

map<pair<string, string>, set<string> > NfaParser:: make_transition(string line) {
    map<pair<string, string>, set<string> > transition;
    size_t start = line.find_first_of('(');
    size_t end = line.find_last_of(')');

    if (start == string::npos || end == string::npos) return transition;

    string sub = line.substr(start + 1, end - start - 1);
    vector<string> tuple  = split(sub, ',');
    pair<string, string> key(trim(tuple[0]), trim(tuple[1]));

    transition.insert(make_pair(key, extract(line)));
    return transition;
}

Nfa NfaParser :: parse() {
    ifstream file(address.c_str());
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            set_variables(line);
        }
    }
    //print(nfa.get_transition());
    //print(nfa.get_final_state());
    return nfa;
    
}


void NfaParser :: set_variables(string line){
    char var;
    istringstream stream(line);
    stream >> var;
    
    switch(var){
        case 'Q':{
            nfa.set_states(extract(line));
            break;
        }
        case 'D':{
            map<pair<string, string>, set<string> > temp;
            temp = make_transition(line);
            nfa.set_transition(temp);
            break;
        }
        case 'F':{
            nfa.set_final_state(extract(line));
            break;
        }
        case 'I':{
            set<string> temp = extract(line);
            set<string>::iterator it = temp.begin();
            nfa.set_initial_state(*it);
            break;
        }
        case 'E':{
            nfa.set_alphabets(extract(line));
        }
    }
    
}

