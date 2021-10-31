#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int T = sc.next_int();
  for (int _ = 0; _ < T; _++)
  {
    int n = sc.next_int();
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 2; j >= 2; j--)
        if (a[i] % j != 0)
          goto ok;
      puts("NO");
      goto nok;
ok:;
    }
    puts("YES");
nok:;
  }
  return 0;
}
