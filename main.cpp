#include <iostream>
#include "NfaParser.h"
#include "NfaParser.cpp"
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

void converter(Nfa nfa, set<string> s, set<set<string> >& visited, map<set<string>, vector<set<string> > >& m ){
    if(m.count(s))
        return;
    if(visited.count(s))
        return;
    
    vector<set<string> > v = nfa.get_part_transition(s);
    m[s] = v;
    visited.insert(s);
    for(int i=0; i< v.size();i++){
        converter(nfa, v[i],visited,m);
    }
}
void print_vec(vector<set<string> > &v){
    
    for(int i=0; i< v.size(); i++){
        print(v[i],' ');
    }
    
}
void converter(Nfa nfa){
    set<set<string> > visited;
    set<string> s;
    s.insert(nfa.get_initial_state());
    map<set<string>, vector<set<string> > > m;
    converter(nfa,s,visited,m);
    map<set<string>, vector<set<string> > >::iterator it;
    for(it = m.begin();it!=m.end();it++){
        print(it->first,' ');
        print_vec(it->second);
        cout<<'\n';
        
    }
}

int main(){
   
    
    NfaParser parser("input.txt");
    Nfa nfa = parser.parse();
    set<string> s;
    s.insert("p");
    s.insert("q");
    s.insert("r");
    set<string> eclose = nfa.eclose("p");
    set<string>::iterator i;
    /*for (i = eclose.begin(); i != eclose.end(); i++) {
        cout << "el :" << *i << endl;
    }*/
    converter(nfa);
    
}
