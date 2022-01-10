#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200005;
int           a[N], n, k;

int main()
{
  n = sc.next_int();
  k = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  std::set<int> s(a, a + k);

  int ans = n - k + 1;
  for (int i = 0; i + k < n; i++)
  {
    s.emplace(a[i + k]);
    if (*s.begin() == a[i] && *s.rbegin() == a[i + k])
      ans--;
    s.erase(a[i]);
  }

  int scnt = 0;
  for (int i = 0; i + 1 < k; i++)
    scnt += a[i + 1] > a[i];
  bool last_scnt = false;
  bool have_stable = false;
  for (int i = 0; i + k <= n; i++)
  {
    bool cur_scnt = scnt == (k - 1);
    if (last_scnt == false && cur_scnt == true)
    {
      ans--;
      have_stable = true;
    }
    last_scnt = cur_scnt;
    scnt -= a[i + 1] > a[i];
    scnt += a[i + k] > a[i + k - 1];
  }
  ans += have_stable;

  std::cout << ans << std::endl;

  return 0;
}
