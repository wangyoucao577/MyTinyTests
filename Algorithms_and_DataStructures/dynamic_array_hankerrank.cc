#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    typedef vector<int> Seq;
    vector<Seq> seqList;

    int lastAns {0}; 

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; ++i){
        seqList.push_back(Seq());
    }

    for (int i = 0; i < q; ++i){
        int act, x, y;
        cin >> act >> x >> y;

        int seq_index = (x ^ lastAns) % n;
        if (act == 1){
            seqList[seq_index].push_back(y);
        }
        else if (act == 2){
            const auto& seq = seqList[seq_index];
            lastAns = seq[y % seq.size()];
            cout << lastAns << endl;
        }
        else{
            //ignore
        }
    }

    return 0;
}

