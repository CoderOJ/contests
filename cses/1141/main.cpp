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
  std::map<int,int> pos;

  int l = 0, ans = 0;
  for (int i = 1; i <= n; i++)
  {
    int a = sc.next_int();
    check_max(l, std::exchange(pos[a], i));
    check_max(ans, i - l);
  }

  std::cout << ans << std::endl;

  return 0;
}

