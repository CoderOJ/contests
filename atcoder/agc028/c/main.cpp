#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <numeric>
#include <set>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int(), b[i] = sc.next_int();

  long long ans = std::min({
      std::accumulate(a.begin(), a.end(), 0ll),
      std::accumulate(b.begin(), b.end(), 0ll),
  });

  struct pkth_t
  {
    std::multiset<int> below, over;
    long long below_sum = 0;
    int k;

    pkth_t(int k) : k(k)
    {
    }

    void insert(int x)
    {
      if (below.empty() || x <= *--below.end())
        below.insert(x), below_sum += x;
      else
        over.insert(x);
      if ((int)below.size() > k)
      {
        over.insert(*--below.end());
        below_sum -= *--below.end();
        below.erase(--below.end());
      }
      if ((int)below.size() < k && !over.empty())
      {
        below_sum += *over.begin();
        below.insert(*over.begin());
        over.erase(over.begin());
      }
    }

    void erase(int x)
    {
      auto below_it = below.find(x);
      if (below_it != below.end())
      {
        below_sum -= x;
        below.erase(below_it);
      }
      else
        over.erase(over.find(x));
      if ((int)below.size() < k && !over.empty())
      {
        below_sum += *over.begin();
        below.insert(*over.begin());
        over.erase(over.begin());
      }
    }

    auto get_pkth_sum()
    {
      return below_sum;
    }
  };

  pkth_t pkth(n - 2);
  for (int i = 0; i < n; i++)
    pkth.insert(a[i]), pkth.insert(b[i]);
  for (int i = 0; i < n; i++)
  {
    pkth.erase(a[i]), pkth.erase(b[i]);
    see(i, a[i], b[i], pkth.get_pkth_sum());
    check_min(ans, a[i] + b[i] + pkth.get_pkth_sum());
    pkth.insert(a[i]), pkth.insert(b[i]);
  }

  std::cout << ans << std::endl;

  return 0;
}
