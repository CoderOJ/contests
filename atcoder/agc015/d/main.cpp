#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <memory>
#include <type_traits>
#include <utility>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  uint64_t l = sc.next_long();
  uint64_t r = sc.next_long();

  auto ans
      = cm::y_combinate([&](auto &&self, uint64_t l, uint64_t r) -> uint64_t {
          auto solve = [&](uint64_t l, uint64_t r) -> uint64_t {
            if (l == r)
            {
              return 1;
            }
            else
            {
              if ((r & 1) == 0)
              {
                uint64_t pr = r ^ (1ull << __builtin_ctzll(r));
                if ((pr >> 1) >= (l >> 1))
                  return self(l, r + 1);
                else
                  return self(l, r + 1) - 1;
              }
              else if ((l & 1) == 1)
              {
                return self(l >> 1, r >> 1) + self((l >> 1) + 1, r >> 1);
              }
              else
              {
                return self(l >> 1, r >> 1) * 2;
              }
            }
          };

          static std::map<std::pair<uint64_t, uint64_t>, uint64_t> cache;

          auto it = cache.find({l, r});
          if (it != cache.end())
          {
            return it->second;
          }
          else
          {
            uint64_t a = solve(l, r);
            cache.insert({{l, r}, a});
            return a;
          }
        })(l, r);

  std::cout << ans << std::endl;

  return 0;
}
