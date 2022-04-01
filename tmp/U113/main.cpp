#include <bits/stdc++.h>

const int MOD = 998244353;

int main()
{
  int n;
  scanf("%d", &n);
  std::vector<int> a{1};
  for (int i = 0; i < n - 1; i++)
  {
    char s[5];
    scanf("%s", s);
    if (s[0] == '&') a.back()++;
    else a.push_back(1);
  }
  int ans = 1;
  int cur = 1;
  for (int x : a)
  {
    cur = (1ll * cur * x) % MOD;
    ans = (ans + cur) % MOD;
  }
  printf("%d\n", ans);
  return 0;
}
