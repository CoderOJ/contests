#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n);
  long long sum = 0;
  for (int i = 0; i < n; i++)
    sum += (a[i] = sc.next_int());

  long long ans = sum;
  for (int i = 0; i < (1<<n); i++)
  {
    long long cur = 0;
    for (int j = 0; j < n; j++)
      if (i & (1 << j))
        cur += a[j];
    check_min(ans, std::abs(sum - cur - cur));
  }

  std::cout << ans << std::endl;
  return 0;
}

