#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <functional>
#include <set>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<int> p(n, -1);
  std::multiset<int> sizes;
  for (int i = 0; i < n; i++)
    sizes.emplace(1);

  std::function<int(int)> get = [&](int u) {
    return p[u] < 0 ? u : p[u] = get(p[u]);
  };

  for (int i = 0; i < m; i++)
  {
    int u = get(sc.next_int() - 1);
    int v = get(sc.next_int() - 1);
    cm_assert(p[u] < 0, p[v] < 0);
    if (u != v)
    {
      sizes.erase(sizes.find(-p[u]));
      sizes.erase(sizes.find(-p[v]));
      p[v] += p[u];
      p[u] = v;
      sizes.insert(-p[v]);
    }
    std::cout << sizes.size() << " " << *--sizes.end() << std::endl;
  }
  return 0;
}
