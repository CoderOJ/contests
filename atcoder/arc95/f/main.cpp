#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;

std::vector<int>                 e[N];
std::vector<std::pair<int, int>> es;

int deg[N], ddeg[N];
int n;

void dfs(std::vector<int> &ans, int u, int f)
{
  int cnt = deg[u] - 1;
  int st  = static_cast<int>(ans.size());
  for (int i = st + 1; i < st + cnt; i++)
    ans.emplace_back(i);
  ans.emplace_back(st);
  for (int v : e[u])
    if (v != f)
      dfs(ans, v, u);
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    es.emplace_back(u, v);
    deg[u]++;
    deg[v]++;
  }

  if (n == 2)
  {
    puts("1 2");
    return 0;
  }

  for (const auto &[u, v] : es)
  {
    if (deg[u] > 1 && deg[v] > 1)
    {
      ddeg[u]++;
      ddeg[v]++;
      e[u].push_back(v);
      e[v].push_back(u);
    }
  }

  std::vector<int> ends;
  for (int i = 1; i <= n; i++)
    if (deg[i] > 1)
    {
      if (ddeg[i] >= 3)
      {
        puts("-1");
        return 0;
      }
      else if (ddeg[i] <= 1)
      {
        ends.push_back(i);
      }
    }

  if (ends.size() == 1)
    ends.push_back(ends[0]);
  cm_assert(ends.size() == 2);

  std::vector<int> ans0{0};
  dfs(ans0, ends[0], ends[0]);
  std::vector<int> ans1{0};
  dfs(ans1, ends[1], ends[1]);
  auto ans = std::move(std::min(ans0, ans1));
  ans.emplace_back(n - 1);

  for (int x : ans)
    std::cout << x + 1 << " ";

  return 0;
}
