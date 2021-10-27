#include <stdio.h>
#include <stdbool.h>

#define MOD 1000000007
#define N 605

int ofac[N];
int jump[N];
int f[N][N];
int n, k;

int main()
{
  scanf("%d%d", &n, &k);
  n *= 2;

  ofac[0] = 1;
  for (int i = 2; i < N; i += 2)
    ofac[i] = 1ll * ofac[i - 2] * (i - 1) % MOD;
  for (int i = 0; i < k; i++)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    jump[u] = v, jump[v] = u;
  }

  int ans = 0;
  for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j += 2)
    {
      bool have_outside = false;
      int free_cnt = j - i + 1;
      for (int k = i; k <= j; k++)
        if (jump[k])
        {
          free_cnt--;
          if (jump[k] < i || jump[k] > j)
          {
            have_outside = true;
            break;
          }
        }

      if (have_outside) continue;
      f[i][j] = ofac[free_cnt];
      for (int k = j, rfree_cnt = 0; k > i; k--)
      {
        rfree_cnt += jump[k] == 0;
        f[i][j] = (f[i][j] - 1ll * f[i][k - 1] * ofac[rfree_cnt]) % MOD;
        if (f[i][j] < 0)
          f[i][j] += MOD;
      }

      ans = (ans + 1ll * f[i][j] * ofac[n - 2 * k - free_cnt]) % MOD;
    }

  printf("%d\n", ans);
  return 0;
}
