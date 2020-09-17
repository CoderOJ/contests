#include "combo.h"
#include <bits/stdc++.h>
using namespace std;
char ch[4];

std::string guess_sequence(int N) {
    ch[0] = 'A'; ch[1] = 'B'; ch[2] = 'X'; ch[3] = 'Y';
    if ( press("AB") ) {
        if (press("B")) swap (ch[0], ch[1]);
    }else {
        if (press("X")) swap (ch[2], ch[0]);
        else            swap (ch[3], ch[0]);
    }
    string res;
    res.push_back( ch[0] );
    for (int i=2;i<N;i++) {
        string tr;
        tr += res; tr.push_back(ch[1]);
        tr += res; tr.push_back(ch[2]); tr.push_back(ch[1]);
        tr += res; tr.push_back(ch[2]); tr.push_back(ch[2]);
        tr += res; tr.push_back(ch[2]); tr.push_back(ch[3]);
        int x = press(tr);
        if (x == i) res += ch[1];
        else if (x == i + 1) res += ch[2];
        else res += ch[3];
    }
    if (N != 1) {
        string tr;
        tr = res; tr.push_back(ch[1]); int x = press(tr);
        if (x == N) res.push_back(ch[1]);
        else {
            tr = res; tr.push_back(ch[2]); int x = press(tr);
            if (x == N) res.push_back(ch[2]);
            else res.push_back(ch[3]);
        }
    }
    return res;
}
