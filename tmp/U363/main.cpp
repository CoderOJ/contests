#include "park.h"
#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <utility>

template <class F>
struct y_combinate_t
{
  F f;

  template <class... Args>
  decltype(auto) operator()(Args &&...args) const
  {
    return f(*this, std::forward<Args>(args)...);
  }
};

template <class F>
y_combinate_t<std::decay_t<F>> y_combinate(F &&f)
{
  return {std::forward<F>(f)};
};

template <class T, typename = typename T::iterator>
std::ostream &operator<< (std::ostream &out, const T &v)
{
  out << "{";
  bool is_first = true;
  for (const auto &x : v)
  {
    if (!is_first) out << ", ";
    else is_first = false;
    out << x;
  }
  out << "}";
  return out;
}

void Detect(int, int n)
{
  using uset_t = std::basic_string<int>;
  using uset_view = std::basic_string_view<int>;

  uset_t det_v{0};
  std::vector<uset_t> e(n);

  auto add_edge = [&](int u, int v) {
    if (u > v) std::swap(u, v);
    // printf("add_edge: %d %d\n", u, v);
    Answer(u, v);
    e[u] += v;
    e[v] += u;
  };

  auto query = [&](const uset_view &s, int u) -> bool {
    // std::cout << "query: s = " << s << " u = " << u << std::endl;
    if (s.empty())
      return false;
    std::vector<int> mask(n, 0);
    for (int u : s)
      mask[u] = 1;
    mask[u] = 1;

    int x = s[0], y = u;
    if (x > y) std::swap(x, y);
    return Ask(x, y, mask.data());
  };

  auto get_adj = y_combinate([&](auto get_adj, const uset_t &s, int u) -> void {
    // std::cout << "get_adj: " << s << " " << u << std::endl;
    if (!query(s, u))
      return;

    int ku = [&]{
      int l = 0, r = static_cast<int>(s.size()) - 1;
      while (l < r)
      {
        int m = l + (r - l + 1) / 2;
        if (query(uset_view(s.c_str(), m), u))
          r = m - 1;
        else
          l = m;
      }
      return s[l];
    }();
    add_edge(ku, u);

    std::vector<bool> vis(n, true);
    for (int u : s)
      vis[u] = false;
    vis[ku] = true;

    auto dfs = y_combinate([&](auto dfs, uset_t &s, int u) -> void {
      vis[u] = true;
      s.push_back(u);
      for (int v : e[u])
        if (!vis[v])
          dfs(s, v);
    });

    for (int v : e[ku])
      if (!vis[v])
      {
        uset_t vs;
        dfs(vs, v);
        get_adj(vs, u);
      }
  });

  auto insert = y_combinate([&](auto insert, int u) -> void {
    // printf("insert: %d\n", u);

    if (query(det_v, u))
    {
      get_adj(det_v, u);
      det_v += u;
    }
    else
    {
      int p = [&]{
        uset_t full = det_v;
        for (int i = 0; i < n; i++) full += i;
        int det_size = static_cast<int>(det_v.size());

        int l = 0, r = n - 1;
        while (l < r)
        {
          int m = l + (r - l + 1) / 2;
          if (query(uset_view(full.c_str(), det_size + m), u))
            r = m - 1;
          else
            l = m;
        }
        return l;
      }();

      insert(p);
      insert(u);
    }
  });

  for (int i = 0; i < n; i++)
    if (det_v.find(i) == uset_t::npos)
      insert(i);
}
