#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <set>

cm::scanner<cm::optimal_reader> sc(stdin);

template <class T>
struct h2h_t
{
  // lower.size() == upper.size() + [0,1]
  std::multiset<T> lower, upper;
  T median() { return *lower.rbegin(); }
  void adjust()
  {
    while (lower.size() > upper.size() + 1)
    {
      upper.emplace(*lower.rbegin());
      lower.erase(--lower.end());
    }
    while (upper.size() > lower.size())
    {
      lower.insert(*upper.begin());
      upper.erase(upper.begin());
    }
  }
  void insert(const T &x)
  {
    if (lower.empty())
    {
      lower.insert(x);
      return;
    }

    if (median() < x)
      upper.insert(x);
    else
      lower.insert(x);
    adjust();
  }
  void erase(const T &x)
  {
    auto low_it = lower.find(x);
    if (low_it != lower.end())
      lower.erase(low_it);
    else
      upper.erase(upper.find(x));
    adjust();
  }
  void log()
  {
    see(lower);
    see(upper);
  }
};

int main()
{
  int n = sc.next_int(), k = sc.next_int();
  std::vector<int> a(n);
  h2h_t<int> h;
  for (int i = 0; i + 1 < k; i++)
    h.insert(a[i] = sc.next_int());
  for (int i = k - 1; i < n; i++)
  {
    h.insert(a[i] = sc.next_int());
    printf("%d ", h.median());
    h.erase(a[i - k + 1]);
  }
  puts("");
  return 0;
}

