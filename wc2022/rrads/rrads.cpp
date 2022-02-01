// #include "/home/jack/cm/debug"
#include <bits/stdc++.h>
using namespace std;

constexpr int N   = 500005;
constexpr int INF = 1000000000;

long long g_ans[N];
int       p[N];

pair<int, int> lines[N];

long long ftree[N];

void modify(int x, long long val)
{
  for (; x < N; x += x & -x)
    ftree[x] += val;
}

long long get(int x)
{
  long long ans = 0;
  for (; x > 0; x -= x & -x)
    ans += ftree[x];
  return ans;
}

template <bool minmax>
struct sgt_t
{
  int _p[N * 4];

  void update(int u, int tl, int tr, int pos, int val)
  {
    if (tl == tr)
    {
      _p[u] = val;
      return;
    }

    int mid = (tl + tr) / 2;
    if (pos <= mid)
      update(u + u, tl, mid, pos, val);
    else
      update(u + u + 1, mid + 1, tr, pos, val);
    if (minmax)
      _p[u] = std::max(_p[u + u], _p[u + u + 1]);
    else
      _p[u] = std::min(_p[u + u], _p[u + u + 1]);
  }

  int get(int u, int tl, int tr, int l, int r)
  {
    if (l <= tl && tr <= r)
      return _p[u];

    int mid = (tl + tr) / 2;
    if (r <= mid)
      return get(u + u, tl, mid, l, r);
    else if (l >= mid + 1)
      return get(u + u + 1, mid + 1, tr, l, r);
    else
    {
      if (minmax)
        return std::max(get(u + u, tl, mid, l, r),
                        get(u + u + 1, mid + 1, tr, l, r));
      else
        return std::min(get(u + u, tl, mid, l, r),
                        get(u + u + 1, mid + 1, tr, l, r));
    }
  }
};

sgt_t<false> mins;
sgt_t<true>  maxs;

set<int> values;

vector<pair<int, long long>> changes;

int v2p[N];

void flex_l(int x, int y, long long &ans, long long pl, int &m)
{
  int _x = x, _y = y;

  long long flex;
  if (y == INF || x == -INF)
    flex = 0;
  else
    flex = abs(v2p[x] - v2p[y]);
  y = min(y, N);
  x = max(x, 0);

  int d;
  if (x + 1 > y - 1)
    d = INF;
  else
    d = mins.get(1, 1, N - 1, x + 1, y - 1);

  long long s = (_x == -INF ? 0 : m - v2p[x]) + (_y == INF ? 0 : m - v2p[y]);
  ans += pl * flex;
  if (d < N && d != INF)
  {
    changes.push_back({d, pl * (s - flex)});
    modify(d, pl * (s - flex));
  }
}

void flex_r(int x, int y, long long &ans, long long pl, int &m)
{
  int _x = x, _y = y;

  long long flex;
  if (y == INF || x == -INF)
    flex = 0;
  else
    flex = abs(v2p[x] - v2p[y]);
  y = min(y, N);
  x = max(x, 0);

  int d;
  if (x + 1 > y - 1)
    d = -INF;
  else
    d = maxs.get(1, 1, N - 1, x + 1, y - 1);

  long long s = (_x == -INF ? 0 : v2p[x] - m) + (_y == INF ? 0 : v2p[y] - m);
  ans += pl * flex;

  if (N - d >= 1 && d != -INF)
  {
    changes.push_back({N - d, pl * (s - flex)});
    modify(N - d, pl * (s - flex));
  }
}

vector<int> id_qs[N];

void dac(int l, int r, const vector<int> &que)
{
  if (l == r)
    return;

  int m = (l + r) >> 1;
  for (int x = m + 1; x <= r; ++x)
    mins.update(1, 1, N - 1, p[x], x);

  long long ans = 0;
  values.clear();
  values.insert(-INF);
  values.insert(INF);
  vector<int> qls, qrs;
  for (int u : que)
  {
    if (lines[u].second <= m)
      qls.push_back(u);
    else if (lines[u].first >= m + 1)
      qrs.push_back(u);
    else
      id_qs[lines[u].first].push_back(u);
  }

  for (int x = m; x >= l; --x)
  {
    v2p[p[x]] = x;
    auto it   = values.lower_bound(p[x]);
    auto prv  = it;
    --prv;
    auto nxt = it;
    flex_l(*prv, *it, ans, -1, m);
    flex_l(*prv, p[x], ans, +1, m);
    flex_l(p[x], *nxt, ans, +1, m);
    values.insert(p[x]);
    for (auto u : id_qs[x])
      g_ans[u] += (ans + get(lines[u].second));
  }

  for (int x = m + 1; x <= r; ++x)
    mins.update(1, 1, N - 1, p[x], INF);
  values.clear();
  values.insert(-INF), values.insert(INF);
  for (int u : que)
    if (lines[u].first <= m && lines[u].second > m)
      id_qs[lines[u].first].clear();
  for (int u : que)
    if (lines[u].first <= m && lines[u].second > m)
      id_qs[lines[u].second].push_back(u);

  for (int x = l; x <= m; ++x)
    maxs.update(1, 1, N - 1, p[x], x);

  while (!changes.empty())
  {
    modify(changes.back().first, -changes.back().second);
    changes.pop_back();
  }
  ans = 0;
  for (int x = m + 1; x <= r; ++x)
  {
    v2p[p[x]] = x;
    auto it   = values.lower_bound(p[x]);
    auto prv  = it;
    --prv;
    auto nxt = it;
    flex_r(*prv, *it, ans, -1, m);
    flex_r(*prv, p[x], ans, +1, m);
    flex_r(p[x], *nxt, ans, +1, m);
    values.insert(p[x]);
    for (auto u : id_qs[x])
      g_ans[u] += (ans + get(N - lines[u].first));
  }

  for (int x = l; x <= m; ++x)
    maxs.update(1, 1, N - 1, p[x], -INF);
  values.clear();

  for (int u : que)
    if (lines[u].first <= m && lines[u].second > m)
      id_qs[lines[u].second].clear();
  while (!changes.empty())
  {
    modify(changes.back().first, -changes.back().second);
    changes.pop_back();
  }

  if (!qls.empty())
    dac(l, m, qls);
  if (!qrs.empty())
    dac(m + 1, r, qrs);
}

int main()
{
  freopen("rrads.in", "r", stdin);
  freopen("rrads.out", "w", stdout);

  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &p[i]);
  for (int i = 0; i < q; ++i)
    scanf("%d%d", &lines[i].first, &lines[i].second);

  for (int x = 1; x < N; ++x)
  {
    maxs.update(1, 1, N - 1, x, -INF);
    mins.update(1, 1, N - 1, x, +INF);
  }

  vector<int> qq(q);
  iota(qq.begin(), qq.end(), 0);
  dac(1, n, qq);

  for (int i = 0; i < q; ++i)
    printf("%lld\n", g_ans[i]);

  return 0;
}
