#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

#define int long long

constexpr int    N = 300005;
std::vector<int> e[N];
int              n, m;

struct mset_t
{
  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      s;
  int a;

  void sub(int x)
  {
    a += x;
  }
  void emplace(int a, int b)
  {
    s.emplace(a + this->a, b);
  }
  void insert(std::pair<int, int> x)
  {
    emplace(x.first, x.second);
  }
  auto size()
  {
    return s.size();
  }
  auto top()
  {
    return std::make_pair(s.top().first - a, s.top().second);
  }
  void pop()
  {
    s.pop();
  }
};

void join(mset_t &a, mset_t &&b)
{
  if (a.size() < b.size())
    std::swap(a, b);
  while (b.size())
  {
    a.insert(b.top());
    b.pop();
  }
}

mset_t ms[N];

int dep[N];
int ans;

void dfs(int u, int f)
{
  dep[u] = dep[f] + 1;
  for (int v : e[u])
    if (v != f)
    {
      dfs(v, u);
      while (ms[v].size() && dep[ms[v].top().second] > dep[u])
        ms[v].pop();
      if (ms[v].size())
      {
        int c = ms[v].top().first;
        ms[v].sub(c);
        ans += c;
      }
      else
      {
        puts("-1");
        exit(0);
      }
      join(ms[u], std::move(ms[v]));
    }
}

signed main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int c = sc.next_int();
    ms[u].emplace(c, v);
  }

  dfs(1, 0);
  std::cout << ans << std::endl;

  return 0;
}
