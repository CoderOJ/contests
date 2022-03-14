#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 500005;

std::vector<int> vals;

int    a[N];
int    n;
double k;

void disassociate()
{
  vals.reserve(n);
  for (int i = 0; i < n; i++)
    vals.push_back(a[i]);
  std::sort(vals.begin(), vals.end());
  for (int i = 0; i < n; i++)
    a[i] = static_cast<int>(std::lower_bound(vals.begin(), vals.end(), a[i]) -
                            vals.begin());
}

struct segment_tree
{
  struct node_t
  {
    int min = 0;
    int add = 0;

    node_t() = default;
    node_t(node_t lhs, node_t rhs) : min(std::min(lhs.min, rhs.min)) {}

    void push_add(int det)
    {
      min += det;
      add += det;
    }

    void push_down(node_t &lhs, node_t &rhs)
    {
      if (add != 0)
      {
        lhs.push_add(add);
        rhs.push_add(add);
        add = 0;
      }
    }
  } p[N * 4];

  void add(int u, int l, int r, int ml, int mr, int det)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_add(det);
    }
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (ml < m)
        add(u + u, l, m, ml, mr, det);
      if (mr > m)
        add(u + u + 1, m, r, ml, mr, det);
      p[u] = node_t(p[u + u], p[u + u + 1]);
    }
  }

  node_t query(int u, int l, int r, int ql, int qr)
  {
    if (ql <= l && r <= qr)
      return p[u];
    else
    {
      p[u].push_down(p[u + u], p[u + u + 1]);
      int m = l + (r - l) / 2;
      if (qr <= m)
        return query(u + u, l, m, ql, qr);
      else if (ql >= m)
        return query(u + u + 1, m, r, ql, qr);
      else
        return node_t(query(u + u, l, m, ql, qr),
                      query(u + u + 1, m, r, ql, qr));
    }
  }

  int l, r;

  void add(int ml, int mr, int det)
  {
    add(1, l, r, ml, mr, det);
  }

  node_t query(int ql, int qr)
  {
    return query(1, l, r, ql, qr);
  }

} sgt;

std::vector<int> e[N];

int fa[N];
int size[N];
int ans[N];

int main()
{
  n = sc.next_int();
  k = sc.next_double();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  disassociate();

  sgt.l = 0;
  sgt.r = n;
  for (int i = 0; i < n; i++)
    sgt.add(0, a[i] + 1, 1);

  for (int i = 1; i <= n; i++)
  {
    fa[i] = static_cast<int>(i / k);
    e[fa[i]].push_back(i);
  }
  for (int u = n; u >= 0; u--)
  {
    size[u] = 1;
    for (int v : e[u])
      size[u] += size[v];
  }

  ans[0] = 0;
  sgt.add(0, 1, -n);
  for (int u = 1; u <= n; u++)
  {
    int s = size[u];

    int tl = ans[fa[u]], tr = n - 1;
    while (tl < tr)
    {
      int tm = tl + (tr - tl + 1) / 2;
      if (sgt.query(ans[fa[u]] + 1, tm + 1).min >= s)
        tl = tm;
      else
        tr = tm - 1;
    }

    ans[u] = tl;
    if (tl > ans[fa[u]])
      sgt.add(ans[fa[u]] + 1, tl + 1, -s);
  }

  for (int i = 1; i <= n; i++)
    printf("%d ", vals[ans[i]]);
  puts("");

  return 0;
}
