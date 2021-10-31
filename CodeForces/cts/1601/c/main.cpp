#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

struct ftree_t
{
  std::vector<int> a;
  int n;

  ftree_t(int n) : a(n + 2), n(n + 2)
  {
  }
  void modify(int pos, int det)
  {
    pos += 2;
    for (; pos < n; pos += pos & (-pos))
      a[pos] += det;
  }
  int query(int pos)
  {
    pos += 2;
    int res = 0;
    for (; pos; pos -= pos & (-pos))
      res += a[pos];
    return res;
  }
};

struct sgt_t
{
  struct node_t
  {
    int min = 0, add = 0;
    node_t() = default;
    node_t(const node_t &lhs, const node_t &rhs)
        : min(std::min(lhs.min, rhs.min))
    {
    }
    void push_add(int det)
    {
      min += det;
      add += det;
    }
    void push_down(node_t &lhs, node_t &rhs)
    {
      if (add)
      {
        lhs.push_add(add);
        rhs.push_add(add);
        add = 0;
      }
    }
  };

  std::vector<node_t> p;
  int n;

  sgt_t(int n) : p(4 * n), n(n)
  {
  }

  void modify(int u, int l, int r, int ml, int mr, int det)
  {
    if (ml <= l && r <= mr)
    {
      p[u].push_add(det);
      return;
    }
    p[u].push_down(p[u + u], p[u + u + 1]);
    int mid = (l + r) / 2;
    if (ml < mid)
      modify(u + u, l, mid, ml, mr, det);
    if (mr > mid)
      modify(u + u + 1, mid, r, ml, mr, det);
    p[u] = node_t(p[u + u], p[u + u + 1]);
  }

  auto query(int u, int l, int r, int ql, int qr)
  {
    if (ql <= l && r <= qr)
      return p[u];
    p[u].push_down(p[u + u], p[u + u + 1]);
    int mid = (l + r) / 2;
    if (qr <= mid)
      return query(u + u, l, mid, ql, qr);
    if (ql >= mid)
      return query(u + u + 1, mid, r, ql, qr);
    return node_t(query(u + u, l, mid, ql, qr),
                  query(u + u + 1, mid, r, ql, qr));
  }
};

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int(), m = sc.next_int();
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();
    for (int i = 0; i < m; i++)
      b[i] = sc.next_int();
    std::sort(b.begin(), b.end());

    std::vector<int> vals(a.begin(), a.end());
    for (int x : b)
      vals.push_back(x);
    std::sort(vals.begin(), vals.end());
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
    for (int &x : a)
      x = static_cast<int>(std::lower_bound(vals.begin(), vals.end(), x) -
                           vals.begin());
    for (int &x : b)
      x = static_cast<int>(std::lower_bound(vals.begin(), vals.end(), x) -
                           vals.begin());

    long long ans = 0;

    {
      ftree_t a_cnt(n + m);
      for (int i = 0; i < n; i++)
      {
        ans += i - a_cnt.query(a[i]);
        a_cnt.modify(a[i], 1);
      }
    }

    {
      std::vector<std::pair<int,int>> aa;
      for (int i = 0; i < n; i++)
        aa.emplace_back(a[i], i);
      std::sort(aa.begin(), aa.end());

      sgt_t ans_pos(n + 1);
      for (int i = 1; i <= n; i++)
        ans_pos.modify(1, 0, n + 1, i, i + 1, i);
      int a_le = 0, a_lt = 0;
      for (int x : b)
      {
        while (a_le < n && aa[a_le].first <= x)
        {
          ans_pos.modify(1, 0, n + 1, aa[a_le].second + 1, n + 1, -1);
          a_le++;
        }
        while (a_lt < n && aa[a_lt].first < x)
        {
          ans_pos.modify(1, 0, n + 1, 0, aa[a_lt].second + 1, 1);
          a_lt++;
        }
        ans += ans_pos.query(1, 0, n + 1, 0, n + 1).min;
      }

      printf("%lld\n", ans);
    }
  }
  return 0;
}
