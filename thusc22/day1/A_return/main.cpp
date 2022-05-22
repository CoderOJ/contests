#include <bits/stdc++.h>

const int N = 1005;
const int T = 10105;
int       n, m, k, s, t, mt;
double    prob[T], pp[T], ppi[T];

struct edge_t
{
  int v, l, a, b;
};

std::vector<edge_t> e[N];

double b_dis[N];

double dfs(int u, int t)
{
  if (u == ::t)
    return 0;
  if (t > mt)
    return 0;

  static double mem[N][T];
  if (mem[u][t] != 0)
    return mem[u][t];

  double res = std::numeric_limits<double>::max();
  for (const auto &p : e[u])
  {
    double pd = pp[t + p.l] - pp[t];
    double pdi = ppi[t + p.l] - ppi[t];
    double cur_res0 = (pp[t + p.l] - pp[t]) * b_dis[p.v] + (pdi - pd * t) * p.a + (pd * (t + p.l) - pdi) * p.b;
    double cur_res1 = (pp[mt] - pp[t + p.l]) * p.l * p.a + dfs(p.v, t + p.l);
    res = std::min(res, cur_res0 + cur_res1);
  }
  // printf("dfs(%d, %d) = %f\n", u, t, res);
  mem[u][t] = res;
  return res;
}

int main()
{
  scanf("%d%d%d%d%d", &n, &m, &k, &s, &t);
  for (int i = 0; i < m; i++)
  {
    int u, v, l, a, b;
    scanf("%d%d%d%d%d", &u, &v, &l, &a, &b);
    e[u].push_back({v, l, a, b});
    e[v].push_back({u, l, a, b});
  }

  for (int i = 0; i < k; i++)
  {
    int t;
    scanf("%d", &t);
    scanf("%lf", &prob[t]);
    mt = std::max(t, mt);
  }
  {
    double psum = 0;
    for (int i = mt; i >= 0; i--)
      psum += prob[i];

    prob[0] /= psum;
    pp[0] = prob[0];
    ppi[0] = 0;
    for (int i = 1; i <= mt + 50; i++)
    {
      prob[i] /= psum;
      pp[i] = pp[i - 1] + prob[i];
      ppi[i] = ppi[i - 1] + prob[i] * i;
    }
  }

  {
    std::fill(b_dis, b_dis + N, std::numeric_limits<double>::max());
    b_dis[t] = 0;
    for (int i = 0; i < n; i++)
    {
      for (int u = 1; u <= n; u++)
        for (auto &p : e[u])
          b_dis[p.v] = std::min(b_dis[p.v], b_dis[u] + p.b * p.l);
    }
    // for (int i = 1; i <= n; i++)
    //   printf("b_dis[%d] = %f\n", i, b_dis[i]);
  }

  printf("%.12lf\n", dfs(s, 0));

  return 0;
}
