#ifndef UTILS
#define UTILS

#include <set>
#include <vector>
#include <sstream>
using namespace std;

string trim(const string& str,const string& whitespace = " "){
    const int strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return "";

    const int strEnd = str.find_last_not_of(whitespace);
    const int strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

vector<string> split(const string& line, char delim){
    vector<string> split;
    istringstream stream(line);
    string str;
    while(getline(stream,str,delim))
        split.push_back(trim(str));
    return split;
}



bool is_empty(string line){
    if (line.size() == 0) return true;
    return false;
}

void print(set<string> s, const char& c = '\n'){
    cout <<"{";
    for(set<string>::iterator it = s.begin(); it != s.end();++it){
           cout <<*it<<",";
    }
    cout <<"}\t";
    cout<<c;
}

string get_str(set<string> s, const char& c = '\n'){
    stringstream os;
    os <<" {";
    for(set<string>::iterator it = s.begin(); it != s.end();++it){
           os <<*it<<",";
    }
    os <<"}";
    os<<c;

    return os.str();
}


void print(map<pair<string,string>, set<string> > m){
    for (map<pair<string, string>, set<string> >::const_iterator it = m.begin(); it != m.end(); ++it) {
        cout << '(' << it->first.first << ',' << it->first.second << ')';
        print(it->second);
    }
}

set<string> uni (set<string>& s, set<string>& k){
    set<string> u;
    u.insert(s.begin(),s.end());
    u.insert(k.begin(),k.end());
    return u;
}

string get_vec_str(vector<set <string> > v){
    stringstream ss;
    ss << " {";
    for(int i=0; i< v.size();++i){
        ss << get_str(v[i],',');
    }
    ss <<"}";
    return ss.str();
}

#endif
