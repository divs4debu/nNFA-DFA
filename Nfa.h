#ifndef NFA
#define NFA

class Nfa{
private:
    map<pair<string,string>, set<string> > transition;
    set<string> alphabets;
    set<string> states;
    set<string> final_state;
    string initial_state;
    set<string> eclose(set<string> visited, set<string> ecl, string state);
public:
    //GETTERS
    map<pair<string,string>, set<string> > get_transition();
    string get_initial_state();
    set<string> get_final_state();
    set<string> get_alphabets();
    set<string> get_states();
    set<string> get_transition_states(pair<string, string> transition);

    set<string> eclose(string state);
    
    //SETTERS
    void set_transition(map<pair<string,string>, set<string> > m);
    void set_initial_state(string s);
    void set_final_state(set<string> s);
    void set_alphabets(set<string> s);
    void set_states(set<string> s);
};

#endif
