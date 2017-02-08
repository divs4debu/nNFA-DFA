#ifndef NFA_CPP
#define NFA_CPP

#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include "utils.cpp"
#include "Nfa.h"
using namespace std;

string Nfa :: get_initial_state(){
    return initial_state;
}

set<string> Nfa :: eclose(set<string> visited, set<string> ecl, string state){
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

set<string> Nfa :: eclose(string state) {
    set<string> visited, ecl;

    return eclose(visited, ecl, state);
}
set<string> Nfa :: get_final_state(){
    return final_state;
}

set<string> Nfa::get_transition_states(pair<string, string> transition) {
    return this->transition[transition];
}

map<pair<string,string>, set<string> > Nfa:: get_transition(){
    return transition;
}

void Nfa:: set_transition(map<pair<string,string>, set<string> > m){
    transition.insert(m.begin(), m.end());
}
void Nfa :: set_initial_state(string s){
    initial_state = s;
}
void Nfa :: set_final_state(set<string> s){
    final_state = s;
}
void Nfa :: set_alphabets(set<string> s){
    alphabets = s;
}
void Nfa :: set_states(set<string> s){
    states = s;
}

set<string> Nfa:: eclose(set<string> s){
    set<string> ecl;
    set<string> ::iterator it;
    for(it=s.begin();it!=s.end();it++){
       set<string> temp = eclose(*it);
       ecl.insert(temp.begin(),temp.end());
    }
    return ecl;
}
#endif
