#include <bits/stdc++.h>
using namespace std;

int bits(int u) {
    int res = 0;
    while (u) {
        res += u & 1;
        u >>= 1;
    }
    return res;
}

int get(int u) {
    int ans = 0;
    for (int i=0;i<=u;i++) ans += !(bits(i) & 1);
    return ans;
}

int main() {
    for (int i=0;i<100;i++) cout << get(i) << endl;
    return 0;
}
