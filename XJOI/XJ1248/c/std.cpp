#include<bits/stdc++.h>
#define LL long long
#define pii pair<int, int>
using namespace std;
const int N = 1e5 + 10;
const int mod = 998244353;
 
template<typename T> void read(T &x) {
    char c = getchar(); int f = 0;
    while (c < '0' || c > '9') f |= (c == '-'),  c = getchar();
    for (x = 0; c >= '0' && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + (c ^ '0');
    if (f) x = -x;
}
 
LL n, k;
LL f[N], g[N], T[N], D[N];
 
LL Qpow(LL x, int p) {
    LL ans = 1;
    while (p) {
        if (p & 1) ans = 1LL * ans * x % mod;
        x = 1LL * x * x % mod;
        p >>= 1;
    }
    return ans;
}
 
LL Inv(LL x) {
    return Qpow(x, mod - 2);
}
 
int main() {
    read(n); read(k);
    if (k != 2) return 0;
    f[0] = g[0] = T[0] = 1;
    for (LL i = 1; i <= n; ++i) {
        f[i] = (2 * i * g[i - 1] % mod + 2 * T[i - 1]) % mod * Inv(i * i % mod) % mod;
        g[i] = (g[i - 1] + f[i]) % mod;
        T[i] = ((i + 4) * Inv(i) % mod * T[i - 1] % mod + f[i]) % mod;
    }
    cout << f[n] << endl;
    return 0;
}
