#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int              n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_char();

  std::vector<int> pre(n);
  int              occur[256];
  occur[(int)'G'] = occur[(int)'H'] = -1;
  for (int i = 0; i < n; i++)
    pre[i] = std::exchange(occur[a[i]], i);

  std::vector<int> suf(n);
  occur[(int)'G'] = occur[(int)'H'] = n;
  for (int i = n - 1; i >= 0; i--)
    suf[i] = std::exchange(occur[a[i]], i);

  long long ans = 0;
  for (int i = 0; i < n; i++)
    ans += 1ll * (i - pre[i]) * (suf[i] - i) - 1 - (i - pre[i] > 1) -
           (suf[i] - i > 1);
  std::cout << ans << std::endl;

  return 0;
}
