#include "library.h"
#include <algorithm>
#include <tuple>
#include <utility>

void Solve(int n)
{
  if (n == 1)
  {
    Answer({1});
    return;
  }

  std::vector<std::vector<int>> e(n + 1);

  auto query = [&](const std::vector<int> &a) {
    std::vector<int> b(n);
    for (int x : a)
      b[x - 1] = 1;
    return Query(b);
  };

  for (int i = 1; i <= n; i++)
    while (e[i].size() < 2)
    {
      std::vector<int> us;
      for (int j = 1; j <= n; j++)
        if (j != i && std::find(e[i].begin(), e[i].end(), j) == e[i].end())
          us.push_back(j);
      us.push_back(-1);

      auto itl = us.begin(), itr = us.end();
      while (std::next(itl) != itr)
      {
        auto itm = std::next(itl, std::distance(itl, itr) / 2);

        std::vector<int> qu(itl, itm);

        int a0 = query(qu);
        qu.push_back(i);
        int a1 = query(qu);

        if (a1 <= a0)
          itr = itm;
        else
          itl = itm;
      }

      if (*itl != -1)
      {
        e[i].push_back(*itl);
        e[*itl].push_back(i);
      }
      else
      {
        break;
      }
    }

  std::vector<int> ans;

  int u = static_cast<int>(std::distance(
      e.begin(),
      std::find_if(e.begin(), e.end(), [](auto x) { return x.size() == 1; })));

  ans.push_back(u);
  for (int p = u, q = e[u][0]; q != 0;)
  {
    ans.push_back(q);
    int vq = 0;
    for (int v : e[q])
      vq ^= v;
    vq ^= p;
    std::tie(p, q) = std::make_pair(q, vq);
  }

  Answer(ans);
}
