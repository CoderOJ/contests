#include <bitset>
#include <cstdint>
#include <unordered_map>
#include <vector>

int get_bit(uint64_t u, int i)
{
  return (int)((u >> i) & 1);
}

uint64_t bit_rev(uint64_t u, int n)
{
  uint64_t r = 0;
  for (int i = 0; i < n; i++)
  {
    r = r << 1 | (u & 1);
    u = u >> 1;
  }
  return r;
}

int main()
{
  int n, m, p;
  scanf("%d%d%d", &n, &m, &p);
  int nm = n * m;

  auto iaddml = [p](int x, int y) {
    int r = x + y;
    return r >= p ? r - p : r;
  };

  if (n == 1)
  {
    for (int i = 0; i < n * m; i++)
    {
      for (int j = 0; j < n * m; j++)
        printf("%d ", i + j == n * m - 1 ? 1 : 0);
      puts("");
    }
  }
  else if (m == 1)
  {
    for (int i = 0; i < n * m; i++)
    {
      for (int j = 0; j < n * m; j++)
        printf("%d ", i == j ? 1 : 0);
      puts("");
    }
  }
  else
  {
    uint64_t init_st = ((1ull << m) - 1) << n;

    static std::vector<std::unordered_map<uint64_t, int>> dp(nm + 1);
    dp[0][init_st] = 1;

    for (int up = 0; up < nm; up++)
      for (const auto &[uk, uv]: dp[up])
        for (int i = 0; i + 1 < n + m; i++)
          if (get_bit(uk, i) == 0 && get_bit(uk, i + 1) == 1)
          {
            auto  vk  = uk ^ (1ull << i) ^ (1ull << (i + 1));
            auto &dpv = dp[up + 1][vk];
            dpv       = iaddml(dpv, uv);
          }

    std::vector pc(n, std::vector(m, std::vector<int>(nm, 0)));
    for (int up = 0; up < nm; up++)
      for (const auto &[uk, uv]: dp[up])
      {
        int cx = n, cy = 0;
        for (int i = 0; i + 1 < n + m; i++)
        {
          if (get_bit(uk, i) == 0)
            cx -= 1;
          else
            cy += 1;

          if (get_bit(uk, i) == 0 && get_bit(uk, i + 1) == 1)
          {
            auto  vk = bit_rev(uk ^ (1ull << i) ^ (1ull << (i + 1)), n + m);
            auto &c  = pc[cx][cy][up];
            c        = (int)((c + (int64_t)uv * dp[nm - up - 1][vk]) % p);
          }
        }
      }

    std::vector ans(nm, std::vector<int>(nm, 0));

    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
      {
        const auto &va = pc[i][j];
        const auto &vb = pc[i][m - j - 1];
        for (int x = 0; x < nm; x++)
          for (int y = 0; y < nm; y++)
          {
            auto &c = ans[x][y];
            c       = (int)((c + (int64_t)va[x] * vb[y]) % p);
          }
      }

    for (int i = 0; i < nm; i++)
    {
      for (int j = 0; j < nm; j++)
        printf("%d ", ans[i][j]);
      puts("");
    }
  }

  return 0;
}
