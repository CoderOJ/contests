#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct dsu_t
{
  std::vector<int> p;
  std::vector<int> s;
  dsu_t(int n) : p(n), s(n)
  {
    for (int i = 0; i < n; i++)
    {
      p[i] = i;
      s[i] = 1;
    }
  }

  int get(int u)
  {
    return p[u] == u ? u : p[u] = get(p[u]);
  }

  void merge(int u, int v)
  {
    u = get(u);
    v = get(v);
    if (u != v)
    {
      p[v] = u;
      s[u] += s[v];
    }
  }
};

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();

  std::vector<std::tuple<int, int, int>> es;
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int w = sc.next_int();
    es.emplace_back(w, u, v);
  }

  std::vector<std::tuple<int, int, int>> et, eo;

  int64_t ans = 0;

  {
    dsu_t st(n);
    std::sort(es.begin(), es.end());
    std::reverse(es.begin(), es.end());
    for (auto [w, u, v] : es)
      if (st.get(u) != st.get(v))
      {
        et.emplace_back(w, u, v);
        u = st.get(u);
        v = st.get(v);
        ans += 1ll * st.s[u] * st.s[v] * w;
        st.merge(u, v);
      }
      else
      {
        eo.emplace_back(w, u, v);
      }
    int cur_size = 0;
    for (int i = 0; i < n; i++)
      if (st.p[i] == i)
      {
        ans += 1ll * cur_size * st.s[i] * 1;
        cur_size += st.s[i];
      }
  }

  {
    dsu_t st(n);
    auto  et_it = et.begin();
    for (const auto &[w, u, v] : eo)
    {
      while (et_it != et.end())
      {
        const auto &[tw, tu, tv] = *et_it;
        if (tw <= w)
          break;
        st.merge(tu, tv);
        et_it++;
      }
      if (st.get(u) == st.get(v))
      {
        puts("-1");
        return 0;
      }
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
