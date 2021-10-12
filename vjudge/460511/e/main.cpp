#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

struct ftree_t
{
  const int n;
  std::vector<int> t;
  ftree_t(size_t _n) : n(static_cast<int>(_n)), t(n + 1)
  {
  }
  void add(int pos, int a)
  {
    for (++pos; pos <= n; pos += pos & -pos)
      t[pos] += a;
  }
  int sum(int pos) const
  {
    int res = 0;
    for (; pos; pos -= pos & -pos)
      res += t[pos];
    return res;
  }
  int sum(int l, int r) const
  {
    return sum(r) - sum(l);
  }
};

void solve()
{
  int n = sc.next_int();
  std::vector<long long> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  std::vector<std::vector<int>> e(n);
  for (int _ = n - 1; _--;)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  std::vector<bool> ex(n, true);
  std::vector<int> sz(n), par(n);
  auto centroids = [&](int r, int cur_n) {
    std::vector<int> res;
    auto dfs = [&](auto &&self, int v, int p) -> void {
      sz[v] = 1, par[v] = p;
      bool ok = true;
      for (int u : e[v])
        if (ex[u] and u != p)
        {
          self(self, u, v);
          sz[v] += sz[u];
          ok &= 2 * sz[u] <= cur_n;
        }
      if (ok &= 2 * sz[v] >= cur_n)
        res.push_back(v);
    };
    dfs(dfs, r, -1);
    return res;
  };

  std::vector<long long> mx(n), sum(n);
  long long res = 0;
  std::vector<std::pair<long long, long long>> vec;
  long long ac = -1;
  auto fn = [&](int l, int r) -> long long {
    sort(begin(vec) + l, begin(vec) + r);
    std::vector<long long> vs;
    for (int i = l; i < r; ++i)
    {
      vs.push_back(vec[i].second);
    }
    sort(begin(vs), end(vs));
    vs.erase(unique(begin(vs), end(vs)), end(vs));
    auto zip = [&](long long x) -> int {
      return static_cast<int>(lower_bound(begin(vs), end(vs), x) - begin(vs));
    };
    ftree_t ft(vs.size());
    long long cnt = 0;
    for (int i = l; i < r; ++i)
    {
      int s = zip(2 * vec[i].first - vec[i].second + ac + 1);
      cnt += ft.sum(s, static_cast<int>(vs.size()));
      ft.add(zip(vec[i].second), 1);
    }
    return cnt;
  };

  auto dfs = [&](auto &&self, int v, int p) -> void {
    mx[v] = std::max(mx[p], a[v]);
    sum[v] = sum[p] + a[v];
    res += 2 * mx[v] < sum[v];
    vec.emplace_back(mx[v], sum[v]);
    for (int u : e[v])
      if (ex[u] and u != p)
        self(self, u, v);
  };

  auto rec = [&](auto &&self, int c, int cur_n) -> void {
    c = centroids(c, cur_n)[0];
    vec.clear();
    ac = a[c];
    for (int v : e[c])
      if (ex[v])
      {
        mx[c] = sum[c] = a[c];
        int prv = static_cast<int>(vec.size());
        dfs(dfs, v, c);
        res -= fn(prv, static_cast<int>(vec.size()));
      }
    res += fn(0, static_cast<int>(vec.size()));
    ex[c] = false;
    for (int v : e[c])
      if (ex[v])
        self(self, v, par[v] == c ? sz[v] : cur_n - sz[c]);
    ex[c] = true;
  };

  rec(rec, 0, n);
  std::cout << res << std::endl;
}

int main()
{
  int tt = sc.next_int();
  while (tt--)
  {
    solve();
  }
}
