#include <bits/stdc++.h>

int n;
int64_t m;

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};

int get_pq(int n, int p)
{
  return n < p ? 0 : (n / p) + get_pq(n / p, p);
}

std::vector<int64_t> facs;

void dfs_fac(int p, int64_t cur)
{
  if (p == sizeof(primes) / sizeof(*primes))
    facs.push_back(cur);
  else
  {
    int q = get_pq(n, primes[p]);
    for (int i = 0; i <= q; i++)
    {
      dfs_fac(p + 1, cur);
      if (i != q) cur *= primes[p];
    }
  }
}

int main()
{
  scanf("%d%" SCNi64, &n, &m);
  dfs_fac(0, 1);
  std::sort(facs.begin(), facs.end());
  while (m > 0)
  {
    auto it = std::prev(std::upper_bound(facs.begin(), facs.end(), m));
    printf("%" SCNi64 "\n", *it);
    m -= *it;
  }
  return 0;
}
