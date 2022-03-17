#include "./maze_io.hpp"
#include "/home/jack/cm/debug"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

int n, m, k, t;

constexpr int N = 100005;

int     p[N];
int64_t dis[N];
int64_t g[N];

int get(int u)
{
  if (p[u] == u)
  {
    return u;
  }
  else
  {
    int fa = p[u];
    p[u]   = get(fa);
    dis[u] += dis[fa];
    return p[u];
  }
}

int main()
{
  maze_io::get_args(&n, &m, &k, &t);

  for (int i = 1; i <= n; i++)
    p[i] = i;

  for (int i = 0; i < m; i++)
  {
    int     opt, u, v;
    int64_t w;
    maze_io::get_line(&opt, &u, &v, &w);
    int pu = get(u);
    int pv = get(v);

    if (opt == 0)
    {
      if (pu == pv)
      {
        g[pu] = cm::gcd(g[pu], std::abs(w - (dis[u] - dis[v])));
      }
      else
      {
        p[pu]   = pv;
        dis[pu] = w - (dis[u] - dis[v]);
        g[pv]   = cm::gcd(g[pu], g[pv]);
      }
    }
    else
    {
      if (pu != pv)
      {
        maze_io::put_ans(0);
      }
      else
      {
        int64_t cur_w = std::abs(w - (dis[u] - dis[v]));
        if (g[pu] == 0)
          maze_io::put_ans(cur_w == 0 ? 1 : 0);
        else
          maze_io::put_ans(cur_w % g[pu] == 0 ? 1 : 0);
      }
    }
  }
  return 0;
}
