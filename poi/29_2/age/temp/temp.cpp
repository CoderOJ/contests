#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 500005;

std::vector<int> e[N];

int n, m;

bool color[N];

int dp[N][4];

void dfs(int u, int f)
{
  dp[u][0] = 0;
  dp[u][1] = -0x3f3f3f3f;
  dp[u][2] = -0x3f3f3f3f;
  dp[u][3] = -0x3f3f3f3f;
  for (int v : e[u])
    if (v != f)
    {
      dfs(v, u);
      int dpv[3];
      if (color[v])
      {
        dpv[0] = std::max({dp[v][0], dp[v][1]});
        dpv[1] = -0x3f3f3f3f;
        dpv[2] = std::max({dp[v][0]}) + 1;
      }
      else
      {
        dpv[0] = std::max({dp[v][0], dp[v][2], dp[v][3]});
        dpv[1] = std::max({dp[v][0], dp[v][1]}) + 1;
        dpv[2] = std::max({dp[v][2]}) + 1;
      }
      int dpu[4];
      dpu[0] = std::max({dp[u][0] + dpv[0]});
      dpu[1] = std::max({dp[u][0] + dpv[1], dp[u][1] + dpv[0]});
      dpu[2] = std::max({dp[u][0] + dpv[2], dp[u][2] + dpv[0]});
      dpu[3] =
          std::max({dp[u][3] + dpv[0], dp[u][1] + dpv[2], dp[u][2] + dpv[1]});
      std::copy(dpu, dpu + 4, dp[u]);
    }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u    = sc.next_int();
    color[u] = true;
  }
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }

  dfs(1, 0);
  int ans = (n - m) * 2;
  if (color[1])
    ans -= std::max({dp[1][0], dp[1][1]});
  else
    ans -= std::max({dp[1][0], dp[1][2], dp[1][3]});

  std::cout << ans << std::endl;

  return 0;
}
