#include "Bruno.h"
#include <utility>
#include <vector>

namespace {

}

long long Bruno(std::vector<int> u) {

  int cur_01 = 0;
  std::vector<int> ans;
  int cur = 0;
  for (int x: u)
  {
    if (x == cur_01)
    {
      cur_01 = !cur_01;
    }
    else
    {
      if (x == 0)
      {
        cur += 1;
        if (cur >= 2) ans.push_back(0), cur = -1;
      }
      else
      {
        cur -= 1;
        if (cur <= -2) ans.push_back(1), cur = 1;
      }
    }
  }

  long long num = 0;
  for (int i = 0; i < (int)ans.size(); i++)
    num |= (long long)(ans[i]) << i;

  return num;
}
