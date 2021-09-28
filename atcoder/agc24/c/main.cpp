#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  if (a[0] != 0) { puts("-1"); return 0; }

  std::vector<int> last(n, 0);

  long long ans = 0;
  for (int i = 1; i < n; i++)
  {
    if (a[i] > a[i-1] + 1) { puts("-1"); return 0; }
    if (a[i]) ans += a[i] - last[i - a[i]];
    see(i, a[i], a[i] - last[i - a[i]]);
    last[i - a[i]] = a[i];
  }
  std::cout << ans << std::endl;
  return 0;
}

