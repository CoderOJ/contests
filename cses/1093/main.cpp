#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int sum = n * (n + 1) / 2;
  if (sum % 2 == 1) { puts("0"); return 0; }
  std::vector<int> cnt(sum / 2 + 1, 0);
  cnt[0] = 1;
  for (int i = 1; i <= n; i++)
    for (int j = sum / 2; j >= i; j--)
      cnt[j] = (cnt[j] + cnt[j - i]) % 1'000'000'007;
  std::cout << cnt[sum / 2] * 500000004ll % 1'000'000'007 << std::endl;
  return 0;
}

