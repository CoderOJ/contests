#define MULTIPLE_TEST_CASES_WITH_T
#include "/home/jack/code/creats/gpl.h"
#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

#ifdef ENABLE_LL
#define int long long
#endif

/** My code begins here **/

const int MOD = 998244353;
const int N = 65536;
int a[N], n;

inline int
Add(int a, int b)
{
  a += b;
  return a>=MOD ? a-MOD : a;
}

inline void
add(int& a, int b)
{
  a += b;
  a = a>=MOD ? a-MOD : a;
}

namespace Math {
inline int
power(int a, int b)
{
  int r = 1;
  for (; b; b >>= 1) {
    if (b & 1)
      r = 1ll * r * a % MOD;
    a = 1ll * a * a % MOD;
  }
  return r;
}
inline int
inv(int a)
{
  return power(a, MOD - 2);
}
} // namespace Math

namespace ntt {
inline int
get_2(int len)
{
  int res = 0, tr = 1;
  while (tr < len) {
    tr <<= 1;
    res++;
  }
  return res;
}
void
dft(int a[], int n)
{
  static int rev[N * 2], rev_n = -1;
  static int w[N * 2], w_n = -1;
  if (rev_n != n) {
    rev_n = n;
    rev[0] = 0;
    int shift_width = get_2(n) - 1;
    for (int i = 1; i < n; ++i)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << shift_width);
  }
  if (w_n < n) {
    w_n = n;
    for (int l = 1; l < n; l <<= 1) {
      int cw = Math::power(3, (MOD - 1) / l / 2), pw = 1;
      for (int j = 0; j < l; ++ j) {
        w[l+j] = pw;
        pw = 1ll * pw * cw % MOD;
      }
    }
  }
  for (int i = 0; i < n; ++i)
    if (i < rev[i])
      std::swap(a[i], a[rev[i]]);
  for (int l = 1; l < n; l <<= 1) {
    int step = l << 1;
    for (int i = 0; i < n; i += step) {
      for (int j = 0; j < l; ++j) {
        int b = 1ll * a[l + i + j] * w[l+j] % MOD;
        a[l+i+j] = Add(a[i+j], MOD-b);
        add(a[i + j], b);
      }
    }
  }
}
void
idft(int a[], int n)
{
  std::reverse(a + 1, a + n);
  dft(a, n);
  int n_inv = Math::inv(n);
  for (int i = 0; i < n; ++i)
    a[i] = 1ll * a[i] * n_inv % MOD;
}
void mul(int a[], int b[], int n, int m) {
  int l = std::max( get_2(n), get_2(m) ) + 1;
  int len = 1 << l;
  for (int i=n; i<len; ++i) { a[i] = 0; }
  for (int i=m; i<len; ++i) { b[i] = 0; }
  dft(a, len);
  dft(b, len);
  for (int i = 0; i < len; ++ i)
    a[i] = 1ll * a[i] * b[i] % MOD;
  idft(a, len);
}
} // namespace ntt

int f[N + 5];

void
cdq(int l, int r)
{
  if (l == r) {
    add(f[l], 1ll * f[l-1] * (l-1) % MOD);
    return;
  }
  int mid = (l + r) / 2;
  cdq(l, mid);
  int len = mid - l + 1;
  static int _a[N*2+10], _b[N*2+10];
  for (int i = l; i <= mid; ++ i) {
    _a[i - l] = 1ll * f[i] * (i-1) % MOD;
    _b[i - l] = f[i];
  }
  ntt::mul(_a, _b, len, len);
  for (int i = std::max(l << 1, mid + 1); i <= r; ++ i) {
    add(f[i], _a[i - (l<<1)]);
  }
  if (l != 2) {
    int d = std::min(l - 1, r - l);
    for (int i = 2; i <= d; ++ i)
      _a[i-2] = f[i];
    for (int i = l; i <= mid; ++ i)
      _b[i-l] = f[i];
    ntt::mul(_a, _b, d-1, mid-l+1);
    for (int i = std::max(l+2, mid+1); i<=r; ++i)
      add(f[i], 1ll * _a[i-l-2] * (i-2) % MOD);
  }
  cdq(mid+1, r);
}

void
preInit()
{
f[0] = 1; f[1] = 2;
}

void
init()
{
  if (n == 0) {
    n = sc.n();
    if (n <= 1000) {
#include "./tab.h"
    } else {
      cdq(2, n);
    }
  }
  rep(i, n) a[i] = sc.n();
}

void
solve()
{
  if (a[0] != 1 || a[n-1] != n) {
    puts("0");
    return;
  }
  typedef std::pair<int, int> Inter;
  typedef std::pair<Inter, int> Val;
  std::stack <Val> st;
  rep (i,n) {
    Inter pos(i-a[i]+1, i);
    int pans = 1;
    int cnt = 0;
    while (!st.empty() && st.top().first.first >= pos.first) {
      pans = 1ll * pans * st.top().second % MOD;
      st.pop();
      cnt++;
    }
    if (!st.empty() && st.top().first.second >= pos.first) {
      puts("0");
      return;
    }
    pans = 1ll * pans * f[cnt] % MOD;
    st.push( Val(pos, pans) );
  }
  printf("%d\n", st.top().second);
}
