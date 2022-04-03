#include <bits/stdc++.h>

std::map<int, std::vector<int>> occur;
int n;

std::vector<int> ans;

void solve(const std::vector<int> vals, int t)
{
  if (vals.size() == 0)
  {
  }
  else if (vals.size() == 1)
  {
    for (int p : occur[vals[0]])
      ans.push_back(p);
  }
  else
  {
    std::vector<int> lhs, rhs;
    for (int x : vals)
    {
      if ((x >> t) % 2 == 0) lhs.push_back(x);
      else rhs.push_back(x);
    }
    solve(lhs, t + 1);
    solve(rhs, t + 1);
  }
}

int main()
{
  scanf("%d", &n);
  std::vector<int> vals;
  for (int i = 0; i < n; i++)
  {
    int x;
    scanf("%d", &x);
    occur[x].push_back(i);
    vals.push_back(x);
  }
  std::sort(vals.begin(), vals.end());
  vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
  solve(vals, 0);
  for (int x : ans) printf("%d ", x + 1);
  puts("");
  return 0;
}
