#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cinttypes>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  using dp_t = std::vector<int64_t>;

  auto dp_join = [](const dp_t &lhs, const dp_t &rhs) {
    dp_t res;
    res.reserve(lhs.size() + rhs.size() - 1);
    for (auto lt = lhs.begin(), rt = rhs.begin();
         lt != lhs.end() && rt != rhs.end();)
    {
      res.push_back(*lt + *rt);
      if (std::next(rt) == rhs.end() ||
          (std::next(lt) != lhs.end() &&
           *std::next(lt) + *rt > *lt + *std::next(rt)))
        lt = std::next(lt);
      else
        rt = std::next(rt);
    }
    return res;
  };

  auto dp_max = [](const dp_t &lhs, const dp_t &rhs) {
    dp_t r(std::max(lhs.size(), rhs.size()));
    std::copy(lhs.begin(), lhs.end(), r.begin());
    for (size_t i = 0; i < rhs.size(); i++)
      r[i] = std::max(r[i], rhs[i]);
    return r;
  };

  auto solve =
      cm::y_combinate([&](auto f, int l, int r) -> cm::array<dp_t, 2, 2> {
        if (r - l == 1)
        {
          cm::array<dp_t, 2, 2> r;
          r[0][0] = {0};
          r[0][1] = {0};
          r[1][0] = {0};
          r[1][1] = {0, a[l]};
          return r;
        }
        else
        {
          int  m  = l + (r - l) / 2;
          auto ls = f(l, m);
          auto rs = f(m, r);

          cm::array<dp_t, 2, 2> r;
          for (int ax = 0; ax < 2; ax++)
            for (int ay = 0; ay < 2; ay++)
              for (int bx = 0; bx < 2; bx++)
                for (int by = 0; by < 2; by++)
                  if (ay == 0 || bx == 0)
                    r[ax][by] =
                        dp_max(r[ax][by], dp_join(ls[ax][ay], rs[bx][by]));

          return r;
        }
      });

  auto dp_ans = solve(0, n);
  auto ans    = dp_max(dp_max(dp_ans[0][0], dp_ans[0][1]),
                    dp_max(dp_ans[1][0], dp_ans[1][1]));

  for (int i = 1; i * 2 - 1 <= n; i++)
    printf("%" SCNi64 "\n", ans[i]);

  return 0;
}
