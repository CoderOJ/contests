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

#define int long long
#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#else
#define see(a) //std::cout << #a << "=" << a << std::endl
#endif
#define foreach(a,b) for (int a=0;a<(int)b.size();a++)

const int MOD = 998244353;
const int N = 1000005;
int sq[N];
int n;

inline void makeSq(int n){
    sq[0] = 1;
    for (int i=1;i<=n;i++){
        sq[i] = sq[i - 1] * i % MOD;
    }
}

inline void init(){
    cin >> n;
    makeSq(n); 
}

inline int power(int b,int o){
    int res = 1;
    while (o){
        if (o & 1){
            (res *= b) %= MOD;
        }
        (b *= b) %= MOD; 
        o >>= 1;
    }
    return res;
}

inline int inv(int n){
    return power(n,MOD - 2);
}

inline int nAr(int n,int r){
    return sq[n] * inv(sq[n - r]) % MOD;
}

inline int calc(int t){
    return nAr(n,t) * ((sq[n - t] - 1 + MOD) % MOD) % MOD; 
}

inline int solve(){
    int res = sq[n];
    for (int i=1;i<n;i++){
        (res += calc(i)) %= MOD;
        if (i % 1000 == 0){
            see(i);
        }
    }
    return res;
}

#undef int
int main(){
#define int long long
    init();
    cout << solve() << endl; 
    return 0;
}
