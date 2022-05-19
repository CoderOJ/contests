#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    static char s[100];
    int n = static_cast<int>(sc.next_token(s) - s);
    if (n == 2)
    {
      printf("%c\n", s[1]);
    }
    else
    {
      printf("%c\n", *std::min_element(s, s + n));
    }
  }
  return 0;
}
