#ifndef UTILS
#define UTILS

#include <set>
#include <vector>
#include <sstream>
using namespace std;

vector<string> split(const string& line, char delim){
    vector<string> split;
    istringstream stream(line);
    string str;
    while(getline(stream,str,delim))
        split.push_back(str);
    return split;
}

string trim(const string& str,const string& whitespace = " "){
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == string::npos)
        return "";

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

bool is_empty(string line){
    if (line.size() == 0) return true;
    return false;
}


void print(set<string> s){
    for(set<string>::iterator it = s.begin(); it != s.end();++it){
        cout <<*it<<" ";
    }
    cout<<endl;
}



#endif
