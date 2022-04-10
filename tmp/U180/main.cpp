#include <bits/stdc++.h>

struct bit_t
{
  std::vector<int> a;
  int n;

  bit_t(int n) : a(n + 1, 0), n(n + 1) {}

  int max(int p) 
  {
    p += 1;
    int res = 0;
    for (; p; p -= p & -p)
      res = std::max(res, a[p]);
    return res;
  }

  void set(int p, int v)
  {
    p += 1;
    for (; p < n; p += p & -p)
      a[p] = std::max(a[p], v);
  }
};

int read_int()
{
  int x;
  scanf("%d", &x);
  return x;
}

int main()
{
  int n = read_int();
  std::vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) a[i] = read_int() - 1;
  for (int i = 0; i < n; i++) b[i] = read_int() - 1;

  std::vector<int> ap(n), bp(n);
  for (int i = 0; i < n; i++) ap[a[i]] = i;
  for (int i = 0; i < n; i++) bp[b[i]] = i;

  bit_t aa(n);
  for (int i = 0; i < n; i++)
  {
    aa.set(ap[i], bp[i]);
    if (aa.max(ap[i]) > bp[i])
    {
      puts("NO");
      return 0;
    }
  }
  puts("YES");

  return 0;
}
