#include <bits/stdc++.h>
#include <utility>
#include <vector>

const int N = 100005;
const int K = 22;

std::vector<std::pair<int, int64_t>> e[N];
int n, m;

std::vector<int> ks;
int k;

int64_t dis[K][N];

void sp(int64_t dis[], int u)
{
  std::fill(dis + 1, dis + n + 1, std::numeric_limits<int64_t>::max() / 2);
  dis[u] = 0;

  std::priority_queue<
    std::pair<int64_t, int>,
    std::vector<std::pair<int64_t, int>>,
    std::greater<std::pair<int64_t, int>>>
      que;
  que.emplace(dis[u], u);

  while (!que.empty())
  {
    const auto [du, u] = que.top();
    que.pop();

    if (du == dis[u])
    {
      for (const auto &[v, w]: e[u])
        if (du + w < dis[v])
        {
          dis[v] = du + w;
          que.emplace(dis[v], v);
        }
    }
  }
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++)
  {
    int u, v;
    int64_t w;
    scanf("%d%d%" SCNi64, &u, &v, &w);
    e[u].emplace_back(v, w * 2);
    e[v].emplace_back(u, w * 2);
  }

  scanf("%d", &k);
  for (int i = 0; i < k; i++)
  {
    int u;
    scanf("%d", &u);
    ks.push_back(u);
  }
  ks.push_back(1);
  k += 1;

  for (int i = 0; i < k; i++)
    sp(dis[i], ks[i]);

  int64_t ans = std::numeric_limits<int64_t>::max() / 2;

  for (int u = 1; u <= n; u++)
    for (const auto &[v, w]: e[u])
      if (v > u)
      {
        std::vector<int64_t> brks{0, w};
        for (int r = 0; r < k; r++)
          brks.push_back((w + dis[r][v] - dis[r][u]) / 2);

        std::sort(brks.begin(), brks.end());
        brks.erase(std::unique(brks.begin(), brks.end()), brks.end());

        for (int i = 0; i + 1 < (int)brks.size(); i++)
        {
          const int64_t il = brks[i], ir = brks[i + 1];
          const int64_t ilen = ir - il;

          int64_t l_max = std::numeric_limits<int64_t>::min() / 2;
          int64_t r_max = std::numeric_limits<int64_t>::min() / 2;
          for (int r = 0; r < k; r++)
          {
            int64_t rk = (w + dis[r][v] - dis[r][u]) / 2;
            if (rk >= ir)
              r_max = std::max(r_max, dis[r][u] + ir);
            else
              l_max = std::max(l_max, dis[r][v] + (w - il));
          }

          if (l_max - ilen >= r_max)
            ans = std::min(ans, l_max - ilen);
          else if (r_max - ilen >= l_max)
            ans = std::min(ans, r_max - ilen);
          else
            ans = std::min(ans, l_max - (ilen + (l_max - r_max)) / 2);
        }
      }

  std::cout << ans << std::endl;

  return 0;
}
