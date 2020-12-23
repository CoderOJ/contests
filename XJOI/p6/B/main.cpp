#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/
#define long long long

constexpr long INF = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr int N = 2000005;
constexpr int M = 10000005;

int L[M], R[M], n, m;
long a[N], sum1[N], sum2[N];
int pre[N], suf[N], st[N][22], lg[N];
long fl[N], gl[N], fr[N], gr[N];
std::stack<int> stk;

int S, A, B, P, tp;
long lastans = 0;
int
Rand()
{
  S = (S * A % P + (B ^ (tp * lastans))) % P;
  S = S < 0 ? -S : S;
  return S;
}
void
initRand()
{
  S = sc.nextInt();
  A = sc.nextInt();
  B = sc.nextInt();
  P = sc.nextInt();
  tp = sc.nextInt();
}

int
query(int l, int r)
{
  int sz = r - l + 1, S = lg[sz];
  if (a[st[l][S]] > a[st[r - (1 << S) + 1][S]])
    return st[l][S];
  else
    return st[r - (1 << S) + 1][S];
}
long
SUB(int l, int r)
{
  long tmp = sum2[r - 1] - (l == 1 ? 0 : sum2[l - 2]);
  long tmp2 = sum1[r - 1] - (l == 1 ? 0 : sum1[l - 2]);
  long delta = n - l + 2 - (r - l + 1);
  return tmp - delta * tmp2;
}

void
preInit()
{}
void
init()
{
  n = sc.n();
  m = sc.n();
  repa(i, n) a[i] = a[i - 1] + sc.nextInt();
  initRand();
}
void
solve()
{
  for (int i = 1; i <= n; i++)
    sum1[i] = a[i] + sum1[i - 1];
  for (int i = 1; i <= n; i++)
    sum2[i] = a[i] * (n - i + 1) + sum2[i - 1];
  a[0] = INF;
  stk.push(0);
  for (int i = 1; i <= n; i++) {
    while (a[stk.top()] <= a[i])
      suf[stk.top()] = i, stk.pop();
    pre[i] = stk.top();
    stk.push(i);
  }
  for (int i = 1; i <= n; i++)
    st[i][0] = i;
  for (int i = 2; i <= n; i++)
    lg[i] = lg[i >> 1] + 1;
  for (int j = 1; j <= 21; j++) {
    for (int i = 1; i <= n; i++) {
      if (i + (1 << j) - 1 > n)
        break;
      int to = i + (1 << (j - 1));
      if (a[st[i][j - 1]] > a[st[to][j - 1]])
        st[i][j] = st[i][j - 1];
      else
        st[i][j] = st[to][j - 1];
    }
  }
  for (int i = 1; i <= n; i++) {
    fr[i] = a[i] * (i - pre[i]) + fr[pre[i]];
    gr[i] = gr[i - 1] + fr[i];
  }
  for (int i = n; i >= 1; i--) {
    fl[i] = a[i] * (suf[i] - i) + fl[suf[i]];
    gl[i] = gl[i + 1] + fl[i];
  }
  long ans = 0;
  for (int i = 1; i <= m; i++) {
    L[i] = Rand() % n + 1, R[i] = Rand() % n + 1;
    if (L[i] > R[i]) std::swap(L[i], R[i]);
    int pos = query(L[i], R[i]);
    int l = L[i], r = R[i];
    lastans = 1ll * (pos - l + 1) * (r - pos + 1) * a[pos];
    lastans += gr[r] - gr[pos] - fr[pos] * (r - pos);
    lastans += gl[l] - gl[pos] - fl[pos] * (pos - l);
    lastans -= SUB(l, r);
    ans = (ans + (lastans % MOD + MOD) % MOD) % MOD;
  }
  printf("%lld\n", ans);
}
