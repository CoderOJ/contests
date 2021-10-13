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
  T lower_sum = T(), upper_sum = T();
  T median() { return *lower.rbegin(); }
  void adjust()
  {
    while (lower.size() > upper.size() + 1)
    {
      upper_sum += *lower.rbegin();
      lower_sum -= *lower.rbegin();
      upper.emplace(*lower.rbegin());
      lower.erase(--lower.end());
    }
    while (upper.size() > lower.size())
    {
      lower_sum += *upper.begin();
      upper_sum -= *upper.begin();
      lower.insert(*upper.begin());
      upper.erase(upper.begin());
    }
  }
  void insert(const T &x)
  {
    if (lower.empty())
    {
      lower.insert(x);
      lower_sum += x;
      return;
    }

    if (median() < x)
      upper.insert(x), upper_sum += x;
    else
      lower.insert(x), lower_sum += x;
    adjust();
  }
  void erase(const T &x)
  {
    auto low_it = lower.find(x);
    if (low_it != lower.end())
      lower.erase(low_it), lower_sum -= x;
    else
      upper.erase(upper.find(x)), upper_sum -= x;
    adjust();
  }
  T calc()
  {
    return upper_sum - median() * upper.size()
         - lower_sum + median() * lower.size();
  }
};

int main()
{

#define int long long

  int n = sc.next_int(), k = sc.next_int();
  std::vector<int> a(n);
  h2h_t<int> h;
  for (int i = 0; i + 1 < k; i++)
    h.insert(a[i] = sc.next_int());
  for (int i = k - 1; i < n; i++)
  {
    h.insert(a[i] = sc.next_int());
    printf("%lld ", h.calc());
    h.erase(a[i - k + 1]);
  }
  puts("");
  return 0;
}

