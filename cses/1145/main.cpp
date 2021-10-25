#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  std::vector<int> vals(a.begin(), a.end());
  std::sort(vals.begin(), vals.end());
  vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
  for (int &x : a)
    x = static_cast<int>(std::lower_bound(vals.begin(), vals.end(), x) - vals.begin());

  std::vector<int> min_end(n + 1, static_cast<int>(vals.size()));
  min_end[0] = -1;
  int ans = 0;
  for (int x : a)
  {
    int cur_ans = static_cast<int>(std::lower_bound(min_end.begin(), min_end.end(), x) - min_end.begin());
    check_max(ans, cur_ans);
    check_min(min_end[cur_ans], x);
  }

  printf("%d\n", ans);

  return 0;
}

