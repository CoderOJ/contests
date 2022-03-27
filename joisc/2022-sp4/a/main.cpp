#include "dango3.h"
#include <algorithm>

void solve_range(const std::vector<int> &ids, int n, int m)
{
  if (m == 1)
  {
    Answer(ids);
  }
  else
  {
    int hm = m / 2;
    std::vector<int> ia = ids;
    std::vector<int> ib{};
    for (int x : ids)
    {
      ia.erase(std::find(ia.begin(), ia.end(), x));
      if (Query(ia) >= hm) { ib.push_back(x); }
      else { ia.push_back(x); }
    }
    solve_range(ia, n, hm);
    solve_range(ib, n, m - hm);
  }
}

void Solve(int N, int M)
{
  std::vector<int> ids;
  for (int i = 1; i <= N * M; i++)
    ids.push_back(i);
  solve_range(ids, N, M);
}
