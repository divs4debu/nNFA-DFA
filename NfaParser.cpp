#include "NfaParser.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include "utils.cpp"

using namespace std;


set<string> NfaParser:: extract(string line) {
    set<string> vars;
    size_t start = line.find_first_of('{');
    size_t end = line.find_last_of('}');
    if (start == string::npos || end == string::npos) return vars;  // throw exception later
    string sub = line.substr(start + 1, end - start - 1);
    vector<string> spli = split(sub, ',');
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
    pair<string, string> key(tuple[0], trim(tuple[1]));

    transition.insert(make_pair(key, extract(line)));
    return transition;
}

void NfaParser :: parse() {
    ifstream file(address.c_str());
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            set_variables(line);
        }
    }
    print(transition);
    print(get_final_state());
    
}

set<string> NfaParser::get_transition_states(pair<string, string> transition) {
    return this->transition[transition];
}

set<string> NfaParser :: eclose(set<string> visited, set<string> ecl, string state){
    if(visited.count(state))
        return ecl;

    ecl.insert(state);

    set<string> transition = get_transition_states(make_pair(trim(state), "e"));
    ecl.insert(transition.begin(), transition.end());

    set<string>::iterator it;
    for(it = transition.begin(); it != transition.end(); it++) {

        set<string> recur = eclose(visited, ecl, *it);
        ecl.insert(recur.begin(), recur.end());
    }

    visited.insert(state);

    return ecl;
}

set<string> NfaParser :: eclose(string state) {
    set<string> visited, ecl;

    return eclose(visited, ecl, state);
}

void NfaParser :: set_variables(string line){
    char var;
    istringstream stream(line);
    stream >> var;
    
    switch(var){
        case 'Q':{
            states = extract(line);
            break;
        }
        case 'D':{
            map<pair<string, string>, set<string> > temp;
            temp = make_transition(line);
            transition.insert(temp.begin(), temp.end());
            break;
        }
        case 'F':{
            final_state = extract(line);
            break;
        }
        case 'I':{
            set<string> temp = extract(line);
            set<string>::iterator it = temp.begin();
            initial_state = *it;
            break;
        }
    }
    
}

string NfaParser :: get_initial_state(){
    return initial_state;
}

set<string> NfaParser :: get_final_state(){ return final_state;}
