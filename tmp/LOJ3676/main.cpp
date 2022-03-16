#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  int     a_min     = 0;
  int     a_min_cnt = 1;
  int     a_add     = 0;
  int     b_add     = 0;
  int64_t b_ams     = 0;

  node_t(const node_t &lhs, const node_t &rhs)
  {
    if (lhs.a_min < rhs.a_min)
    {
      a_min     = lhs.a_min;
      a_min_cnt = lhs.a_min_cnt;
      b_ams     = lhs.b_ams;
    }
    else if (lhs.a_min > rhs.a_min)
    {
      a_min     = rhs.a_min;
      a_min_cnt = rhs.a_min_cnt;
      b_ams     = rhs.b_ams;
    }
    else
    {
      a_min     = lhs.a_min;
      a_min_cnt = lhs.a_min_cnt + rhs.a_min_cnt;
      b_ams     = lhs.b_ams + rhs.b_ams;
    }
  }

  void push_a_add(int det)
  {
    a_min += det;
    a_add += det;
  }

  void push_b_add(int det)
  {
    b_ams += 1ll * a_min_cnt * det;
    b_add += det;
  }

  void push_down(node_t &lhs, node_t &rhs)
  {
    if (a_add != 0)
    {
      lhs.push_a_add(a_add);
      rhs.push_a_add(a_add);
      a_add = 0;
    }
    if (b_add != 0)
    {
      lhs.push_b_add(b_add);
      rhs.push_b_add(b_add);
      b_add = 0;
    }
  }
};

int main()
{
  int n = sc.next_int();
  int q = sc.next_int();

  std::vector<std::pair<int, int>> es;
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    es.emplace_back(u, v);
  }

  std::vector<int> t(n + 1);
  for (int i = 1; i < n; i++)
  {
    t[sc.next_int()] = i;
  }
  t[1] = n;

  cm::segment_tree<node_t> sgt(1, n);
  for (int i = 1; i < n; i++)
  {
    sgt.modify(i, i + 1, &node_t::push_a_add, n - i);
    sgt.modify(i, i + 1, &node_t::push_b_add, i);
  }

  auto add_edge = [&](int u, int v, int d) {
    int l = t[u];
    int r = t[v];
    if (l > r)
      std::swap(l, r);
    // see(1, l, d);
    // see(r, n, d);
    if (1 < l)
      sgt.modify(1, l, &node_t::push_a_add, d);
    if (r < n)
      sgt.modify(r, n, &node_t::push_b_add, d);
  };

  for (const auto &[u, v] : es)
  {
    add_edge(u, v, -1);
  }

  auto answer = [&]() -> int64_t {
    auto r = sgt.query(1, n);
    if (r.a_min == 1)
      return r.b_ams;
    else
      return 0;
  };

  std::cout << answer() << '\n';
  for (int i = 0; i < q; i++)
  {
    int du = sc.next_int();
    int dv = sc.next_int();
    add_edge(du, dv, 1);
    int iu = sc.next_int();
    int iv = sc.next_int();
    add_edge(iu, iv, -1);
    std::cout << answer() << '\n';
  }

  return 0;
}
