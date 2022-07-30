#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <map>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  using point_t = std::pair<int, int>;

  int n = sc.next_int();

  std::vector<point_t> ps(n);
  for (int i = 0; i < n; i++)
  {
    ps[i].first  = sc.next_int() * 2;
    ps[i].second = sc.next_int() * 2;
  }
  std::sort(ps.begin(), ps.end());

  using state_t = std::pair<point_t, point_t>;

  auto distance = [](const point_t &a, const point_t &b) {
    auto dx = a.first - b.first;
    auto dy = a.second - b.second;
    return (int64_t)dx * dx + (int64_t)dy * dy;
  };

  auto median = [](auto &&v) {
    cm_assert(!v.empty());

    int n = (int)v.size();

    if (n % 2 == 1)
    {
      std::nth_element(v.begin(), v.begin() + n / 2, v.end());
      return v[n / 2];
    }
    else
    {
      std::nth_element(v.begin(), v.begin() + n / 2, v.end());
      auto v2 = v[n / 2];
      auto v1 = *std::max_element(v.begin(), v.begin() + n / 2);
      return (v1 + v2) / 2;
    }
  };

  auto get_partition_rc = [&](const state_t &st) {
    std::vector<int> rax, ray;
    std::vector<int> rbx, rby;
    for (const auto &p: ps)
    {
      auto da = distance(st.first, p);
      auto db = distance(st.second, p);
      if (da <= db)
      {
        rax.push_back(p.first);
        ray.push_back(p.second);
      }
      else
      {
        rbx.push_back(p.first);
        rby.push_back(p.second);
      }
    }

    // see(st);
    // see(rax, ray);
    // see(rbx, rby);

    state_t res
        = {{median(std::move(rax)), median(std::move(ray))},
           {median(std::move(rbx)), median(std::move(rby))}};
    if (res.first > res.second)
      std::swap(res.first, res.second);

    return res;
  };

  auto get_final = [&] {
    using res_t = std::pair<state_t, int>;

    auto mem = std::make_unique<std::map<state_t, res_t>>();

    return cm::y_combinate(
        [&, mem = std::move(mem)](auto &&self, const state_t &st) -> res_t {
          auto mem_it = mem->find(st);

          if (mem_it != mem->end())
            return mem_it->second;
          else
          {
            auto next_st = get_partition_rc(st);

            if (next_st == st)
            {
              mem->insert({st, {st, 1}});
              return {st, 1};
            }
            else
            {
              res_t ns_res = self(next_st);
              res_t res    = {ns_res.first, ns_res.second + 1};
              mem->insert({st, res});
              return res;
            }
          }
        });
  }();

  using fraction_t = std::pair<int64_t, int>;
  std::map<state_t, fraction_t> ans;
  for (int i = 0; i < (int)ps.size(); i++)
    for (int j = i + 1; j < (int)ps.size(); j++)
    {
      auto  res = get_final(state_t(ps[i], ps[j]));
      auto &ap  = ans[res.first];
      ap.first += res.second;
      ap.second += 1;
    }

  for (const auto &[p, q]: ans)
  {
    printf(
        "%.6f %.6f %.6f %.6f %.12f\n",
        p.first.first / 2.,
        p.first.second / 2.,
        p.second.first / 2.,
        p.second.second / 2.,
        (double)q.first / q.second);
  }

  return 0;
}
