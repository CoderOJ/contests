#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1000005;
char s[N];

int main()
{
  sc.next_token(s);
  char last = 0;
  int ans = 0, cur = 0;
  for (char *c = s; *c; c++)
  {
    if (*c == last)
      cur++;
    else
    {
      last = *c;
      cur = 1;
    }
    check_max(ans, cur);
  }

  std::cout << ans << std::endl;
  return 0;
}

