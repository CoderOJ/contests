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
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  double ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
    {
      int cnt = 0;
      for (int x = 1; x <= a[i]; x++)
        for (int y = 1; y <= a[j]; y++)
          if (x > y)
            cnt++;
      ans += 1.0 * cnt / (a[i] * a[j]);
    }

  printf("%.6f\n", ans);

  return 0;
}

