#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

#define long long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)

char s[50];

void init(){
    cin >> s;
}

int main(){
    init();
    string res;
    int n = strlen(s);
    int start = (n - 1) / 2;
    res = s[start];
    int l = start ,r = start;
    while ((l >= 0) || (r < n)){
        l--;r++;
        if (r <  n) res = res + s[r];
        if (l >= 0) res = res + s[l];
    }
    cout << res << endl;
    return 0;
}
