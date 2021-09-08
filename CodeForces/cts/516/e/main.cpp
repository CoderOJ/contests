#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <vector>
#include <queue>
#include <limits>

cm::scanner<cm::optimal_reader> sc(stdin);

template <class Int>
Int gcd(Int a, Int b)
{ return b == 0 ? a : gcd(b, a % b); }

struct graph_t
{
  std::vector<int> vertices, exclude;
  std::vector<std::vector<std::pair<int,long long>>> edge;
  std::vector<long long> dis;

  void add_vertex(int u) { vertices.push_back(u); }
  int get_vertex(int u) { return static_cast<int>(std::lower_bound(vertices.begin(), vertices.end(), u) - vertices.begin()); }
  void ready() { 
    std::sort(vertices.begin(), vertices.end());
    vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end()); 
    edge.resize(vertices.size()); dis = std::vector<long long>(vertices.size(), std::numeric_limits<long long>::max() / 2);
    for (auto& x : exclude) x = get_vertex(x); }
  void add_edge(int u, int v, long long w) { 
    see(u, v, w);
    u = get_vertex(u); v = get_vertex(v);
    edge[u].emplace_back(v, w); }

  long long get_max_mp(int s) { s = get_vertex(s);
    std::priority_queue<std::pair<long long,int>, std::vector<std::pair<long long,int>>, std::greater<std::pair<long long,int>>> que;
    dis[s] = 0; que.emplace(0, s);
    while (!que.empty()) { const auto [d, u] = que.top(); que.pop();
      see(d, u);
      if (d != dis[u]) continue;
      for (const auto& [v,w] : edge[u]) if (check_min(dis[v], d + w)) {
        que.emplace(dis[v], v); see(d, w, d + w); } }
    for (int x : exclude) dis[x] = 0;
    see(dis);
    return *std::max_element(dis.begin(), dis.end()); }
};

int phi(int x) {
  int res = x;
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      res = res / i * (i - 1);
      while (x % i == 0) x /= i; } }
  if (x != 1) res = res / x * (x - 1);
  return res; }
int power(int a, int b, int mod) {
  int r = 1;; 
  for (; b; b >>= 1) {
    if (b & 1) r = 1ll * r * a % mod;
    a = 1ll * a * a % mod; }
  return r; }
int inv(int a, int b) { return power(a, phi(b) - 1, b); }

std::vector<int> join(const std::vector<int> &a, const std::vector<int> &b)
{
  std::vector<int> res(a.size() + b.size());
  std::merge(a.begin(), a.end(), b.begin(), b.end(), res.begin());
  res.erase(std::unique(res.begin(), res.end()), res.end());
  return res;
}

long long solve(int n, int m, const std::vector<int> &a, const std::vector<int> &b)
{
  see(n, m);
  see(a);
  see(b);

  {
    int g = gcd(n ,m);
    see(g);
    if (g != 1)
    {
      if ((size_t)g > a.size() + b.size()) { puts("-1"); exit(0); }
      std::vector<std::vector<int>> ga(g), gb(g);
      for (int x : a) ga[x % g].push_back(x / g);
      for (int x : b) gb[x % g].push_back(x / g);
      see(ga, gb);
      long long ans = 0;
      for (int i = 0; i < g; i++)
        check_max(ans, solve(n / g, m / g, ga[i], gb[i]) * g + i);
      return ans;
    }
  }

  if ((int)a.size() == n && (int)b.size() == m) { return -1; }
  if (n < m) return solve(m, n, b, a);
  if (a.empty() && b.empty()) { puts("-1"); exit(0); }

  auto c = join(a, b);
  if ((size_t)n == c.size())
  {
    long long res = 0;
    for (int i = 1; i <= n; i++)
      if ((int)a.size() - i < 0 || a[a.size() - i] != n - i)
      { check_max(res, (long long)n - i); break; }
    for (int i = 1; i <= m; i++)
      if ((int)b.size() - i < 0 || b[b.size() - i] != m - i)
      { check_max(res, (long long)m - i); break; }
    return res;
  }

  graph_t g;
  g.add_vertex(-1);
  for (int x : c) 
  {
    g.add_vertex(x);
    g.add_vertex((x + n - m) % n);
  }
  for (int x : a)
    g.exclude.push_back(x);
  g.ready();

  for (int x : c)
  {
    g.add_edge(-1, x, x);
    g.add_edge((x + n - m) % n, x, m);
  }

  int inv_m = inv(m, n);
  std::vector<std::pair<int,int>> ord;
  for (int x : c)
    ord.emplace_back(1ll * x * inv_m % n, x);
  std::sort(ord.begin(), ord.end());
  ord.push_back(ord.front());
  ord.back().first += n;
  see(ord);

  for (size_t i = 0; i < c.size(); i++)
  {
    long long ew = 1ll * m * (ord[i + 1].first - ord[i].first - 1);
    g.add_edge(ord[i].second, (ord[i].second + ew) % n, ew);
  }

  return g.get_max_mp(-1);
}

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<int> a(sc.next_int());
  for (auto& x: a) x = sc.next_int();
  std::vector<int> b(sc.next_int());
  for (auto& x: b) x = sc.next_int();
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  std::cout << std::max(0ll, solve(n, m, a, b)) << std::endl;
  return 0;
}

