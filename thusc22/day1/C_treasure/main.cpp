#include "treasure.h"
#include <bits/stdc++.h>

const int THR = 2502;

const int        N = 1000005;
std::vector<int> e[N];

int dis[N], col[N];

void Alice(const int,
           const int n,
           const int m,
           const int s,
           const int u[],
           const int v[],
           bool      dir[])
{
  for (int i = 0; i < m; i++)
  {
    e[u[i]].push_back(v[i]);
    e[v[i]].push_back(u[i]);
  }

  std::fill(dis, dis + n, -1);
  dis[s] = 0;
  col[s] = 0;
  std::queue<int> que;
  que.push(s);
  while (!que.empty())
  {
    int u = que.front();
    que.pop();
    for (int v : e[u])
      if (dis[v] == -1)
      {
        dis[v] = dis[u] + 1;
        col[v] = 1 - col[u];
        que.push(v);
        // printf("%d: dis = %d, col = %d\n", v, dis[v], col[v]);
      }
  }

  int inv_cnt[2] = {0, 0};
  for (int i = 0; i < n; i++)
    if (dis[i] >= THR)
      inv_cnt[col[i]] += 1;
  int inv_col = inv_cnt[0] > inv_cnt[1] ? 0 : 1;

  for (int i = 0; i < m; i++)
  {
    if (dis[u[i]] < THR && dis[v[i]] < THR)
    {
      if (dis[u[i]] < dis[v[i]])
        dir[i] = false;
      else
        dir[i] = true;
    }
    else if (dis[u[i]] < THR && dis[v[i]] >= THR)
    {
      dir[i] = false;
    }
    else if (dis[u[i]] >= THR && dis[v[i]] < THR)
    {
      dir[i] = true;
    }
    else
    {
      if (col[u[i]] == inv_col)
        dir[i] = false;
      else
        dir[i] = true;
    }
  }
}

using et_t = decltype(discover(0));
et_t eq[N];
int  eq_any[N];

void query(int u)
{
  if (eq[u].empty())
  {
    eq[u]     = discover(u);
    eq_any[u] = -1;
    for (const auto &[v, w] : eq[u])
      if (w)
      {
        eq_any[u] = v;
        break;
      }
  }
}

int Bob(const int, const int n)
{
  if (n < THR)
  {
    int u = 0;
    query(u);
    while (eq_any[u] != -1)
    {
      u = eq_any[u];
      query(u);
    }
    return u;
  }

  std::vector<int> us(n);
  for (int i = 0; i < n; i++)
    us[i] = i;
  std::shuffle(us.begin(), us.end(), std::mt19937(18100301));

  static int special_cnt[N];
  std::fill(special_cnt, special_cnt + n, 0);

  int u_cnt = 0;
  auto is_special_root = [&](int u) {
    if (u_cnt >= 2300 && special_cnt[u] >= 2100)
      return true;
    else
      return false;
  };

  for (int u : us)
  {
    query(u);
    u_cnt += 1;
    if (eq_any[u] == -1)
    {
    }
    else
    {
      int v = eq_any[u];
      query(v);
      if (eq_any[v] == -1)
      {
        special_cnt[v] += 1;
        if (is_special_root(v))
          return v;
      }
      else
      {
        while (eq_any[v] != -1)
        {
          v = eq_any[v];
          query(v);
        }
        return v;
      }
    }
  }

  return -1;
}
