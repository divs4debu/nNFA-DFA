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



using namespace std;

int main(){
   
    
    NfaParser parser("input.txt");
   parser.parse();
    
}
