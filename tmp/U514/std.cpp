

// Skyqwq
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second
#define mp make_pair

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

template <typename T> bool chkMax(T &x, T y) { return (y > x) ? x = y, 1 : 0; }
template <typename T> bool chkMin(T &x, T y) { return (y < x) ? x = y, 1 : 0; }

template <typename T> void inline read(T &x) {
    int f = 1; x = 0; char s = getchar();
    while (s < '0' || s > '9') { if (s == '-') f = -1; s = getchar(); }
    while (s <= '9' && s >= '0') x = x * 10 + (s ^ 48), s = getchar();
    x *= f;
}

const int N = 255, P = 998244353;

int n, a, b, m, inv[N], f[N][N * N], fact[N * N], infact[N * N];
 
void inline preInv(int n) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++) inv[i] = (P - (LL)P / i) * inv[P % i] % P;
}

int inline power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = (LL)res * a % P;
        a = (LL)a * a % P;
        b >>= 1;
    }
    return res;
}

void inline factPrework(int n) {
    fact[0] = infact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = (LL)fact[i - 1] * i % P;
    infact[n] = power(fact[n], P - 2);
    for (int i = n - 1; i; i--) infact[i] = infact[i + 1] * (i + 1ll) % P;
}


int inline C(int a, int b) {
    if (a < b || a < 0 || b < 0) return 0;
    return (LL)fact[a] * infact[b] % P * infact[a - b] % P;
}

void inline add(int &x, int y) {
    x += y;
    if (x >= P) x -= P;
}

int main() {
    read(n), read(a), read(b);
    m = (n - 1) * b + a - 1;
    preInv(n); factPrework(m);
    f[0][0] = 1;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            if (j - i * b < 0) continue;
            add(f[i][j + 1], 1ll * f[i][j] * inv[n - i] % P);
            add(f[i + 1][j + 1], 1ll * f[i][j] * inv[n - i] % P * C(j - i * b, b - 1) % P);
        }
    }
    int w = 1ll * f[n - 1][m] * fact[n - 1] % P;
    int ans = 1ll * n * (1 + P - w) % P;
    printf("%d\n", ans);
    return 0;
}

