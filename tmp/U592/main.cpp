#include "meeting.h"
#include <bits/stdc++.h>

int mex(const std::vector<int> &a)
{
  std::set<int> s(a.begin(), a.end());
  for (int i = 0; ; i++)
    if (!s.count(i))
      return i;
}

std::vector<std::vector<int>> 
get_independent(
    std::vector<int> us, 
    const std::vector<std::pair<int, int>> &es)
{
  std::map<int, std::vector<int>> adj;
  for (const auto &[u, v] : es)
  {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  std::sort(us.begin(), us.end(), [&](int u, int v) {
    return adj[u].size() > adj[v].size();
  });
  std::map<int, int> color;
  for (int u : us)
  {
    std::vector<int> adj_color;
    for (int v : adj[u])
      if (color.count(u))
        adj_color.push_back(color[v]);
    color[u] = mex(adj_color);
  }
  std::vector<std::vector<int>> res;
  for (const auto &[u, c] : color)
  {
    if (c >= (int)res.size())
      res.resize(c + 1);
    res[c].push_back(u);
  }
  return res;
}

void find_edge(
    std::vector<std::pair<int, int>> &ans,
    std::vector<int> ul,
    std::vector<int> ur)
{
  if (ul.empty() || ur.empty())
    return;
  std::vector<int> u;
  u.insert(u.begin(), ul.begin(), ul.end());
  u.insert(u.begin(), ur.begin(), ur.end());
  if (!meeting(std::move(u)))
  {
    if (ul.size() == 1 && ur.size() == 1)
    {
      ans.emplace_back(ul[0], ur[0]);
    }
    else
    {
      find_edge(ans, std::vector<int>(ul.begin(), ul.begin() + ul.size() / 2), std::vector<int>(ur.begin(), ur.begin() + ur.size() / 2));
      find_edge(ans, std::vector<int>(ul.begin(), ul.begin() + ul.size() / 2), std::vector<int>(ur.begin() + ur.size() / 2, ur.end()));
      find_edge(ans, std::vector<int>(ul.begin() + ul.size() / 2, ul.end()), std::vector<int>(ur.begin(), ur.begin() + ur.size() / 2));
      find_edge(ans, std::vector<int>(ul.begin() + ul.size() / 2, ul.end()), std::vector<int>(ur.begin() + ur.size() / 2, ur.end()));
    }
  }
}

std::vector<std::pair<int, int>> 
solve_set(std::vector<int> us)
{
  static std::mt19937 rd(18100222);

  if (us.size() == 1) 
    return {};
  else
  {
    std::shuffle(us.begin(), us.end(), rd);
    auto it_l = us.begin(), it_m = it_l + us.size() / 2, it_r = us.end();
    std::vector<int> ul(it_l, it_m);
    std::vector<int> ur(it_m, it_r);
    auto el = solve_set(ul);
    auto er = solve_set(ur);
    auto sl = get_independent(ul, el);
    auto sr = get_independent(ur, er);
    std::vector<std::pair<int, int>> res;
    res.insert(res.end(), el.begin(), el.end());
    res.insert(res.end(), er.begin(), er.end());
    find_edge(res, ul, ur);
    return res;
  }
}

std::vector<std::pair<int, int>> 
solve(int n)
{
  std::vector<int> us(n);
  std::iota(us.begin(), us.end(), 0);
  return solve_set(std::move(us));
}
