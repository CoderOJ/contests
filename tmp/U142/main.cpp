#include <bits/stdc++.h>

int main()
{
  int T;
  scanf("%d", &T);
  for (int i = 0; i < T; i++)
  {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    if (1ll * n * m > k * 4)
    {
      puts("No");
      for (int i = 0; i < k; i++) scanf("%*d%*d");
    }
    else
    {
      std::vector<std::vector<bool>> ban(n, std::vector<bool>(m, false));
      for (int i = 0; i < k; i++)
      {
        int x, y;
        scanf("%d%d", &x, &y);
        x--, y--;
        ban[x][y] = true;
      }
      bool ans = [&]{
        struct node_t
        {
          node_t *p;
          node_t *get()
          {
            return p == this ? p : p = p->get();
          }
        };
        std::vector<std::vector<node_t>> p(n, std::vector<node_t>(m));
        for (int i = 0; i < n; i++)
          for (int j = 0; j < m; j++)
            p[i][j].p = &p[i][j];
        for (int i = 0; i < n; i++)
          for (int j = 0; j < m; j++)
          {
            int x = j, y = (j + 1) % m;
            if (!ban[i][x] && !ban[i][y])
            {
              if (p[i][x].get() != p[i][y].get())
                p[i][x].get()->p = p[i][y].get();
              else
                return false;
            }
          }
        for (int i = 0; i + 1 < n; i++)
          for (int j = 0; j < m; j++)
          {
            if (!ban[i][j] && !ban[i + 1][j])
            {
              if (p[i][j].get() != p[i + 1][j].get())
                p[i][j].get()->p = p[i + 1][j].get();
              else
                return false;
            }
          }
        int comp_cnt = 0;
        for (int i = 0; i < n; i++)
          for (int j = 0; j < m; j++)
            if (!ban[i][j] && p[i][j].p == &p[i][j])
              comp_cnt++;
        return comp_cnt <= 1;
      }();
      puts(ans ? "Yes" : "No");
    }
  }
  return 0;
}
