#include <bits/stdc++.h>

const int N = 5'000'005;
int p[N], pc[N], n;
int e[N], *el[N], *ec[N];
char s[N];

void init_p()
{
  int v = 0;
  int tot = 0;
  for (int i = 0; i < n * 2; i++)
  {
    if (s[i] == '(')
    {
      tot++;
      p[tot] = v;
      pc[v] += 1;
      // printf("edge: %d %d\n", v, tot);
      v = tot;
    }
    else
    {
      v = p[v];
    }
  }
  el[0] = ec[0] = e;
  for (int i = 0; i <= n; i++)
  {
    ec[i + 1] = el[i + 1] = el[i] + pc[i];
  }
  for (int i = 1; i <= n; i++)
  {
    *ec[p[i]]++ = i;
  }
}

struct dp_t
{
  int dep;
  int height;
  int leaf_cnt;
  int64_t leaf_sum;
};

dp_t dp[N];
int pkey[N], pnext[N];
int64_t f[N];

int main()
{
  scanf("%d", &n);
  scanf("%s", s);
  init_p();

  for (int u = 2; u <= n; u++)
    dp[u].dep = dp[p[u]].dep + 1;
  for (int u = n; u >= 1; u--)
  {
    if (pc[u] == 0)
    {
      dp[u].leaf_cnt = 1;
    }
    else
    {
      for (int *v = el[u]; v < el[u + 1]; v++)
      {
        dp[u].leaf_cnt += dp[*v].leaf_cnt;
        dp[u].leaf_sum += dp[*v].leaf_sum + dp[*v].leaf_cnt;
        if (dp[*v].height + 1 > dp[u].height)
        {
          dp[u].height = dp[*v].height + 1;
          std::swap(el[u][0], *v);
        }
      }
    }
  }

  for (int u = n; u >= 1; u--)
  {
    if (pc[u] == 0)
    {
      pnext[u] = 0;
    }
    else
    {
      int v_height = 0;
      for (int *v = el[u] + 1; v < el[u + 1]; v++)
      {
        for (int q = *v; q != 0; q = pnext[q])
          pkey[q] = u;
        v_height = std::max(v_height, dp[*v].height + 1);
      }
      int q = el[u][0];
      for (; q != 0 && dp[q].dep <= dp[u].dep + v_height; q = pnext[q])
        pkey[q] = u;
      pnext[u] = q;
    }
  }

  for (int u = 2; u <= n; u++)
  {
    f[u] = 0x3f3f3f3f3f3f3f3f;
    if (pc[p[u]] == 1) f[u] = std::min(f[u], f[p[u]] + 1);
    if (pkey[u] != 0) f[u] = std::min(f[u], f[pkey[u]] + (dp[pkey[u]].leaf_sum - dp[u].leaf_sum - (int64_t)dp[u].leaf_cnt * (dp[u].dep - dp[pkey[u]].dep)));
    // printf("f[%d] = %" SCNi64 "\n", u, f[u]);
  }

  int64_t ans = 0x3f3f3f3f3f3f3f3f;
  for (int u = 1; u <= n; u++)
    if (pc[u] == 0)
      ans = std::min(ans, f[u]);
  printf("%" SCNi64 "\n", ans);

  return 0;
}
