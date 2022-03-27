#include <bits/stdc++.h>

const int N = 2505;

char s[N];
int prev_c[N][N];
int prev[N][N];
int a, b, c;
int n;

void calc_prev()
{
  for (int l = 0; l < n; l++)
  {
    prev_c[l][l] = l - 1;
    for (int r = l; r < n; r++)
    {
      int p = prev_c[l][r];
      while (p != -1)
      {
        if (s[p + (r - l)] == s[r])
          break;
        p = prev_c[p][p + (r - l)];
      }
      prev_c[l][r + 1] = p;
      // printf("prev_c[%d][%d] = %d\n", l, r, prev_c[l][r]);
    }
  }
  for (int l = 0; l < n; l++)
    for (int r = l; r <= n; r++)
      prev[l][r] = prev_c[l][r];
  for (int l = n - 1; l >= 0; l--)
    for (int r = l; r <= n; r++)
    {
      while (prev[l][r] != -1)
      {
        if (prev[l][r] + (r - l) <= l)
          break;
        prev[l][r] = prev_c[prev[l][r]][prev[l][r] + (r - l)];
      }
      if (prev_c[l][r] != -1)
        prev[prev_c[l][r]][prev_c[l][r] + (r - l)] = prev[l][r];
    }
}

int64_t dp[N][N];
std::vector<int> due_len[N];
int len_cnt[N];

void calc_dp()
{
  for (int r = 1; r <= n; r++)
  {
    for (int i = 0; i <= r; i++)
      len_cnt[i] = 0;
    for (int l = 0; l < r; l++)
      due_len[l].push_back(r - l);

    for (int l = r - 1; l >= 0; l--)
    {
      dp[l][r] = std::min(dp[l][r - 1] + a, dp[l + 1][r] + a);
      for (int tl : due_len[l])
      {
        len_cnt[tl] += 1;
        dp[l][r] = std::min<int64_t>(dp[l][r], dp[l][l + tl] + b + 1ll * c * len_cnt[tl] + 1ll * a * (r - l - tl * len_cnt[tl]));
        int p = prev[l][l + tl];
        if (p != -1)
          due_len[p].push_back(tl);
      }
      due_len[l].clear();
    }
  }
}

int main()
{
  scanf("%d", &n);
  scanf("%s", s);
  scanf("%d%d%d", &a, &b, &c);

  calc_prev();
  calc_dp();

  std::cout << dp[0][n] << std::endl;

  return 0;
}
