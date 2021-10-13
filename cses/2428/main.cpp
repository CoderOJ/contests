#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <map>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int k = sc.next_int();
  std::map<int, int> cnt;
  std::vector<int> a(n);
  int l = 0, tot = 0;
  long long ans = 0;
  for (int r = 0; r < n;)
  {
    int cur = sc.next_int();
    a[r++] = cur;
    if (cnt[cur]++ == 0) tot++;
    while (tot > k)
    {
      if (--cnt[a[l++]] == 0)
        tot--;
    }
    ans += r - l;
  }
  std::cout << ans << std::endl;

  return 0;
}

