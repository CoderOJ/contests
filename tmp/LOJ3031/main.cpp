#include "meetings.h"
#include <algorithm>
#include <map>
#include <random>
#include <tuple>
#include <vector>

namespace
{

void add_edge(int u, int v)
{
  std::apply(Bridge, std::minmax(u, v));
}

void solve(std::vector<int> us)
{
  static std::mt19937 rd(18100301);
  std::shuffle(us.begin(), us.end(), rd);
  if (us.size() == 1) {}
  else if (us.size() == 2)
  {
    add_edge(us[0], us[1]);
  }
  else
  {
    int ru = us[0];
    int rv = us[1];
    us.erase(us.begin(), us.begin() + 2);
    std::map<int, std::vector<int>> vu;
    vu[ru] = {ru};
    vu[rv] = {rv};
    for (int u : us)
      vu[Query(ru, rv, u)].push_back(u);

    std::vector<int> keys;
    for (auto &[k, v] : vu)
    {
      keys.push_back(k);
      solve(std::move(v));
    }
    solve(std::move(keys));
  }
}

} // namespace

void Solve(int n)
{
  std::vector<int> us(n);
  for (int i = 0; i < n; i++)
    us[i] = i;
  solve(std::move(us));
}
