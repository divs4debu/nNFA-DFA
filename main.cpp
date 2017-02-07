#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include "utils.cpp"

const char var_list[6] = {'Q','E','e','D','I','F'};


using namespace std;

bool is_var(char var){
    for(int i=0; i< 6;i++){
        if(var == var_list[i]) return true;
    }
    return false;
}


set<string> extract(string line){
    set<string> vars;
    size_t start = line.find_first_of('{');
    size_t end = line.find_last_of('}');
    if(start == string::npos || end == string::npos) return vars;   // throw exception later
    string sub = line.substr(start+1, end-start-1);
    vector<string> spli = split(sub, ',');
    vars.insert(spli.begin(), spli.end());
    return vars;
}



map<pair<string,string>, set<string> > make_transition(string line){
    map<pair<string,string>, set<string> > transition;
    size_t start = line.find_first_of('(');
    size_t end = line.find_last_of(')');
    
    if(start == string::npos || end == string::npos) return transition;
    
    string sub = line.substr(start+1,end-start-1);
    vector<string> tuple  = split(sub, ',');
    pair<string,string> key(tuple[0],trim(tuple[1]));
    transition.insert(make_pair(key, extract(line)));
    //cout<<transition<<endl;
    return transition;
}




int main(){
    ifstream file("input.txt");
    string line;
    map<pair<string,string>, set<string> > trans;
    
    char var;
    while(getline(file,line)){
        istringstream stream(line);
        stream >> var;
        set<string> founds;
        if(!line.empty()){
            
            //founds = extract(line);
            if(var == 'D'){
                map<pair<string,string>, set<string> > temp;
                temp = make_transition(line);
                trans.insert(temp.begin(),temp.end());
                for(map<pair<string,string>, set<string> >::const_iterator it = trans.begin();it != trans.end(); ++it){
                    cout << '('<<it->first.first<<','<<it->first.second<<')';
                    print(it->second);
                }
            }
        }
        cout<<"\n";
    }
    //pair<string,string> p("p","a");
    //cout<<trans.count(p)<<endl;
}
