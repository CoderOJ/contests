#include <algorithm>
#include <vector>

#include "./kth.h"

int query_kth(int, int, int, int k)
{
  int s_a = 0, s_b = 0, s_c = 0;
  while (true)
  {
    if (k == 1)
    {
      return std::min({ get_a(s_a), get_b(s_b), get_c(s_c) });
    }
    else if (k == 2)
    {
      std::vector<int> a{ get_a(s_a), get_a(s_a + 1),
                          get_b(s_b), get_b(s_b + 1),
                          get_c(s_c), get_c(s_c + 1), };
      std::sort(a.begin(), a.end());
      return a[1];
    }
    else if (k == 3)
    {
      std::vector<int> a{ get_a(s_a), get_a(s_a + 1), get_a(s_a + 2),
                          get_b(s_b), get_b(s_b + 1), get_b(s_b + 2),
                          get_c(s_c), get_c(s_c + 1), get_c(s_c + 2), };
      std::sort(a.begin(), a.end());
      return a[2];
    }
    else
    {
      int l = (k - 1) / 3;
      int v_a = get_a(s_a + l - 1);
      int v_b = get_b(s_b + l - 1);
      int v_c = get_c(s_c + l - 1);
      int min_val = std::min({v_a, v_b, v_c});
      if (v_a == min_val) s_a += l;
      else if (v_b == min_val) s_b += l;
      else s_c += l;
      k -= l;
    }
  }
}
