#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n + 1); a[0] = -1;
  std::vector<int> p(n + 1);
  for (int i = 1; i <= n; i++)
  {
    a[i] = sc.next_int();
    int pos = i - 1;
    while (a[pos] >= a[i]) pos = p[pos];
    p[i] = pos;
    printf("%d ", pos);
  }
  puts("");
  return 0;
}

