#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  long long n = sc.next_long();
  int k = sc.next_int();
  std::vector<long long> ps(1 << k, 1);
  for (int i = 0; i < k; i++)
  {
    long long a = sc.next_long();
    for (int b = 0; b < (1 << k); b++)
      if (b & (1 << i))
      {
        if (ps[b] <= (n + 1) / a)
          ps[b] *= a;
        else
          ps[b] = n + 1;
      }
  }

  long long ans = 0;
  for (int b = 0; b < (1 << k); b++)
    ans += (n / ps[b]) * (__builtin_popcount(b) % 2 == 1 ? -1 : 1);
  std::cout << n - ans << std::endl;

  return 0;
}

