#include <bits/stdc++.h>

const int MOD = 998244353;

int main()
{
  int n, v;
  scanf("%d%d", &n, &v);
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  std::sort(a.begin(), a.end());

  std::vector<std::vector<std::vector<int>>> pref_knap(n + 1);
  pref_knap[0] = {{1}};
  for (int i = 0; i < n; i++)
  {
    pref_knap[i + 1] = pref_knap[i];
    pref_knap[i + 1].push_back(std::vector<int>((i + 1) * v + 1, 0));
    for (int j = 0; j <= i; j++)
      for (int k = 0; k <= j * v; k++)
        (pref_knap[i + 1][j + 1][k + a[i]] += pref_knap[i][j][k]) %= MOD;
  }

  std::vector<std::vector<std::vector<int>>> suff_knap(n + 1);
  suff_knap[n] = {{1}};
  for (int i = n - 1; i >= 0; i--)
  {
    suff_knap[i] = suff_knap[i + 1];
    suff_knap[i].push_back(std::vector<int>((n - i) * v + 1, 0));
    for (int j = 0; j <= (n - i - 1); j++)
      for (int k = 0; k <= j * v; k++)
        (suff_knap[i][j + 1][k + a[i]] += suff_knap[i + 1][j][k]) %= MOD;
  }

  for (auto &a : pref_knap)
    for (auto &b : a)
      for (size_t i = 1; i < b.size(); i++)
        b[i] = (b[i] + b[i - 1]) % MOD;

  int ans = 0;
  for (int i = 1; i < n - 1; i++)
    for (int j = 1; j <= std::min(i, n - i - 1); j++)
      for (int d = 0; d <= std::min(j * (v - a[i]), j * a[i] - 1); d++)
        ans = (ans + 1ll * pref_knap[i][j][a[i] * j - d - 1] * suff_knap[i + 1][j][a[i] * j + d]) % MOD;

  printf("%d\n", ans);

  return 0;
}
