#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n + 1);
  for (int i = 0; i < n; i++)
    a[sc.next_int()] = i;

  int ans = 0;
  int last_pos = n + 1;
  for (int i = 1; i <= n; i++)
  {
    ans += a[i] < last_pos;
    last_pos = a[i];
  }

  std::cout << ans << std::endl;

  return 0;
}

