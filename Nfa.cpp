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

set<string> Nfa :: get_alphabets(){
    return alphabets;
}

set<string> Nfa::get_states(){
    return states;
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

vector<set<string> > Nfa :: get_part_transition(set<string> s){
    vector<set<string> > part;
    set<string> :: iterator it,is;
    set<string> alpha = alphabets;
    for(it = alpha.begin();it!= alpha.end(); ++it){
        set<string> u ;
        for(is = s.begin();is!= s.end();++is){
            set<string> temp = get_transition_states(make_pair(*is,*it));
            u.insert(temp.begin(),temp.end());
        }
        part.push_back(eclose(u));
        u.clear();
    }
    return part;
}

bool Nfa::verify(){
    for (map<pair<string, string>, set<string> >::const_iterator it = transition.begin(); it != transition.end(); ++it) {
       if( ! states.count(it->first.first) ){
            cout<<it->first.first<<" : not a valid state"<<endl;
            return false;
        }
       if(!alphabets.count(it->first.second) && it->first.second != "e") {
            cout<<it->first.second<<" : not a valid alphabet"<<endl;
            return false;
       }
       set<string> :: iterator is;
       set<string> temp = it->second;
       for(is = temp.begin(); is!= temp.end(); ++is){
            if(! states.count(*is)){
                cout<<*is<<" Transition to the invalid state"<<endl;
                return false;
            }
       }
       
       
    }

    if(!states.count(initial_state)){
        cout<<"I :"<<initial_state<<" is not valid state "<<endl;
        return false;
    }
    set<string> ::iterator it;
    set<string> s = get_final_state();
    for(it = s.begin(); it!= s.end();++it ){
        if( ! states.count(*it) ){
            cout<<*it<<" not a valid state"<<endl;
            return false;
        }
    }

    return true;
} 
#endif
