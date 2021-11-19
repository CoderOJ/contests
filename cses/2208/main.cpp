#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int T = sc.next_int();
  for (int i = 0; i < T; i++)
  {
    int n = sc.next_int();
    bool ans = false;
    for (int i = 0; i < n; i++)
      if (sc.next_int() % 2 == 1)
        ans = true;
    puts(ans ? "first" : "second");
  }
  return 0;
}

