#include <bits/stdc++.h>

const int N = 50005;
int a[N], b[N], n, m;

bool check(int v)
{
  std::multiset<int> s{v};
  std::multiset<int> t(a, a + n);

  while (true)
  {
    if (t.empty())
      return true;
    else if (s.empty())
      return false;
    else if (s.size() >= t.size())
    {
      std::vector<int> ss(s.rbegin(), s.rend());
      std::vector<int> tt(t.rbegin(), t.rend());
      for (size_t i = 0; i < tt.size(); i++)
        if (ss[i] < tt[i])
          return false;
      return true;
    }
    else
    {
      int s0 = *std::prev(s.end());
      int t0 = *std::prev(t.end());
      if (s0 < t0)
        return false;
      else if (s0 < t0 + b[0])
      {
        s.erase(s.lower_bound(t0));
        t.erase(std::prev(t.end()));
      }
      else
      {
        s.erase(std::prev(s.end()));
        for (int i = 0; i < m; i++)
          s.insert(s0 - b[i]);
      }
    }
  }
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < m; i++) scanf("%d", &b[i]);
  std::sort(a, a + n);
  std::sort(b, b + m);

  int l = a[0], r = 1e9;
  while (l < r)
  {
    int m = l + (r - l) / 2;
    if (check(m))
      r = m;
    else
      l = m + 1;
  }

  std::cout << l << std::endl;

  return 0;
} 
