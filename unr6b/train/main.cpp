#include <bits/stdc++.h>

int main()
{
  int n;
  int64_t p;
  scanf("%d%" SCNi64, &n, &p);

  std::vector<int64_t> as(n);
  for (int i = 0; i < n; i++)
    scanf("%" SCNi64, &as[i]);

  auto get_ssum = [p](const std::vector<int64_t> &a) {
    int n = (int)a.size();
    std::vector<std::pair<int64_t, uint32_t>> r(1 << n);
    r[0] = {0, 0};
    for (uint32_t i = 1; i < (1u << n); i++) 
    {
      int lb = __builtin_ctz(i);
      r[i] = {(r[i ^ (1 << lb)].first + a[lb]) % p, i};
    }
    std::sort(r.begin(), r.end());
    return r;
  };

  int n0 = n / 2;
  int n1 = n - n0;
  auto a0 = get_ssum({as.begin(), as.begin() + n0});
  auto a1 = get_ssum({as.begin() + n0, as.end()});

  auto pairs_bt = [&](int64_t sl, int64_t sr) {
    int64_t ans = 0;
    auto b0l = a1.begin(), b0r = a1.begin();
    auto b1l = a1.begin(), b1r = a1.begin();
    for (auto ai = a0.rbegin(); ai != a0.rend(); ai++)
    {
      int64_t ac = ai->first;
      while (b0r != a1.end() && ac + b0r->first < sr) b0r++;
      while (b0l != a1.end() && ac + b0l->first < sl) b0l++;
      while (b1r != a1.end() && ac + b1r->first < p + sr) b1r++;
      while (b1l != a1.end() && ac + b1l->first < p + sl) b1l++;
      ans += std::distance(b0l, b0r);
      ans += std::distance(b1l, b1r);
    }
    return ans;
  };

  int64_t al = 0, ar = p;
  while (ar - al > 1)
  {
    int64_t am = al + (ar - al) / 2;
    if (pairs_bt(al, am) > am - al)
      ar = am;
    else
      al = am;
  }
  
  std::vector<std::pair<uint64_t, uint64_t>> ps;
  auto b0 = a1.begin(), b1 = a1.begin();
  for (auto ai = a0.rbegin(); ai != a0.rend() && ps.size() < 2; ai++)
  {
    int64_t ac = ai->first;
    while (b0 != a1.end() && ac + b0->first < al) b0++;
    while (b1 != a1.end() && ac + b1->first < p + al) b1++;
    for (auto i = b0; i != a1.end() && ac + i->first == al; i++)
      ps.emplace_back(ai->second, i->second);
    for (auto i = b1; i != a1.end() && ac + i->first == p + al; i++)
      ps.emplace_back(ai->second, i->second);
  }

  auto print_ans = [&](std::pair<uint32_t, uint32_t> p0, std::pair<uint32_t, uint32_t> p1) {
    auto dump = [](uint32_t x, uint32_t y, int n) {
      for (int i = 0; i < n; i++)
      {
        int bx = (x >> i) & 1;
        int by = (y >> i) & 1;
        if (bx == by)
          printf("0 ");
        else if (bx == 1)
          printf("1 ");
        else
          printf("-1 ");
      }
    };
    dump(p0.first, p1.first, n0);
    dump(p0.second, p1.second, n1);
    puts("");
  };

  print_ans(ps[0], ps[1]);

  return 0;
}
