
#include <iostream>
#include <stack>
#include <string>
using namespace std;

void reverseWords(string& s){

    stack<string> st;
    string tmp;

    for(auto it = s.begin(); it != s.end(); ++it){
        char c = *it;
        if (!isspace(c)){
            tmp += c;
        }else{
            if (!tmp.empty()){
                st.push(tmp);
                tmp.clear();
            }
        }        
    }
    if (!tmp.empty()){
        st.push(tmp);
    }

    s.clear();
    while (!st.empty()){
        if (!s.empty()){
            s += " ";
        }
        s += st.top();
        st.pop();
    }
}

int main(int argc, char* argv[]){
    if (argc < 2){   
        cout << "Usage: reversewords <str>" << endl;
        cout << "   Sample: reversewords \"the sky is blue\"" << endl;
        return 0;    
    }   
    string s(argv[1]);
    reverseWords(s);
    cout << s << endl;             

    return 0;
}

