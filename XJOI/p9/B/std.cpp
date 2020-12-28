#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
typedef long long ll;
typedef std::pair<int, int> pii;
ll
read()
{
  ll x = 0, f = 1;
  char c = getchar();
  while (c < '0' || c > '9') {
    if (c == '-')
      f = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9')
    x = x * 10 + (c - '0'), c = getchar();
  return f * x;
}
ll
max(ll a, ll b)
{
  return a > b ? a : b;
}
int
min(int a, int b)
{
  return a < b ? a : b;
}
void
umax(int& a, int t)
{
  if (a < t)
    a = t;
}
bool
umin(ll& a, ll t)
{
  if (a > t)
    return a = t, 1;
  return 0;
}
/**********/
#define MAXN 100011
struct edge
{
  int v, w, nxt;
} e[MAXN << 1 | 1];
int cnt = 0, last[MAXN];
void
adde(int u, int v, int w)
{
  e[++cnt].v = v, e[cnt].w = w, e[cnt].nxt = last[u], last[u] = cnt;
}

struct node
{
  int u;
  ll dis;
  node(int _u = 0, ll _dis = 0) { u = _u, dis = _dis; }
  bool operator<(const node& you) const { return dis > you.dis; }
};
std::priority_queue<node> q;
ll dis[MAXN];
bool vis[MAXN];
ll
Dij(int n, int k)
{
  while (q.size())
    q.pop();
  memset(dis, 0x3f, sizeof dis), memset(vis, 0, sizeof vis);
  dis[1] = 0, q.push(node(1, 0));
  while (q.size()) {
    node tp = q.top();
    q.pop();
    if (vis[tp.u])
      continue;
    vis[tp.u] = 1;
    if (tp.u == n)
      return tp.dis;
    for (int i = last[tp.u]; i; i = e[i].nxt) {
      int v = e[i].v, w = max(0, e[i].w - k);
      if (umin(dis[v], dis[tp.u] + w))
        q.push(node(v, dis[v]));
    }
  }
  return 0;
}
int
main()
{
  int n = read(), m = read(), k = read();
  for (int i = 1; i <= m; ++i) {
    int u = read(), v = read(), w = read();
    adde(u, v, w), adde(v, u, w);
  }
  ll res = Dij(n, 0);
  for (int x = 1; x <= (m << 1); x += 2) {
    ll cur = Dij(n, e[x].w);
    umin(res, cur + ll(k) * e[x].w);
  }
  printf("%lld\n", res);
  return 0;
}
