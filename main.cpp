#include <iostream>
#include "NfaParser.h"
#include "NfaParser.cpp"
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>
#include "utils.cpp"

#include "Nfa.h"
#include "Nfa.cpp"


using namespace std;

void converter(Nfa nfa, set<string> s, vector<set<string> >& visited, map<set<string>, vector<set<string> > >& m ){
    if(m.count(s))
        return;
    if(find(visited.begin(), visited.end(), s) != visited.end())
        return;
    
    vector<set<string> > v = nfa.get_part_transition(s);
    m[s] = v;
    visited.push_back(s);
    for(int i=0; i< v.size();i++){
        converter(nfa, v[i],visited,m);
    }
}

string converter(Nfa nfa){
    if(!nfa.verify())
        return "";
    string content;

    vector<set<string> > visited;
    set<string> s = nfa.eclose(nfa.get_initial_state());
    map<set<string>, vector<set<string> > > m;
    converter(nfa,s,visited,m);

    set<string> alpha = nfa.get_alphabets();

    content+="Q: "+get_vec_str(visited)+"\n";
    content+="E: "+get_str(alpha)+"\n";
    cout << "Initial State : "; 
    print(visited[0],'\n');
    cout << endl;

    

    vector< set<string> > final;

    for(int j = 0; j < visited.size(); j++){
        set<string> current = visited[j];
        cout << "State : ";
        print(current,'\n');

        vector< set<string> > states = m[current];

        set<string>::iterator is;
        int i =0;
        for(is = alpha.begin();is!= alpha.end();is++){
            cout<<*is<<"->";
            print(states[i++]);
            content+="D("+get_str(current,',')+" "+*is+") : "+get_str(states[i]);
        }
        cout<<'\n';

        for (is = current.begin();is!= current.end();is++) {
            set<string> final_states = nfa.get_final_state();

            if(final_states.count(*is)) {
                final.push_back(current);
                continue;
            }
        }

    }
    content += "\nI : " + get_str(visited[0]);
    cout << "Final States : ";
    content += "F : {";
    for (int i = 0; i < final.size(); ++i) {
        print(final[i], ',');
        content += get_str(final[i], ',');
    }
    content += " }\n";
    cout << endl;

    return content;
}

int main(){
  
    NfaParser parser("input.txt");
    Nfa nfa = parser.parse();
    string dfa;
    dfa = converter(nfa);
    ofstream f;
    f.open("dfa.txt");
    f << dfa;
    f.close();
}
