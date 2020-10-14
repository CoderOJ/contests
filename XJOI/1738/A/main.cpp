#include <bits/stdc++.h>
#include "./bigint-10-2-src/bigInt.h"
#include "./bigint-10-2-src/bigInt.cpp"
using namespace std;

typedef BigInt::Rossi Int;

int main() {
    string _a,_b; cin >> _a >> _b;
    Int a(_a,BigInt::DEC_DIGIT), b(_b, BigInt::DEC_DIGIT);
    Int c = a*b;
    cout << c.toStrDec() << endl;
    return 0;
}
