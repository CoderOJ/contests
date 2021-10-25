#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int x = sc.next_int();
  std::vector<int> c(x + 1, 0);
  c[0] = 1;
  for (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    for (int i = a; i <= x; i++)
      c[i] = (c[i] + c[i - a]) % 1'000'000'007;
  }
  std::cout << c[x] << std::endl;
  return 0;
}

