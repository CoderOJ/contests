#include "tree.h"
#include <bits/stdc++.h>

std::vector<std::pair<int, int>> solve(int n)
{
  std::vector<std::pair<int, int>> res;

  std::vector<std::vector<int>> comp{{}};
  for (int u = 0; u < n; u++)
    comp[0].push_back(u);

  for (int t = 1; t < (n - 1); t <<= 1)
  {
    // see(comp);
    // int t_cnt = 0;

    std::vector<std::vector<int>> cids(n);
    for (int i = 0; i < (int)comp.size(); i++)
      for (int u: comp[i])
      {
        cids[u].push_back(i);
        // t_cnt += 1;
      }

    // fprintf(stderr, "t_cnt = %d\n", t_cnt);

    std::vector<std::vector<int>> r_comp;
    {
      std::vector<int> mask(n - 1, 0);
      for (int i = 0; i < (n - 1); i++)
        if (i & t)
          mask[i] = 1;
      auto r = query(mask);
      r_comp.insert(r_comp.end(), r.begin(), r.end());
    }
    {
      std::vector<int> mask(n - 1, 1);
      for (int i = 0; i < (n - 1); i++)
        if (i & t)
          mask[i] = 0;
      auto r = query(mask);
      r_comp.insert(r_comp.end(), r.begin(), r.end());
    }

    std::vector<std::vector<int>> v_comp;
    for (const auto &cc: r_comp)
      if (cc.size() >= 2)
      {
        std::vector<std::pair<int, int>> ucs;
        for (int u: cc)
          for (int ci: cids[u])
            ucs.emplace_back(ci, u);

        std::sort(ucs.begin(), ucs.end());
        for (auto itl = ucs.begin(), itr = itl; itl != ucs.end(); itl = itr)
        {
          while (itr != ucs.end() && itl->first == itr->first)
            itr++;
          if (std::distance(itl, itr) >= 2)
          {
            std::vector<int> vc;
            for (auto it = itl; it != itr; it++)
              vc.push_back(it->second);
            v_comp.emplace_back(std::move(vc));
          }
        }
      }

    std::sort(v_comp.begin(), v_comp.end());
    v_comp.erase(std::unique(v_comp.begin(), v_comp.end()), v_comp.end());

    for (const auto &cc: v_comp)
      if (cc.size() == 2)
      {
        const auto &[u, v] = std::minmax(cc[0], cc[1]);
        res.emplace_back(u, v);
      }

    comp = std::move(v_comp);
  }

  std::sort(res.begin(), res.end());
  res.erase(std::unique(res.begin(), res.end()), res.end());

  // see(res);

  return res;
}
