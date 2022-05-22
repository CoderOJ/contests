#include <bits/stdc++.h>

const int N = 2005;

int n, x;
int a[N], b[N];
double p[N];

bool used[N];

double ans = 0;

void dfs(int u, double p)
{
  ans += p * a[u];
  if (used[u] && used[b[u]])
  {
  }
  else if (used[u] && !used[b[u]])
  {
    if (b[u] != x)
    {
      used[b[u]] = true;
      dfs(b[u], p);
      used[b[u]] = false;
    }
  }
  else if (!used[u] && used[b[u]])
  {
    if (u != x)
    {
      used[u] = true;
      dfs(u, p);
      used[u] = false;
    }
  }
  else
  {
    {
      if (u != x)
      {
        used[u] = true;
        dfs(u, p * ::p[u]);
        used[u] = false;
      }
    }
    {
      if (b[u] != x)
      {
        used[b[u]] = true;
        dfs(b[u], p * (1 - ::p[u]));
        used[b[u]] = false;
      }
    }
  }
}

int main()
{
  std::cin >> n >> x;
  x -= 1;
  for (int i = 0; i < n; i++)
  {
    std::cin >> a[i] >> b[i] >> p[i];
    b[i] -= 1;
  }

  for (int i = 0; i < n; i++)
    dfs(i, 1.0 / n);

  printf("%.12f\n", ans);
  return 0;
}
