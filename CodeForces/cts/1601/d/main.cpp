#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int(), d = sc.next_int();
  std::vector<std::pair<int,int>> a(n);
  for (int i = 0; i < n; i++)
    a[i].first = sc.next_int(), a[i].second = sc.next_int();
  std::sort(a.begin(), a.end(), [](auto a, auto b) {
    auto am = std::max(a.first, a.second), bm = std::max(b.first, b.second);
    return am != bm ? am < bm : (a.first < a.second) > (b.first < b.second); });
  int ans = 0;
  for (const auto & [s,a] : a) {
    if (d <= s) { ans++; check_max(d, a); } }
  printf("%d\n", ans);
  return 0;
}

