#include "/home/jack/code/creats/gpl.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/log.h"

#include <bits/stdc++.h>
#define long long long

constexpr int N = 100005;
int n, m, head[N], tot, a[N];
std::pair<int,int> qr[N];
long Ans[N];
int rem[N], Top;
struct Edge
{
  int to, nxt, d;
} e[N << 1];
void
add_edge(int u, int v, int d)
{
  e[++tot] = (Edge){ v, head[u], d };
  head[u] = tot;
}
int vis[N], Siz, rt, col[N], C, siz[N];
std::queue<int> q[N];
int mi[N], st[N], tp, f[N][19];
long sm_p[N], sm_b[N], dist[N];
void
find_rt(int u, int f)
{
  int flg = ((siz[u] << 1) >= Siz);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (vis[v] || v == f)
      continue;
    find_rt(v, u);
    if ((siz[v] << 1) > Siz)
      flg = 0;
  }
  if (flg)
    rt = u;
}
void
find_siz(int u, int f)
{
  siz[u] = 1;
  Siz++;
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (vis[v] || v == f)
      continue;
    find_siz(v, u);
    siz[u] += siz[v];
  }
}
void
dfs(int u, int fa, int len)
{
  int tim = Top;
  col[u] = C;
  f[u][0] = fa;
  dist[u] = dist[fa] + len;
  sm_b[u] = sm_b[fa] + 1ll * mi[fa] * len;
  mi[u] = std::min(a[u], mi[fa]);
  while (tp > 1 && a[u] <= a[st[tp]])
    rem[++Top] = st[tp--];
  sm_p[u] = sm_p[st[tp]] + 1ll * a[u] * (dist[u] - dist[st[tp]]);
  st[++tp] = u;
  for (int i = 1; i < 19; i++)
    f[u][i] = f[f[u][i - 1]][i - 1];
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (v == fa || vis[v])
      continue;
    dfs(v, u, e[i].d);
  }
  tp--;
  while (Top > tim)
    st[++tp] = rem[Top--];
}
void
solve(int x)
{
  rt = -1;
  Siz = 0;
  find_siz(x, 0);
  find_rt(x, 0);
  if (x != rt) {
    while (!q[x].empty())
      q[rt].push(q[x].front()), q[x].pop();
    x = rt;
  }
  mi[x] = a[x];
  dist[x] = 0;
  vis[x] = 1;
  sm_b[x] = sm_p[x] = 0;
  col[x] = 0;
  for (int i = 0; i < 19; i++)
    f[x][i] = 0;
  st[tp = 1] = x;
  Top = 0;
  for (int i = head[x]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (vis[v])
      continue;
    C = v;
    dfs(v, x, e[i].d);
  }
  while (!q[x].empty()) {
    int nw = q[x].front();
    q[x].pop();
    int u = qr[nw].first, v = qr[nw].second;
    if (u == v) {
      Ans[nw] = 0;
      continue;
    }
    if (col[u] == col[v]) {
      q[col[u]].push(nw);
      continue;
    }
    Ans[nw] = sm_p[u];
    int lim = mi[u], t = v;

    for (int k = 18; k >= 0; k--)
      if (f[t][k] && mi[f[t][k]] <= lim)
        t = f[t][k];
    Ans[nw] += 1ll * dist[t] * lim + sm_b[v] - sm_b[t];
  }
  for (int i = head[x]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (vis[v])
      continue;
    solve(v);
  }
}
namespace duipai {
int fa[N], mi[N], len[N];
void
dfs(int u, int f)
{
  fa[u] = f;
  mi[u] = std::min(a[u], mi[f]);
  for (int i = head[u]; i; i = e[i].nxt) {
    int v = e[i].to;
    if (v == f)
      continue;
    len[v] = e[i].d;
    dfs(v, u);
  }
}
long
solve(int u, int v)
{
  mi[0] = std::numeric_limits<int>::max();
  dfs(u, 0);
  long ans = 0;
  while (v != u)
    ans += 1ll * len[v] * mi[fa[v]], v = fa[v];
  return ans;
}
}
int
main()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i < n; i++) {
    int u, v, d;
    scanf("%d%d%d", &u, &v, &d);
    add_edge(u, v, d);
    add_edge(v, u, d);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &qr[i].first, &qr[i].second);
    q[1].push(i);
  }
  solve(1);
  for (int i = 1; i <= m; i++)
    printf("%lld\n", Ans[i]);
  return 0;
}
