#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 5'000'005;

char s[N];
char t[N];
int  n;

int main()
{
  n = sc.next_int();
  sc.next_token(s);
  sc.next_token(t);

  int det = 0;
  int cur = 0;
  for (int i = n - 1; i >= 0; i--)
  {
    if (det == 0 && s[cur] == t[i])
    {
      cur += 1;
    }
    else
    {
      det += t[i] == 'Y' ? 1 : -1;
      det -= s[i + cur] == 'Y' ? 1 : -1;
    }
  }

  if (det != 0)
  {
    puts("0");
  }
  else
  {
    int64_t ans = 0;
    for (int i = 0; i < cur; i++)
      if (s[i] == t[0])
        ans += i + 1;
    std::cout << ans << std::endl;
  }

  return 0;
}
