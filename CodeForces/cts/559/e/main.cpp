#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <map>
#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int inf = 2e8;
constexpr int N = 105;
std::map<int,int> dp[N];
std::pair<int,int> seg[N];
int n;

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    seg[i].first = sc.next_int();
    seg[i].second = sc.next_int();
  }
  std::sort(seg, seg + n);

  dp[0][-inf] = 0;
  for (int i = 0; i < n; i++)
    for (const auto& [cr,cv] : dp[i])
    {
      int vr = -inf;
      for (int j = i; j < n; j++)
      {
        check_max(vr, seg[j].first); 
        check_max(dp[j + 1][vr], cv + vr - std::max(cr, seg[j].first - seg[j].second));
        check_max(vr, seg[j].first + seg[j].second);
        check_max(dp[j + 1][vr], cv + vr - std::max(cr, seg[j].first));
      }
    }

  int ans = 0;
  for (int i = 0; i <= n; i++)
    for (const auto& [cr,cv] : dp[i])
      check_max(ans, cv);
  std::cout << ans << std::endl;

  return 0;
}

