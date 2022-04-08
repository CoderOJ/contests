#include <bits/stdc++.h>

const int MOD = 998244353;

int solve(std::vector<int> &a, const std::vector<int> &b, int t)
{
  if (t == 0) return a == b;
  else
  {
    static std::map<std::pair<std::vector<int>, int>, int> mem;

    auto it = mem.find({a, t});
    if (it != mem.end()) return it->second;

    int ans = (a == b);
    bool is_first[3] = {true, true, true};
    for (size_t i = 0; i < a.size(); i++)
    {
      if (is_first[a[i]])
      {
        int c = a[i];
        for (int d = 0; d < 3; d++) if (d != c)
          if (is_first[d])
          {
            a[i] = d;
            ans = (ans + solve(a, b, t - 1)) % MOD;
          }
        a[i] = c;
      }
      is_first[a[i]] = false;
    }

    mem[{a, t}] = ans;
    return ans;
  }
}

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]), a[i]--;
  for (int i = 0; i < n; i++) scanf("%d", &b[i]), b[i]--;
  std::cout << solve(a, b, m) << std::endl;
  return 0;
}
