#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

struct ftree_t
{
  std::vector<int> a;
  ftree_t(size_t n) : a(n + 5) {}
  static size_t low(size_t x) { return x & (-x); }
  void modify(size_t pos, int val) { pos += 5;
    for (; pos < a.size(); pos += low(pos)) a[pos] += val; }
  int query(size_t pos) { pos += 5; int res = 0;
    for (; pos; pos -= low(pos)) res += a[pos]; return res; }
};

int main()
{
  struct inter_t
  {
    int l, r, id;
  };

  int n = sc.next_int();
  std::vector<inter_t> a;
  for (int i = 0; i < n; i++)
  {
    int l = sc.next_int(), r = sc.next_int();
    a.push_back({l, r, i});
  }

  {
    std::vector<int> values;
    for (const auto [l,r,id] : a)
      values.push_back(l), values.push_back(r);
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());
    for (auto& [l,r,id] : a)
    {
      l = static_cast<int>(std::lower_bound(values.begin(), values.end(), l) - values.begin());
      r = static_cast<int>(std::lower_bound(values.begin(), values.end(), r) - values.begin());
    }
  }

  {
    ftree_t st(n * 2 + 5);
    std::sort(a.begin(), a.end(), [](inter_t x, inter_t y) {
      return x.r != y.r ? x.r < y.r : x.l > y.l; });
    std::vector<int> ans(n, 0);
    for (const auto [l,r,id] : a)
    {
      see(l, r, id, st.query(r), st.query(l - 1));
      ans[id] = st.query(r) - st.query(l - 1);
      st.modify(l, 1);
    }
    for (int i : ans)
      std::cout << i << " ";
    std::cout << std::endl;
  }
  {
    ftree_t st(n * 2 + 5);
    std::sort(a.begin(), a.end(), [](inter_t x, inter_t y) {
      return x.l != y.l ? x.l < y.l : x.r > y.r; });
    std::vector<int> ans(n, 0);
    for (const auto [l,r,id] : a)
    {
      ans[id] = st.query(n * 2 + 2) - st.query(r - 1);
      st.modify(r, 1);
    }
    for (int i : ans)
      std::cout << i << " ";
    std::cout << std::endl;
  }
  return 0;
}

