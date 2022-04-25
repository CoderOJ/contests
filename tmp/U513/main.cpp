#include <bits/stdc++.h>

const int N = 300;

std::bitset<N> e[N];
int b[N], n, m;

std::bitset<N> bs[N];
int bsv[N];

void rmain()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
  {
    e[i].reset();
    b[i] = 0;
  }
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--, v--;
    e[u].set(v);
    e[v].set(u);
    b[u] ^= w;
    b[v] ^= w;
  }
  for (int i = 0; i < n; i++)
    if (e[i].count() % 2 == 1)
      e[i].set(i);

  for (int i = 0; i < n; i++)
  {
    bs[i].reset();
    bsv[i] = 0;
  }
  for (int i = 0; i < n; i++)
  {
    auto &c = e[i];
    int cv = b[i];
    for (int j = 0; j < n; j++)
      if (c.test(j))
      {
        if (bs[j].any())
        {
          c ^= bs[j];
          cv ^= bsv[j];
        }
        else
        {
          bs[j] = c;
          bsv[j] = cv;
          cv = 0;
          break;
        }
      }
    if (cv)
    {
      puts("no");
      return;
    }
  }
  puts("yes");
}

int main()
{
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
    rmain();
  return 0;
}
