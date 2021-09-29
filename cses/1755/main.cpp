#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);
constexpr int N = 1000005;
char s[N];
int cnt[128];

int main()
{
  size_t n = static_cast<size_t>(sc.next_token(s) - s); 
  for (size_t i = 0; i < n; i++)
    cnt[static_cast<int>(s[i])]++;

  int odd_cnt = 0;
  for (int i = 'A'; i <= 'Z'; i++)
    odd_cnt += cnt[i] % 2;
  if (odd_cnt > 1) { puts("NO SOLUTION"); return 0; }

  for (int i = 'A'; i <= 'Z'; i++)
    for (int j = 0; j < cnt[i] / 2; j++)
      putchar(i);
  for (int i = 'A'; i <= 'Z'; i++)
    if (cnt[i] % 2 == 1)
      putchar(i);
  for (int i = 'Z'; i >= 'A'; i--)
    for (int j = 0; j < cnt[i] / 2; j++)
      putchar(i);

  return 0;
}

