#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  auto primes = [&] {
    const int lim = 1'000'005;

    std::vector<bool> is_prime(lim, true);
    std::vector<int>  primes;
    for (int i = 2; i < lim; i++)
      if (is_prime[i])
      {
        primes.push_back(i);
        for (int j = i + i; j < lim; j += i)
          is_prime[j] = false;
      }

    return primes;
  }();

  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    uint64_t l = sc.next_long();
    uint64_t r = sc.next_long() + 1;

    using basis_t = std::vector<uint64_t>;

    auto basis_insert = [](basis_t &bs, uint64_t v) {
      for (int i = 39; i >= 0; i--)
        if (v & (1ull << i))
        {
          if (bs[i] != 0)
            v ^= bs[i];
          else
          {
            bs[i] = v;
            break;
          }
        }
    };

    auto get_basis = [&](uint64_t pre, int pn) {
      if (pn < 13)
      {
        std::vector<bool> isp(1 << pn, true);
        for (int p: primes)
        {
          int st = (int)(pre % p);
          st     = (st == 0) ? 0 : p - st;
          if ((uint64_t)p == pre + st)
            st += p;
          for (int i = st; i < (1 << pn); i += p)
            isp[i] = false;
        }

        basis_t res(40, 0);
        for (int i = 0; i < (1 << pn); i++)
          if (isp[i])
            basis_insert(res, pre + i);

        return res;
      }
      else
      {
        basis_t res(40, 0);
        basis_insert(res, pre + 1);
        for (uint64_t i = 2; i < (1ull << pn); i <<= 1)
          basis_insert(res, pre + i + 1);
        return res;
      }
    };

    auto ans = //
        cm::y_combinate([&](auto &&self, uint64_t l, uint64_t r) -> basis_t {
          if (l == r)
          {
            return basis_t(40, 0);
          }
          else
          {
            if (l == 2)
            {
              // see("split: 2");
              auto res = self(3, r);
              basis_insert(res, 2);
              return res;
            }
            else
            {
              int pn = 0;
              while ((l & (1ull << pn)) == 0 && l + (1ull << (pn + 1)) <= r)
                pn += 1;

              // see("split", l, pn);

              auto l_res = get_basis(l, pn);
              auto r_res = self(l + (1ull << pn), r);
              for (int i = 0; i < 40; i++)
                if (l_res[i])
                  basis_insert(r_res, l_res[i]);

              return r_res;
            }
          }
        })(l, r);

    // see(ans);
    int ans_cnt = 0;
    for (int i = 0; i < 40; i++)
      if (ans[i] != 0)
        ans_cnt += 1;

    std::cout << (1ull << ans_cnt) << std::endl;
  }
  return 0;
}
