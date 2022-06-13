#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t
{
  int ch[2], sum;
};

struct sgt_t
{
  node_t t[20000000];
  int    node_cnt;

  void init()
  {
    node_cnt = 0;
  }

  int new_node()
  {
    int p      = ++node_cnt;
    t[p].ch[0] = t[p].ch[1] = t[p].sum = 0;
    return p;
  }

  void insert(int &p, int64_t l, int64_t r, int64_t pos)
  {
    if (!p)
      p = new_node();

    t[p].sum++;

    if (l == r)
      return;

    int64_t mid = (l + r) >> 1;

    if (pos <= mid)
      insert(t[p].ch[0], l, mid, pos);
    else
      insert(t[p].ch[1], mid + 1, r, pos);
  }

  int query(int p, int64_t l, int64_t r, int64_t ql, int64_t qr)
  {
    if (!p)
      return 0;
    if (ql <= l && r <= qr)
      return t[p].sum;

    int64_t mid = (l + r) >> 1;
    int     ret = 0;

    if (ql <= mid)
      ret = query(t[p].ch[0], l, mid, ql, qr);
    if (qr > mid)
      ret += query(t[p].ch[1], mid + 1, r, ql, qr);

    return ret;
  }

  int merge(int x, int y)
  {
    if (!x || !y)
      return x | y;

    t[x].sum += t[y].sum;
    t[x].ch[0] = merge(t[x].ch[0], t[y].ch[0]);
    t[x].ch[1] = merge(t[x].ch[1], t[y].ch[1]);
    return x;
  }
};

sgt_t T;

CONSTRAINT(N, 200005, 205)

std::vector<int> stapple[N], t[N], pt1;
int              rt[N], bans, bane;

int n, m, l, c, q;
int a[N], b[N], fa[N], d[N];

std::vector<std::pair<int, int64_t>> query[N];

int64_t dep[N], ans[N];
bool    vis[N];
void    dfs(int np)
{
  vis[np] = true;
  pt1.push_back(np);
  for (int &x : stapple[np])
    T.insert(rt[np], 0, 2e18, x + dep[np]);
  for (int &x : t[np])
    if (np != bans || x != bane)
      dep[x] = dep[np] + d[x], dfs(x), rt[np] = T.merge(rt[np], rt[x]);
  for (auto &x : query[np])
    ans[x.first] = T.query(rt[np], 0, 2e18, dep[np], dep[np] + x.second);
}

void solve(int p)
{
  T.init();
  int cx = p;
  pt1.clear();

  while (!vis[cx])
  {
    vis[cx] = true;
    cx      = fa[cx];
  }

  bans = fa[cx], bane = cx, dfs(cx);
  int64_t totlen = dep[bans] + d[cx];
  T.init();
  std::vector<int64_t> cur;

  for (int &x : pt1)
    for (int &y : stapple[x])
      cur.push_back(y + dep[x] + d[cx] + dep[bans]);

  std::sort(cur.begin(), cur.end());
  std::vector<std::pair<int64_t, int64_t>> c2;

  for (int i = bans; i; i = fa[i])
  {
    for (auto &t : query[i])
      c2.emplace_back(t.second + totlen + dep[i], t.first);

    if (i == bane)
      break;
  }

  std::sort(c2.begin(), c2.end());
  int64_t vl = 0;
  int     R  = 0;

  for (int i = 0, j = 0; i < (int)c2.size(); i++)
  {
    while (j < (int)cur.size() && cur[j] <= c2[i].first)
    {
      T.insert(R, 0, totlen, cur[j] % totlen);
      vl += cur[j] / totlen, j++;
    }

    ans[c2[i].second] -= vl;
    ans[c2[i].second] += (int64_t)(c2[i].first / totlen) *
                         T.query(R, 0, totlen, 0, c2[i].first % totlen);
    ans[c2[i].second] +=
        (int64_t)(c2[i].first / totlen - 1) *
        T.query(R, 0, totlen, c2[i].first % totlen + 1, totlen);
  }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  l = sc.next_int();
  c = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    a[i] = sc.next_int();
    a[i] = l - 1 - a[i];
  }
  for (int i = 1; i <= m; i++)
  {
    b[i] = sc.next_int();
    b[i] = l - 1 - b[i];
  }
  std::reverse(a + 1, a + n + 1);
  std::reverse(b + 1, b + m + 1);

  for (int i = 1; i <= n; i++)
  {
    int next = (a[i] + c) % l;
    if (next > a[n])
    {
      fa[i] = 1;
      d[i]  = l + a[1] - next + c;
    }
    else
    {
      fa[i] = static_cast<int>(std::lower_bound(a + 1, a + n + 1, next) - a);
      d[i]  = a[fa[i]] - next + c;
    }
  }

  for (int i = 1; i <= m; i++)
  {
    if (b[i] > a[n])
      stapple[1].push_back(a[1] + l - b[i]);
    else
    {
      int cur = static_cast<int>(std::lower_bound(a + 1, a + n + 1, b[i]) - a);
      stapple[cur].push_back(a[cur] - b[i]);
    }
  }

  q = sc.next_int();

  for (int i = 1; i <= q; i++)
  {
    int     p = sc.next_int();
    int64_t T = sc.next_long();
    query[n + 1 - p].emplace_back(i, T);
  }

  for (int i = 1; i <= n; i++)
    t[fa[i]].push_back(i);

  for (int i = 1; i <= n; i++)
    if (!vis[i])
      solve(i);

  for (int i = 1; i <= q; i++)
    std::cout << ans[i] << std::endl;

  return 0;
}
