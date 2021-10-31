#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long

  int n = sc.next_int(), x = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  std::vector<int> valid(1 << n);
  for (int i = 0; i < (1 << n); i++)
  {
    int cur = 0;
    for (int j = 0; j < n; j++)
      if (i & (1 << j))
        cur += a[j];
    valid[i] = cur <= x;
  }

  for (int i = 0; i < n; i++)
    for (int j = 0; j < (1 << n); j++)
      if (j & (1 << i))
        valid[j] += valid[j ^ (1 << i)];

  auto ori = valid;
  for (int t = 1; ; t++)
  {
    int ans = 0;
    for (int i = 0; i < (1 << n); i++)
      ans += valid[i] * ((n - __builtin_popcountll(i)) % 2 ? -1 : 1);
    if (ans)
    {
      std::cout << t << std::endl;
      return 0;
    }
    for (int i = 0; i < (1 << n); i++)
      valid[i] *= ori[i];
  }
  return 0;
}

