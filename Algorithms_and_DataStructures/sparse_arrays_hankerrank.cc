
#include <cmath>
#include <cstdio>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int n, q;
    map<string, int> n_strings;

    cin >> n;
    for (int i = 0; i < n; ++i){
        string s;
        cin >> s;
        
        auto it = n_strings.find(s);
        if (it == n_strings.end()){
            n_strings.insert(map<string, int>::value_type(s, 1));
        }else{
            it->second++;  
        }
    }

    cin >> q;
    for (int i = 0; i < q; ++i){
        string s;
        cin >> s;
        
        auto it = n_strings.find(s);
        if (it != n_strings.end()){
            cout << it->second << endl;
        }else{
            cout << 0 << endl;
        }
    }

    return 0;
}


