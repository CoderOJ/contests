#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);
  std::vector<std::vector<std::pair<int,int>>> ans;
  if (n % 2 == 0) ans = {{{1, 2}}};
  else ans = {{{1, 2}, {2, 3}}};
  for (int i = n % 2 ? 3 : 2; i + 2 <= n; i += 2)
  {
    for (int j = 0; j < (int)ans.size(); j++)
    {
      ans[j].emplace_back(i - j, i + 1);
      ans[j].emplace_back(1 + j, i + 2);
    }
    ans.push_back({{i + 1, i + 2}});
    for (int j = 1; j <= i; j++)
      ans.back().emplace_back(j, j <= i - j + 1 ? i + 1 : i + 2);
  }
  std::cout << ans.size() << std::endl;
  for (auto &v : ans) 
  {
    for (auto &x : v) printf("%d %d ", x.first, x.second); 
    puts("");
  }
  return 0;
}
