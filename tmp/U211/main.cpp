#include <bits/stdc++.h>

const int MOD = 998244353;
const int N = 105;
int move[4][3] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int n;

template <class T>
struct array_t
{
  T data[N * 2];
  T &operator[](size_t id) { return data[N + id]; }
  T operator[](size_t id) const { return data[N + id]; }
};

int pw[N];
void init_pw()
{
  pw[0] = 1;
  pw[1] = move[0][2] + move[1][2] + move[2][2] + move[3][2];
  for (int i = 2; i < N; i++)
    pw[i] = 1ll * pw[i - 1] * pw[1] % MOD;
}

array_t<array_t<int>> direct[N];
void init_direct()
{
  direct[0][0][0] = 1;
  for (int i = 0; i < n; i++)
    for (int x = -N; x < N; x++)
      for (int y = -N; y < N; y++)
        if (direct[i][x][y])
          for (const auto &[dx, dy, dw] : move)
            direct[i + 1][x + dx][y + dy] = (direct[i + 1][x + dx][y + dy] + 1ll * direct[i][x][y] * dw) % MOD;
}

void direct_ban(int ans[], int n, int bx, int by)
{
  static int cnt[N][2];
  int kx[] = {0, bx}, ky[] = {0, by};
  cnt[0][0] = cnt[0][1] = 0;
  for (int i = 1; i <= n; i++)
    for (int b = 0; b < 2; b++)
    {
      cnt[i][b] = direct[i][kx[b]][ky[b]];
      for (int p = 1; p < i; p++)
        for (int pb = 0; pb < 2; pb++)
          if (direct[i - p][kx[b] - kx[pb]][ky[b] - ky[pb]])
            cnt[i][b] = (cnt[i][b] - 1ll * cnt[p][pb] * direct[i - p][kx[b] - kx[pb]][ky[b] - ky[pb]]) % MOD;
    }
  int p = 0;
  for (int i = 0; i <= n; i++)
  {
    p = (1ll * p * pw[1] + cnt[i][0] + cnt[i][1]) % MOD;
    ans[i] = (pw[i] - p) % MOD;
  }
}

int p_sum()
{
  static int db[N];
  direct_ban(db, n, n, n);

  int ans = 0;
  for (int t = 0; t <= n; t++)
    for (int x = -n; x <= n; x++)
      for (int y = -n; y <= n; y++)
        if (direct[t][x][y])
          ans = (ans + 1ll * direct[t][x][y] * db[n - t]) % MOD;

  return ans;
}

int p_ban[N];
void init_p_ban()
{
  static array_t<array_t<int>> db[N];
  db[0][0][0] = 1;
  for (int i = 0; i < n; i++)
  {
    for (int x = -n; x <= n; x++)
      for (int y = -n; y <= n; y++)
        if (db[i][x][y])
          for (const auto &[dx, dy, dw] : move)
            db[i + 1][x + dx][y + dy] = (db[i + 1][x + dx][y + dy] + 1ll * db[i][x][y] * dw) % MOD;
    db[i + 1][0][0] = 0;
  }

  for (int x = -n; x <= n; x++)
    for (int y = -n; y <= n; y++)
      if ((x != 0 || y != 0) && x + y <= n)
      {
        static int dbb[N];
        direct_ban(dbb, n, -x, -y);
        for (int p = 1; p <= n; p++)
          for (int q = 0; p + q <= n; q++)
            if (db[p][x][y])
              p_ban[p + q] = (p_ban[p + q] + 1ll * db[p][x][y] * dbb[q]) % MOD;
      }
}

int psq_sum()
{
  int ans = 0;
  for (int i = 0; i <= n; i++)
    for (int x = -n; x <= n; x++)
      for (int y = -n; y <= n; y++)
        ans = (ans + 1ll * direct[i][x][y] * p_ban[n - i]) % MOD;
  return (0ll + ans + ans + p_sum()) % MOD;
}

int main()
{
  scanf("%d", &n);
  scanf("%d%d%d%d", &move[0][2], &move[1][2], &move[2][2], &move[3][2]);
  init_pw();
  init_direct();
  init_p_ban();
  int p = p_sum();
  int psq = psq_sum();
  int ans = (1ll * psq * pw[n] - 1ll * p * p) % MOD;
  ans = (ans + MOD) % MOD;
  std::cout << ans << std::endl;
  return 0;
}
