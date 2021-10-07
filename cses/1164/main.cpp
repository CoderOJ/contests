#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <set>
#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

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

  std::sort(a.begin(), a.end(), [](inter_t a, inter_t b) { return a.r < b.r; });
  
  std::vector<size_t> ans(n);
  std::set<std::pair<int,size_t>> vs;
  for (const auto& [l,r,id] : a)
  {
    auto it = vs.lower_bound(std::make_pair(l,0));
    if (it == vs.begin())
    {
      ans[id] = vs.size();
      vs.insert(std::make_pair(r, vs.size()));
    }
    else
    {
      --it;
      ans[id] = it->second;
      vs.erase(it);
      vs.insert(std::make_pair(r, ans[id]));
    }
  }

  std::cout << vs.size() << std::endl;
  for (auto x: ans) std::cout << x + 1 << " ";
  std::cout << std::endl;

  return 0;
}

