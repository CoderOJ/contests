#include <bits/stdc++.h>
#define maxn 4000005
#define ll long long
using namespace std;
const ll TT = 1e9 + 7;
int n, a[maxn], b[maxn], N, tot, lnk[maxn], nxt[maxn], Nxt[maxn], pos[maxn],
    son[maxn], ans, fa[maxn], cnt[maxn];
inline int read() {
  int ret = 0;
  char ch = getchar();

  while (ch < '0' || ch > '9')
    ch = getchar();

  while (ch <= '9' && ch >= '0')
    ret = ret * 10 + ch - '0', ch = getchar();

  return ret;
}
inline int Getfa(int x) {
  return fa[x] == x ? x : fa[x] = Getfa(fa[x]);
}
inline void add(int x, int y) {
  nxt[++tot] = lnk[x];
  lnk[x] = tot;
  son[tot] = y;
}
inline void dfs(int x) {
  for (int i = lnk[x]; i; i = nxt[i]) {
    if (cnt[son[i]] == cnt[x]) {
      printf("0");
      exit(0);
    } else if (cnt[son[i]])
      continue;

    cnt[son[i]] = cnt[x] ^ 1;
    dfs(son[i]);
  }
}
int main() {
  n = read();

  for (int i = 1; i <= n; i++)
    a[read()] = a[read()] = i;

  n <<= 1;

  for (int i = 1; i <= n; i++)
    fa[i] = i, Nxt[i] = i;

  for (int i = 1; i <= n; i++) {
    if (!pos[a[i]]) {
      b[pos[a[i]] = ++N] = a[i];
      continue;
    }

    for (int j = fa[pos[a[i]]] = Getfa(pos[a[i]] + 1), k; j <= N; j = k) {
      add(b[j], a[i]);
      add(a[i], b[j]);
      k = Getfa(Nxt[j] + 1);
      Nxt[j] = N;
    }
  }

  for (int i = 1; i <= n >> 1; i++)
    if (!cnt[i])
      cnt[i] = 2, ans++, dfs(i);

  ll Ans = 1;

  for (int i = 1; i <= ans; i++)
    Ans = Ans * 2 % TT;

  printf("%lld", Ans);
  return 0;
}