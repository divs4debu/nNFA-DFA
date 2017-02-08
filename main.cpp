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

int main(){
   
    
    NfaParser parser("input.txt");
    Nfa nfa = parser.parse();
    set<string> s;
    s.insert("p");
    s.insert("q");
    s.insert("r");
    set<string> eclose = nfa.eclose("p");
    set<string>::iterator i;
    for (i = eclose.begin(); i != eclose.end(); i++) {
        cout << "el :" << *i << endl;
    }

    /*set<string> eclose = parser.get_transition_states(make_pair("q", "e"));
    set<string>::iterator i;
    for (i = eclose.begin(); i != eclose.end(); i++) {
        cout << "el :" << *i << endl;
    }*/
    
}
