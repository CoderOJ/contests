#include <bits/stdc++.h>

#define rep(i,n) for (int i=0;i<n;++i)
#define repa(i,n) for (int i=1;i<=n;++i)

#define int long long

constexpr int N = 200505;
int a[N], pre[N];
int n, k;


signed main() {
  scanf("%lld%lld", &n, &k); n++;
  rep (i,n) scanf("%lld", &a[i]);

  int lz = 0;
  {
    int rem = 0;
    rep (i,n + 100) {
      if (rem & 1) {
        lz = i; break; }
      pre[i] = rem / 2;
      rem /= 2;
      rem += a[i]; }
  }

  int ans = 0;
  {
    int rem = 0;
    for (int i=n-1; i>=0; i--) {
      if (std::abs(rem) > (int)(1e17)) { break; }
      if (i < lz) {
        int nv = - rem*2 - pre[i];
        if (std::abs(nv) <= k && (i!=n-1 || nv!=0)) {
          ans++; } } 
      rem = rem * 2 + a[i];
    }
  }

  printf("%lld\n", ans);

  return 0;
}
