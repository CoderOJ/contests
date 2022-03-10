#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 18;

int e[N][N];
int e_min[N][N];

int      n;
uint32_t n_all;

int solve(uint32_t);
int solve_chain(uint32_t, int, int);

int cur[1 << N][N];

void init_cur()
{
  for (uint32_t mask = 1; mask <= n_all; mask++)
    for (int next = 0; next < n; next++)
      if ((mask & (1u << next)) == 0)
      {
        int cur = 0;
        for (int p = 0; p < n; p++)
          if ((mask & (1u << p)) && e[p][next] != -1)
            cur += e_min[p][next];
        ::cur[mask][next] = cur;
      }
}

int solve_chain(uint32_t mask, int u, int v)
{
  if (mask == n_all)
    return 0x3f3f3f3f;

  static int mem[1 << N][N][N];
  if (mem[0][1][2] == 0)
    memset(mem, -1, sizeof(mem));
  if (mem[mask][u][v] != -1)
    return mem[mask][u][v];

  int ans = 0x3f3f3f3f;
  for (int next = 0; next < n; next++)
    if ((mask & (1u << next)) == 0 && e[v][next] != -1)
    {
      int cur = 0;
      cur     = ::cur[mask][next];
      if (u == v)
      {
        cur -= e_min[v][next];
        cur += e[v][next];
      }
      else
      {
        if (e[u][next] != -1)
          cur -= e_min[u][next];
        cur -= e_min[v][next];
        cur += e[v][next];
      }

      if (e[u][next] != -1)
      {
        if (u != v)
        {
          check_min(ans, cur + e[next][u] + solve(mask | (1u << next)));
          check_min(ans,
                    cur + e_min[u][next] +
                        solve_chain(mask | (1u << next), u, next));
        }
        else
        {
          check_min(ans, cur + solve_chain(mask | (1u << next), u, next));
        }
      }
      else
      {
        check_min(ans, cur + solve_chain(mask | (1u << next), u, next));
      }
    }

  mem[mask][u][v] = ans;
  return ans;
}

int solve(uint32_t mask)
{
  if (mask == n_all)
    return 0;

  static int mem[1 << N];
  if (mem[0] == 0)
    memset(mem, -1, sizeof(mem));
  if (mem[mask] != -1)
    return mem[mask];

  int ans = 0x3f3f3f3f;
  for (int u = 0; u < n; u++)
    if (mask & (1u << u))
      for (int v = 0; v < n; v++)
        if (mask & (1u << v))
          check_min(ans, solve_chain(mask, u, v));

  mem[mask] = ans;
  return ans;
}

int main()
{
  n     = sc.next_int();
  n_all = (1u << n) - 1;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      e[i][j] = sc.next_int();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      e_min[i][j] = std::min(e[i][j], e[j][i]);

  init_cur();

  auto ans = solve(1u);
  if (ans >= 0x3f3f3f3f)
    std::cout << -1 << std::endl;
  else
    std::cout << solve(1u) << std::endl;

  return 0;
}
