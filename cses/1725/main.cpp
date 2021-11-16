#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int l = sc.next_int();
  int r = sc.next_int();

  std::vector<double> prob{1};
  for (int i = 0; i < n; i++)
  {
    std::vector<double> cur(prob.size() + 6);
    for (size_t i = 0; i < cur.size(); i++)
      for (size_t j = 1; j <= 6; j++)
        if (i >= j && i - j < prob.size())
          cur[i] += prob[i - j] / 6;
    prob = std::move(cur);
  }

  double ans = 0;
  for (int i = l; i <= r; i++)
    ans += prob[i];
  printf("%.6lf\n", ans);

  return 0;
}

