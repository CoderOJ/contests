#include <cstdio>
#include <cstring>
#include <algorithm>
 
#define clear(a) memset(a, 0, sizeof(a))
 
const int N = 35;
 
int n, a[300005];
int _f[2 * N * N], *f = _f + N * N;
 
void init() {
    clear(a);
    clear(_f);
}
 
int solve() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) scanf("%d", a + i);
    if (n >= 31) return 0;
    if (n == 1) return a[0];
    int sum = 0;
    f[0] = 1;
    for (int i = 0; i < n; ++i) {
        if (f[a[i]]) return 0;
        for (int j = -sum; j <= sum; ++j) f[j - a[i]] |= f[j];
        for (int j = sum; j >= -sum; --j) f[j + a[i]] |= f[j];
        sum += a[i];
    }
    std::sort(a, a + n);
    int ans = a[n - 1];
    do {
        for (int i = 0; i < 1 << n; i += 2) {
            int res = a[0];
            for (int j = 1; j < n; ++j) {
                if (i & 1 << j) {
                    res = res - a[j];
                    if (!res) return 0;
                    if (res < 0) res = -res;
                } else {
                    res = res * a[j];
                    if (res >= 1000000) break;
                }
            }
            if (res < ans) ans = res;
        }
    } while (std::next_permutation(a, a + n));
    return ans;
}
 
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        init();
        printf("%d\n", solve());
    }
    return 0;
}
