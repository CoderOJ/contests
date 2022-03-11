#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

std::vector<int> factors(int n)
{
  std::vector<int> res;
  for (int i = 1; i * i <= n; i++)
  {
    if (n % i == 0)
    {
      res.push_back(i);
      if (i * i != n)
        res.push_back(n / i);
    }
  }
  return res;
}

bool is_period(const std::vector<int> &a, int p)
{
  for (size_t i = 0; i + p < a.size(); i++)
    if (a[i] != a[i + p])
      return false;
  return true;
}

int main()
{
  int n = sc.next_int();

  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; i++)
  {
    a[i].first  = sc.next_int();
    a[i].second = sc.next_int();
  }

  std::vector<int> ans;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (a[i].second != a[j].second)
        ans += factors(std::abs(a[i].first - a[j].first));

  for (int i = 1; i <= n; i++)
  {
    [&] {
      std::vector<int> rem(i, -1);
      for (const auto &[k, v] : a)
      {
        int rem_k = (k % i + i) % i;
        if (rem[rem_k] != -1 && rem[rem_k] != v)
          return;
        rem[rem_k] = v;
      }
      if (std::any_of(rem.begin(), rem.end(), [](int v) { return v == -1; }))
        return;
      for (int j = 1; j < i; j++)
        if (i % j == 0 && is_period(rem, j))
        {
          ans.push_back(i);
          return;
        }
    }();
  }

  std::sort(ans.begin(), ans.end());
  ans.erase(std::unique(ans.begin(), ans.end()), ans.end());

  std::cout << ans.size() << " ";
  std::cout << std::accumulate(ans.begin(), ans.end(), 0ll) << std::endl;

  return 0;
}