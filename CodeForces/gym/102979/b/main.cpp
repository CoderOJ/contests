#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 300'005;

int p[N];
int n, k;

int get(int u)
{
  return u == p[u] ? u : p[u] = get(p[u]);
}

std::vector<std::tuple<int, int, int>> es;
std::vector<int>                       candi[N];

int main()
{
  n = sc.next_int();
  k = sc.next_int();
  for (int i = 1; i <= n; i++)
    p[i] = i;
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    es.emplace_back(w, u, v);
  }

  std::sort(es.begin(), es.end());
  for (auto [w, u, v] : es)
  {
    u = get(u);
    v = get(v);
    if (u > v)
      std::swap(u, v);
    candi[v].push_back(w);
    p[v] = u;
  }

  std::priority_queue<int, std::vector<int>, std::greater<int>> que;
  int64_t                                                       sum = 0;

  for (int i = 1; i <= n; i++)
  {
    for (int w : candi[i])
    {
      que.push(w);
      sum += w;
    }
    while ((int)que.size() > k)
    {
      sum -= que.top();
      que.pop();
    }
    std::cout << sum << '\n';
  }

  return 0;
}
