#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <map>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long
  int n = sc.next_int();
  std::map<int, int> cnt;

  cnt[0]++;
  int cur = 0;
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    cur += a;
    cur = ((cur % n) + n) % n;
    if (cnt.count(cur))
      ans += cnt[cur];
    cnt[cur]++;
  }
  std::cout << ans << std::endl;
  return 0;
}

