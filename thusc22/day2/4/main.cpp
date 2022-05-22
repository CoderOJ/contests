#include <bits/stdc++.h>

const double d = 0.9;

int main()
{
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> e(n);
  std::vector<int>              outd(n, 0);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
      int c;
      std::cin >> c;
      if (c == 1)
      {
        outd[i] += 1;
        e[j].push_back(i);
      }
    }

  std::vector<double> pr(n, 1.0 / n);
  while (true)
  {
    std::vector<double> upr(n);
    for (int i = 0; i < n; i++)
    {
      double s = 0;
      for (int v : e[i])
        s += pr[v] / outd[v];
      upr[i] = (1 - d) / n + d * s;
    }

    bool is_ok = [&] {
      for (int i = 0; i < n; i++)
        if (std::abs(pr[i] - upr[i]) >= 1e-6)
          return false;
      return true;
    }();
    
    pr = std::move(upr);
    if (is_ok)
      break;
  }
  
  for (int i = 0; i < n; i++)
    printf("%.6f\n", pr[i]);

  return 0;
}