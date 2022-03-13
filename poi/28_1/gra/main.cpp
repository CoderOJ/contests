#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <deque>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 100'005, 100'005)
CONSTRAINT(M, 3'000'005, 3'000'005)

using inter_t = std::pair<int, int>;

std::vector<std::pair<inter_t, int>> inters[N];
std::vector<std::pair<int, int>>     e[M];

int n, m, q;
int dis[M];

void add_edge(int u, int v, int w)
{
  see(u, v, w);
  e[u].emplace_back(v, w);
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  q = sc.next_int();

  int inter_id = 0;
  for (int i = 0; i < n; i++)
  {
    int k   = sc.next_int();
    int cur = 0;
    for (int j = 0; j < k; j++)
    {
      int r = sc.next_int() - 1;
      inters[i].emplace_back(inter_t(cur, r), inter_id++);
      cur = r + 1;
    }
    inters[i].emplace_back(inter_t(cur, m), inter_id++);
    see(i, inters[i]);
  }

  see("insert e_");
  for (int i = 0; i < n; i++)
    for (size_t j = 0; j + 1 < inters[i].size(); j++)
      add_edge(inters[i][j + 1].second, inters[i][j].second, 1);

  see("insert e/");
  for (int i = 0; i + 1 < n; i++)
  {
    auto it = inters[i + 1].begin();
    for (const auto &[inter, u] : inters[i])
    {
      while (it != inters[i + 1].end() && it->first.second <= inter.first - 1)
        it++;
      if (it != inters[i + 1].end() && it->first.first <= inter.first - 1 &&
          inter.first - 1 < it->first.second)
        add_edge(u, it->second, 1);
    }
  }

  see("insert e\\");
  for (int i = 0; i + 1 < n; i++)
  {
    auto it = inters[i + 1].begin();
    for (const auto &[inter, u] : inters[i])
    {
      while (it != inters[i + 1].end() && it->first.second <= inter.second)
        it++;
      if (it != inters[i + 1].end() && it->first.first <= inter.second &&
          inter.second < it->first.second)
        add_edge(it->second, u, 0);
    }
  }

  std::deque<int> que;
  std::fill(dis, dis + M, 0x3f3f3f3f);
  for (int i = 0; i < n; i++)
  {
    int s  = inters[i].back().second;
    dis[s] = 0;
    que.emplace_back(s);
  }

  while (!que.empty())
  {
    int u = que.front();
    que.pop_front();
    for (const auto &[v, w] : e[u])
      if (check_min(dis[v], dis[u] + w))
      {
        if (w == 0)
          que.push_front(v);
        else
          que.push_back(v);
      }
  }

  for (int i = 0; i < q; i++)
  {
    int id = sc.next_int() - 1;
    printf("%d\n", dis[inters[id][0].second]);
  }

  return 0;
}
