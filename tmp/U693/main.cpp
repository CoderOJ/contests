#include "subway.h"
#include <bits/stdc++.h>

namespace
{

int n, m, lim;

std::vector<std::pair<int, int>> st;
int zero_cnt = 0;

void rebuild()
{
  for (size_t i = 0; i < st.size(); i++)
    undo();
  std::reverse(st.begin(), st.end());
  for (size_t i = 0; i < st.size(); i++)
  {
    merge(st[i].first);
    st[i].second = 0;
    zero_cnt++;
  }
}

void push1(int id)
{
  st.push_back({id, 1});
  merge(id);
}

void pop0()
{
  if (zero_cnt == 0)
  {
    rebuild();
    undo();
    st.pop_back();
    zero_cnt--;
  }
  else
  {
    int cnt0 = 1 << __builtin_ctz(zero_cnt);
    std::vector<std::pair<int,int>> v0, v1;
    for (int c = 0; c < cnt0; )
    {
      if (st.back().second == 0)
      {
        v0.push_back(st.back());
        st.pop_back();
        undo();
        c++;
        zero_cnt--;
      }
      else
      {
        v1.push_back(st.back());
        st.pop_back();
        undo();
      }
    }
    while (!v1.empty())
    {
      st.push_back(v1.back());
      merge(v1.back().first);
      v1.pop_back();
    }
    while (v0.size() > 1)
    {
      st.push_back(v0.back());
      merge(v0.back().first);
      v0.pop_back();
      zero_cnt++;
    }
  }
}

int cur_r = 1;

}

void init(int n, int m, int lim)
{
  ::n = n;
  ::m = m;
  ::lim = lim;
}

int solve(int)
{
  while (cur_r <= m && check(cur_r))
  {
    push1(cur_r);
    cur_r++;
  }
  pop0();
  return cur_r - 1;
}
