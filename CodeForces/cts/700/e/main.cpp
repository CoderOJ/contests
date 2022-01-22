#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 200005;
constexpr int B = 19;
constexpr int C = 26;

namespace STree
{
struct Node
{
  Node *l, *r;
};
int          g_n;
Node         pool[N * 40];
std::size_t  pool_top = 0;
Node *newNode()
{
  return &pool[pool_top++];
}
void _modify(Node *&u, int l, int r, int p)
{
  if (u == nullptr)
  {
    u = newNode();
  }
  if (l == r)
  {
    return;
  }
  int mid = (l + r) / 2;
  if (p <= mid)
  {
    _modify(u->l, l, mid, p);
  }
  else
  {
    _modify(u->r, mid + 1, r, p);
  }
}
void merge(Node *&u, Node *&v)
{
  if (v == nullptr)
  {
    return;
  }
  if (u == nullptr)
  {
    u = v;
    return;
  }
  Node *c = newNode();
  *c      = *u;
  u       = c;
  merge(u->l, v->l);
  merge(u->r, v->r);
}
bool _query(Node *&u, int sl, int sr, int l, int r)
{
  if (u == nullptr || sl > sr)
  {
    return 0;
  }
  if (sl <= l && r <= sr)
  {
    return 1;
  }
  int mid = (l + r) / 2;
  if (sl > mid)
  {
    return _query(u->r, sl, sr, mid + 1, r);
  }
  else if (sr <= mid)
  {
    return _query(u->l, sl, sr, l, mid);
  }
  else
  {
    return _query(u->l, sl, sr, l, mid) || _query(u->r, sl, sr, mid + 1, r);
  }
}

void init(int _g_n)
{
  g_n = _g_n;
}
void modify(Node *&u, int p)
{
  _modify(u, 0, g_n, p);
}
bool query(Node *&u, int l, int r)
{
  return _query(u, l, r, 0, g_n);
}
} // namespace STree

struct SAM
{
  struct Node
  {
    int              next[C], link = -1, len = 0, pos = 0;
    STree::Node     *pset;
    std::vector<int> e;
    int              fa[B], ans = 0;
    Node()
    {
      memset(next, -1, sizeof(next));
      memset(fa, -1, sizeof(fa));
    }
  };

  static constexpr int root = 0;
  int                  last = root, cnt = root + 1;
  Node                 p[N * 2];

  void insert(std::size_t c)
  {
    int cur    = cnt++;
    p[cur].len = p[last].len + 1;
    p[cur].pos = p[cur].len;
    int pos    = last;
    while (pos != -1 && p[pos].next[c] == -1)
    {
      p[pos].next[c] = cur;
      pos            = p[pos].link;
    }
    if (pos == -1)
    {
      p[cur].link = root;
    }
    else
    {
      int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1)
      {
        p[cur].link = q;
      }
      else
      {
        int clone    = cnt++;
        p[clone]     = p[q];
        p[clone].len = p[pos].len + 1;
        p[clone].pos = -1;
        p[cur].link = p[q].link = clone;
        while (pos != -1 && p[pos].next[c] == q)
        {
          p[pos].next[c] = clone;
          pos            = p[pos].link;
        }
      }
    }
    last = cur;
  }

  void build()
  {
    repa(i, cnt - 1)
    {
      p[p[i].link].e.push_back(i);
    }
  }

  void dfs0(int u = root)
  {
    p[u].fa[0]                                         = p[u].link;
    rep(b, B - 1) if (p[u].fa[b] != -1) p[u].fa[b + 1] = p[p[u].fa[b]].fa[b];
    if (p[u].pos != -1)
    {
      STree::modify(p[u].pset, p[u].pos);
    }
    for (int v : p[u].e)
    {
      dfs0(v);
      STree::merge(p[u].pset, p[v].pset);
    }
    if (p[u].pos == -1)
      p[u].pos = p[p[u].e[0]].pos;
  }

  bool checkDouble(int u, int fa)
  {
    int l = p[u].pos - (p[u].len - p[fa].len);
    int r = p[u].pos - 1;
    return STree::query(p[fa].pset, l, r);
  }

  void dfs(int u = root)
  {
    if (u != root)
    {
      int fa = u;
      repb(i, B - 1, 0) if (p[fa].fa[i] != -1)
      {
        if (!checkDouble(u, p[fa].fa[i]))
        {
          fa = p[fa].fa[i];
        }
      }
      p[u].ans = p[p[fa].link].ans + 1;
    }
    for (int v : p[u].e)
      dfs(v);
  }

  int getAns()
  {
    int ans = 0;
    rep(i, cnt) checkMax(ans, p[i].ans);
    return ans;
  }
} sam;

char s[N];
int  n;

void preInit() {}
void init()
{
  scanf("%d%s", &n, s);
  STree::init(n);
}
void solve()
{
  rep(i, n) sam.insert(s[i] - 'a');
  sam.build();
  sam.dfs0();
  sam.dfs();
  printf("%d\n", sam.getAns());
}
